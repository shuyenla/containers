#pragma once

# include "node.hpp"
# include "tree.hpp"

namespace ft {

	template<class iterator> struct iterator_traits;
    template<class T> struct iterator_traits<T*>;
	template<class T> struct iterator_traits<const T*>;

			template<class P>
			node<P>* min(node<P>* x) {
				while (x->left != x->TNULL)
					x = x->left;
				return x;
			}

			template<class P>
			node<P>*	max(node<P>* x) {
				while (x->right != x->TNULL)
					x = x->right;
				return x;
			}

			template<class P, class Key>
			node<P>*		__searchR(node<P>* x, Key k)
			{
				// std::cout << "searching!!" << std::endl;
				if (x == x->TNULL || k == (x->data).first)
					return x;
				if (k < x->data.first)
					return __searchR(x->left, k);
				else
					return __searchR(x->right, k);
			}


			template<class P, class Key>
			node<P>*		__upper_bound(Key k, node<P>* root)
			{
				node<P>* n = __searchR(root, k);
				// std::cout << "upper n: " << n->data.first << std::endl;
				if (n->right != root->TNULL)
					return min(n->right);

				node<P>* y = n->parent;
				// std::cout << "upper y: " << y->data.first << std::endl;
				while (y != root->TNULL && n == y->right)
				{
					n = y;
					y = y->parent;
				}
				return y;
			}

			template<class P, class Key>
			node<P>*		__lower_bound(Key k, node<P>* root)
			{
				node<P>* n = __searchR(root, k);
				if (n->left != root->TNULL)
					return max(n->left);

				node<P>* y = n->parent;
				while (y != root->TNULL && n == y->left)
				{
					n = y;
					y = y->parent;
				}
				return y;
			}



	template<class P, class Mapped, class nodePointer, class Compare>
	class rbt_iterator
	{
		public:

			typedef std::bidirectional_iterator_tag 							iterator_category;
			typedef P           												value_type;
			typedef Mapped           											mapped_type;
			typedef nodePointer													nodePtr;
			typedef ptrdiff_t    												difference_type;
			typedef P*		     												pointer;
			typedef P&			   												reference;
			typedef ft::rbt_iterator<P, mapped_type, nodePtr>					iterator;
			typedef ft::rbt_iterator<const P, const mapped_type, nodePtr>		const_iterator;
	
		protected:
			nodePtr		_it;

		private:
			Compare		_cmp;

		public:
			rbt_iterator():_it(NULL) {}
			explicit rbt_iterator(nodePtr n):_it(n) {}


			operator rbt_iterator<const P, const Mapped, nodePtr>() const
			{ return rbt_iterator<const P, const Mapped, nodePtr>(_it); }


			nodePtr		getNode() const { return _it; }
			reference operator*() const { return _it->data; }
			pointer operator->() const { return &(_it->data); }
			iterator& operator++() {
				_it = __upper_bound(_it->data.first, *(_it->root));
				return *this; }
			iterator  operator++(int) {
				iterator it = *this;
				++(*this);
				return it; }
			iterator& operator--()
			{
				if (_it != _it->TNULL)
					_it = __lower_bound(_it->data.first, *(_it->root));
				else
					_it = max(*(_it->root));
				return *this; }

			iterator  operator--(int) {
				iterator it = *this;
				--(*this);
				return it; }


			friend bool operator==(const iterator &x, const iterator &y)
			{ return x._it == y._it; }
			friend bool operator!=(const iterator &x, const iterator &y)
			{ return x._it != y._it; }
			// template<class U>
			// friend bool operator==(const iterator &x, const ft::rbt_iterator<U> &y)
			// { (void)x, (void)y; return false; }
			// template<class U>
			// friend bool operator!=(const iterator &x, const ft::rbt_iterator<U> &y)
			// { (void)x, (void)y; return true; }

	};

}
