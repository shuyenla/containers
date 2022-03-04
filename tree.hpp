#ifndef _TREE_H_
# define _TREE_H_

# include <iostream>

# include "node.hpp"
# include "rbt_iterator.hpp"
# include "rbt_reverse_iterator.hpp"
#include "pair.hpp"

namespace ft {

	template<class Key, class P, class Compare, class Allocator>
	class RedBlackTree {

		public:

			typedef RedBlackTree<Key, P, Compare, Allocator>					rbt;
			typedef P															value_type;
			typedef Key															key_type;
			typedef Allocator													allocator_type;
			typedef size_t 														size_type;
	    	typedef ptrdiff_t					 								difference_type;
	    	typedef ft::rbt_iterator<P, rbt>											iterator;
	    	typedef ft::rbt_iterator<P, rbt>									const_iterator;
	    	typedef ft::rbt_reverse_iterator<ft::rbt_iterator<P, rbt> >				reverse_iterator;
	    	typedef ft::rbt_reverse_iterator<ft::rbt_iterator<const P, rbt> >		const_reverse_iterator;
	    	typedef node<P>														node_type;
			typedef typename ft::rbt_iterator<P, rbt>::nodePtr						nodePtr;
	    	typedef nodePtr														insert_return_type;

		private:

			nodePtr		_root;
			nodePtr		_TNULL;
			size_type	_size;


			nodePtr		newNode(P data)
			{
				nodePtr		n = new node<P>;
				n->data = data;
				n->parent = nullptr;
				n->left = nullptr;
				n->right = nullptr;
				n->color = 1;
				return n;
			}

			nodePtr		move(nodePtr newbee, nodePtr *parent, nodePtr target)
			{
				while (target != _TNULL)
				{
					*parent = target;
					if (newbee->data.first > target->data.first)
						target = target->right;
					else
						target = target->left;
				}
				newbee->parent = *parent;
				return target;
			}

