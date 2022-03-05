#pragma once

# include "node.hpp"
# include "tree.hpp"

namespace ft {

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
				if (x == x->TNULL || k == x->data.first)
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



	template<class Key, class P, class Compare, class Allocator>
	class rbt_iterator
	{
		public:

		typedef std::bidirectional_iterator_tag 		iterator_category;
		typedef Key           							key_type;
		typedef P           							value_type;
		typedef Compare           							compare_type;
		typedef Allocator           							allocator_type;
    	typedef ptrdiff_t    							difference_type;
    	typedef P*		     							pointer;
    	typedef P&			   							reference;
		typedef ft::rbt_iterator<Key, P, Compare, Allocator>				iterator;
		typedef node<P>*								nodePtr;

		operator rbt_iterator<Key, const P, Compare, Allocator>() const { return rbt_iterator<Key, const P, Compare, Allocator>(_it); }



		protected:

			nodePtr		_it;

		public:
		rbt_iterator():_it(){}
		explicit rbt_iterator(nodePtr N):_it(N) {}

		nodePtr		getNode() const { return _it; }
		reference operator*() const { return (_it->data); }
    	pointer operator->() const { return &(_it->data); }
    	iterator& operator++() { 
			// std::cout << "upper r: " << (*(_it->root))->data.first << std::endl;
			_it = __upper_bound(_it->data.first, *(_it->root)); 
		// std::cout << "upper: " << _it->data.first << std::endl;
		return *this; }
    	iterator  operator++(int) {
			iterator it = *this;
			++(*this);
			return it; }
    	iterator& operator--() { _it = __lower_bound(_it->data.first, *(_it->root)); return *this; }
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
