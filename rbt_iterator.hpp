#pragma once

# include "node.hpp"
# include "tree.hpp"
# include "iterator_traits.hpp"

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

			template<class P, class Key, class Compare>
			node<P>*		__searchR(node<P>* x, Key k, Compare cmp)
			{
				if (x == x->TNULL || k == (x->data).first)
					return x;
				if (cmp(k, x->data.first))
					return __searchR(x->left, k, cmp);
				else
					return __searchR(x->right, k, cmp);
			}

			template<class P, class Key, class Compare>
			node<P>*		__upper_bound(Key k, node<P>* root, Compare cmp)
			{
				node<P>* n = __searchR(root, k, cmp);
				if (n->right != root->TNULL)
					return min(n->right);
				node<P>* y = n->parent;
				while (y != root->TNULL && n == y->right)
				{
					n = y;
					y = y->parent;
				}
				return y;
			}

			template<class P, class Key, class Compare>
			node<P>*		__lower_bound(Key k, node<P>* root, Compare cmp)
			{
				node<P>* n = __searchR(root, k, cmp);
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
			typedef std::bidirectional_iterator_tag 								iterator_category;
			typedef P           													value_type;
			typedef Mapped           												mapped_type;
			typedef nodePointer														nodePtr;
			typedef	Compare															cmp;
			typedef ptrdiff_t    													difference_type;
			typedef P*		     													pointer;
			typedef P&			   													reference;
			typedef ft::rbt_iterator<P, mapped_type, nodePtr, cmp>					iterator;
			typedef ft::rbt_iterator<const P, const mapped_type, nodePtr, cmp>		const_iterator;
	
		protected:
			nodePtr		_it;
			cmp			_cmp;

		public:
			rbt_iterator():_it(), _cmp(Compare()) {}
			explicit rbt_iterator(nodePtr n):_it(n), _cmp(Compare()) {}

			operator rbt_iterator<const P, const Mapped, nodePtr, cmp>() const
			{ return rbt_iterator<const P, const Mapped, nodePtr, cmp>(_it); }

			reference operator*() const { return _it->data; }
			pointer operator->() const { return &(_it->data); }

			iterator& operator++()
			{
				_it = __upper_bound(_it->data.first, *(_it->root), _cmp);
				return *this;
			}

			iterator  operator++(int)
			{
				iterator it = *this;
				++(*this);
				return it;
			}

			iterator& operator--()
			{
				if (_it != _it->TNULL)
					_it = __lower_bound(_it->data.first, *(_it->root), _cmp);
				else
					_it = max(*(_it->root));
				return *this;
			}

			iterator  operator--(int)
			{
				iterator it = *this;
				--(*this);
				return it;
			}

			nodePtr		getNode() const { return _it; }

			friend bool operator==(const iterator &x, const iterator &y)
			{ return x._it == y._it; }
			friend bool operator!=(const iterator &x, const iterator &y)
			{ return x._it != y._it; }
	};
}