			void		leftRotate(nodePtr x)
			{
				nodePtr		y = x->right;
				x->right = y->left;
				if (y->left != nullptr)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void		rightRotate(nodePtr x)
			{
				nodePtr		y = x->left;
				x->left = y->right;
				if (y->right != nullptr)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->right = x;
				x->parent = y;
			}

			void		insertFix(nodePtr x)
			{
				nodePtr		gx;
				while (x != _root && x->parent->color == 1)
				{
					gx = x->parent->parent;
					if (x->parent == gx->left)
					{
						if (gx->right->color == 1)
						{
							gx->left->color = 0;
							gx->right->color = 0;
							x = gx;
						}
						else if (x == x->parent->right)
						{
							x = x->parent;
							leftRotate(x);
						}
						x->parent->color = 0;
						x->parent->parent->color = 1;
						rightRotate(x->parent->parent);
					}
					else
					{
						if (gx->left->color == 1)
						{
							gx->left->color = 0;
							gx->right->color = 0;
							gx->color = 1;
							x = gx;
						}
						else if (x == x->parent->left)
						{
							x = x->parent;
							rightRotate(x);
						}
						x->parent->color = 0;
						x->parent->parent->color = 1;
						leftRotate(x->parent->parent);
					}
				}
				_root->color = 0;
			}

			void		transplant(nodePtr x, nodePtr y) {
				if (x->parent == nullptr)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->parent = x->parent;
			}

			void		deleteFix(nodePtr x) {
				nodePtr		y;
				while (x != _root && x->color == 0)
				{
					if (x == x->parent->left)
					{
						y = x->parent->right;
						if (y->color == 1)
						{
							y->color = 0;
							x->parent->color = 1;
							leftRotate(x->parent);
							y = x->parent->right;
						}
						if (y->left->color == 0 && y->right->color == 0) {
							y->color = 1;
							x = x->parent;
						}
						else {
							if (y->right->color == 0) {
								y->left->color = 0;
								y->color = 1;
								rightRotate(y);
								y = x->parent->right;
							}
							y->color = x->parent->color;
							x->parent->color = 0;
							y->right->color = 0;
							leftRotate(x->parent);
							x = _root;
						}
					}
					else
					{
						y = x->parent->left;
						if (y->color == 1) {
							y->color = 0;
							x->parent->color = 1;
							rightRotate(x->parent);
							y = x->parent->left;
						}
						if (y->right->color == 0 && y->right->color == 0) {
							y->color = 1;
							x = x->parent;
						}
						else
						{
							if (y->left->color == 0)
							{
								y->right->color = 0;
								y->color = 1;
								leftRotate(y);
								y = x->parent->left;
							}
							y->color = x->parent->color;
							x->parent->color = 0;
							y->left->color = 0;
							rightRotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = 0;
			}

			nodePtr		_upper_bound(key_type k)
			{
				nodePtr n = _searchR(_root, k);
				if (n->right != _TNULL)
				return min(n->right);

				nodePtr y = n->parent;
				while (y != _TNULL && n == y->right)
				{
					n = y;
					y = y->parent;
				}
				return y;
			}

			nodePtr		_lower_bound(key_type k)
			{
				nodePtr n = _searchR(_root, k);
				if (n->left != _TNULL)
					return max(n->left);

				nodePtr y = n->parent;
				while (y != _TNULL && n == y->left)
				{
					n = y;
					y = y->parent;
				}
				return y;
			}

			iterator		_insert(nodePtr start, P data)
			{
				nodePtr newbee = newNode(data);
				nodePtr parent = nullptr;
				nodePtr target = move(newbee, &parent, start);
			
				_size++;
				if (target == nullptr)
					_root = newbee;
				else if (newbee->data.first > parent->data.first)
					parent->right = newbee;
				else
					parent->left = newbee;

				if (parent == nullptr)
				{
					newbee->color = 0;
					return iterator(newbee);
				}

				if (newbee->parent->parent == nullptr)
					return iterator(newbee);

				insertFix(newbee);
				return iterator(newbee);
			}

			void		_deleteNode(key_type k)
			{
				nodePtr		d = _searchR(_root, k);
				if (d == _TNULL) {
					std::cout << "Key to be deleted not found in the tree" << std::endl;
					return ;
				}
				_size--;
				nodePtr		x, y;
				int			color = d->color;
				if (d->left == _TNULL)
				{
					x = d->right;
					transplant(d, x);
				}
				else if (x->right == _TNULL)
				{
					x = d->left;
					transplant(d, x);
				}
				else
				{
					y = min(d->right);
					color = y->color;
					x = y->right;
					if (y->parent == d)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = d->right;
						y->right->parent = y;
					}
					transplant(d, y);
					y->left = d->left;
					y->left->parent = y;
					y->color = d->color;
				}
				delete d;
				if (color == 0)
					deleteFix(x);
			}

			nodePtr		_searchR(nodePtr x, key_type k) const
			{
				if (x != _TNULL || k == x->data.first)
					return x;
				if (k < x->data.first)
					return _searchR(x->left, k);
				else
					return _searchR(x->right, k);
			}


		public:

			RedBlackTree() {
				_TNULL = new node<P>;
				_TNULL->color = 0;
				_TNULL->left = nullptr;
				_TNULL->right = nullptr;
				_root = _TNULL;
				_size = 0;
			}

			RedBlackTree(nodePtr root):_root(root), _size(1) {
				_TNULL = new node<P>;
				_TNULL->color = 0;
				_TNULL->left = nullptr;
				_TNULL->right = nullptr;
				_root->left = _TNULL;
				_root->right = _TNULL;
				_root->parent = nullptr;
				_root->color = 0;
			}

			nodePtr min(nodePtr x) {
				while (x->left != _TNULL)
					x = x->left;
				return x;
			}

			nodePtr	max(nodePtr x) {
				while (x->right != _TNULL)
					x = x->right;
				return x;
			}

			nodePtr					getRoot() const { return _root; }

			size_type				size() const { return _size; }
			size_type				max_size() const { allocator_type _a; return _a.max_size(); }

			iterator				begin() { return iterator(_root); }
	    	const_iterator			begin() const { return const_iterator(_root); }
	    	iterator				end() { return iterator(_TNULL); }
	    	const_iterator			end() const { return const_iterator(_TNULL); }

			reverse_iterator		rbegin() { return reverse_iterator(iterator(_TNULL)); }
    		const_reverse_iterator	rbegin() const { return const_reverse_iterator(iterator(_TNULL)); }
    		reverse_iterator		rend() { return reverse_iterator(iterator(_root)); }
    		const_reverse_iterator	rend() const { return const_reverse_iterator(iterator(_root)); }

			value_type&		 		operator[](const key_type& x)
			{
				nodePtr	n = _searchR(_root, x);
				if (n == _TNULL)
					return *insert(const_iterator(_root), ft::make_pair(x, 0));
				else
					return n->data;

			}

	    	value_type&			at(const key_type& x);
	    	const value_type&		at(const key_type& x) const;

			pair<iterator, bool>	insert(const value_type& x) { return ft::make_pair(_insert(_root, x), true); }
	    	iterator				insert(const_iterator position, const value_type& x) { return _insert(*position, x); }
	    	template<class InputIt>
	    		void				insert(InputIt first, InputIt last)
				{ 
					for (; first != last; first++)
						_insert(_root, *first);
				}
	    	void					erase(iterator pos) { _deleteNode(*pos); }
	    	void					erase(iterator first, iterator last)
			{
				for (; first != last; first++)
					_deleteNode(*first);
			}
			size_type				erase(const key_type& x) { _deleteNode(x); }

	    	void					clear() { erase(begin(), end()); }

	    	iterator				find(const key_type& x) { return iterator(_searchR(_root, x)); }
	    	const_iterator			find(const key_type& x) const { return const_iterator(_searchR(_root, x)); }
	    	nodePtr					lower_bound(const key_type& x) { return _lower_bound(x); }
	    	nodePtr					upper_bound(const key_type& x) { return _upper_bound(x); }
	    	pair<iterator, iterator>				equal_range(const key_type& x) { return ft::make_pair(iterator(lower_bound(x)), iterator(upper_bound(x))); }
	    	pair<const_iterator, const_iterator>	equal_range(const key_type& x) const { return ft::make_pair(const_iterator(lower_bound(x)), const_iterator(upper_bound(x))); }

			// void		printTree();
	};



}

#endif