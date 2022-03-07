#pragma once

# include <iostream>

# include "node.hpp"
# include "rbt_iterator.hpp"
// # include "rbt_c_iterator.hpp"
// # include "rbt_reverse_iterator.hpp"
#include "pair.hpp"

namespace ft {

	template<class P, class Mapped, class nodePtr>
	class rbt_iterator;
	template<class rbt_iterator>
	class rbt_reverse_iterator;

	template<class P, class Key, class Mapped>
	class RedBlackTree {

		public:

			typedef P																	value_type;
			typedef Key																	key_type;
			typedef Mapped																mapped_type;
			typedef size_t 																size_type;
	    	typedef ptrdiff_t					 										difference_type;
	    	typedef node<P>																node_type;
			typedef node_type*															nodePtr;
	    	typedef ft::rbt_iterator<P, mapped_type, nodePtr>							iterator;
	    	typedef ft::rbt_iterator<const P, const mapped_type, nodePtr>				const_iterator;
	    	typedef ft::rbt_reverse_iterator<ft::rbt_iterator<P, mapped_type, nodePtr> >			reverse_iterator;
	    	typedef ft::rbt_reverse_iterator<ft::rbt_iterator<const P, const mapped_type, nodePtr> >	const_reverse_iterator;

		private:

			nodePtr			_root;
			nodePtr			_TNULL;
			size_type		_size;
			// allocator_type	_allocator;

			nodePtr		newNode(P data)
			{
				nodePtr		n = new node<P>;
				n->data = data;
				n->parent = _TNULL;
				n->left = _TNULL;
				n->right = _TNULL;
				n->root = &_root;
				n->TNULL = _TNULL;
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
				return *parent;
			}

			void		leftRotate(nodePtr x)
			{
				nodePtr		y = x->right;
				x->right = y->left;
				if (y->left != _TNULL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == _TNULL)
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

				// std::cout << "-----x: " <<x->data.first << std::endl;
				// std::cout << "x->left : " << x->left->data.first << std::endl;
				// std::cout << "x->right: " << x->right->data.first << std::endl << std::endl << std::endl;
				nodePtr		y = x->left;
				x->left = y->right;
				if (y->right != _TNULL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == _TNULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->right = x;
				x->parent = y;

				
			}

void insertFix(nodePtr k) {
    nodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == _root) {
        break;
      }
    }
    _root->color = 0;
  }


			// void		insertFix(nodePtr x)
			// {
			// 	nodePtr		gx;
			// 	// std::cout << "fixing" << std::endl;
			// 	while (x != _root && x->parent->color == 1)
			// 	{
			// 		gx = x->parent->parent;
			// 		if (x->parent == gx->left)
			// 		{
			// 			if (gx->right->color == 1)
			// 			{
			// 				gx->left->color = 0;
			// 				gx->right->color = 0;
			// 				gx->color = 1;
			// 				x = gx;
			// 			}
			// 			else if (x == x->parent->right)
			// 			{
			// 				x = x->parent;
			// 				leftRotate(x);
			// 			}
			// 			x->parent->color = 0;
			// 			gx->color = 1;
			// 			rightRotate(gx);
			// 							_root->color = 0;

			// 		}
			// 		else
			// 		{
			// 			if (gx->left->color == 1)
			// 			{
			// 				gx->left->color = 0;
			// 				gx->right->color = 0;
			// 				gx->color = 1;
			// 				x = gx;
			// 			}
			// 			else if (x == x->parent->left)
			// 			{
			// 				x = x->parent;
			// 				rightRotate(x);
			// 			}
			// 			x->parent->color = 0;
			// 			gx->color = 1;
			// 			leftRotate(gx);
			// 			_root->color = 0;

			// 		}
			// 		if (x == _root) {
        	// 			break;
      		// 		}
			// 	}
			// 	_root->color = 0;
			// }

			void		transplant(nodePtr x, nodePtr y) {
				if (x->parent == _TNULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->parent = x->parent;
			}

			void		deleteFix(nodePtr x) {
				nodePtr		y;
				// std::cout << "deleteFix func" << std::endl;
				// printTree();
				while (x != _root && x->color == 0)
				{
					// std::cout << "deleteFix loop" << std::endl;
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

			nodePtr		_upper_bound(key_type k) const
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

			nodePtr		_lower_bound(key_type k) const 
			{
				nodePtr n = _searchR(_root, k);
				if (n->data.first == k)
					return n;
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

			iterator	_insert(nodePtr start, value_type data)
			{
				nodePtr newbee = newNode(data);
				nodePtr parent = _TNULL;
				nodePtr target = move(newbee, &parent, start);
				_size++;
				if (target == _TNULL)
					_root = newbee;
				else if (newbee->data.first > parent->data.first)
					parent->right = newbee;
				else
					parent->left = newbee;
				if (parent == _TNULL)
				{
					// printTree();
					newbee->color = 0;
					return iterator(newbee);
				}

				if (newbee->parent->parent == _TNULL)
				{ return iterator(newbee);}
				// printTree();
				// std::cout << std::endl;
				// std::cout << "r: " << _root->data.first << std::endl;
				// std::cout << std::endl;
				insertFix(newbee);
				// printTree();
				// std::cout << std::endl;
				// std::cout << "r: " << _root->data.first << std::endl;
				// std::cout << std::endl;

				return iterator(newbee);
			}

			void		_deleteNode(key_type k)
			{
				nodePtr		d = _searchR(_root, k);
				if (d == _TNULL) {
					// std::cout << "Key to be deleted not found in the tree" << std::endl;
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
				else if (d->right == _TNULL)
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
				// std::cout << "searching!!" << std::endl;
				if (x == _TNULL || k == x->data.first)
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
				_TNULL->left = _TNULL;
				_TNULL->right = _TNULL;
				_TNULL->parent = _TNULL;
				_TNULL->root = &_root;
				_TNULL->TNULL = _TNULL;
				_root = _TNULL;
				_root->color = 0;
				_root->left = _TNULL;
				_root->right = _TNULL;
				_root->parent = _TNULL;
				_root->root = &_root;
				_root->TNULL = _TNULL;
				_size = 0;
			}

			~RedBlackTree() { clear(); delete _TNULL; }

			nodePtr min(nodePtr x) const {
				// std::cout << "add:" << x << std::endl;
				// std::cout << "add l:" << x->left << std::endl;
				// std::cout << "add t:" << _TNULL << std::endl;
				if (x == _TNULL)
					return x;
				while (x->left != _TNULL)
					x = x->left;
				return x;
			}

			nodePtr	max(nodePtr x) const {
				while (x->right != _TNULL)
					x = x->right;
				return x;
			}

			nodePtr					getRoot() const { return _root; }

			size_type				size() const { return _size; }
			iterator				begin() { return iterator(min(_root)); }
	    	const_iterator			begin() const { return const_iterator(min(_root)); }
	    	iterator				end() { return iterator(_TNULL); }
	    	const_iterator			end() const { return const_iterator(_TNULL); }

			reverse_iterator		rbegin() { return reverse_iterator(iterator(_TNULL)); }
    		const_reverse_iterator	rbegin() const { return const_reverse_iterator(iterator(_TNULL)); }
    		reverse_iterator		rend() { return reverse_iterator(iterator(min(_root))); }
    		const_reverse_iterator	rend() const { return const_reverse_iterator(iterator(min(_root))); }

			value_type&		 		operator[](const key_type& x)
			{
				nodePtr	n = _searchR(_root, x);
				if (n == _TNULL)
					return *insert(const_iterator(_root), 
					ft::pair<key_type, typename value_type::second_type>(x, typename value_type::second_type()));
				else
					return n->data;
			}

	    	// value_type&			at(const key_type& x)
			// {
			// 	if (n > _size)
			// 	throw(std::out_of_range("out_of_range"));
			// }
	    	// const value_type&		at(const key_type& x) const;

			pair<iterator, bool>	insert(const value_type& x) {
				nodePtr old = _searchR(_root, x.first);
				if (old != _TNULL)
				{
					return ft::make_pair(old, false);
				}
				else
					return ft::make_pair(_insert(_root, x), true); }
	    	iterator				insert(const_iterator position, const value_type& x) { (void)position; return insert(x).first; }
	    	template<class InputIt>
	    		void				insert(InputIt first, InputIt last)
				{ 
					for (; first != last; first++)
						insert(*first);
				}

	    	void					erase(iterator pos) { erase((*pos).first); }
	    	void					erase(iterator first, iterator last)
			{
				while (first != last)
					erase((*(first++)).first);
			}
			size_type				erase(const key_type& x)
			{
				if (_searchR(_root, x) == _TNULL)
					return 0;
				else
					_deleteNode(x);
				return 1;
			}
			void printHelper(nodePtr root, std::string indent, bool last) {
				if (root != _TNULL) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}

				std::string sColor = root->color ? "RED" : "BLACK";
				std::cout << root->data.first << "(" << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
				}
			}

			void printTree() {
				if (_root) {
				printHelper(this->_root, "", true);
				}
			}

	    	void					clear() { erase(begin(), end()); }

	    	iterator				find(const key_type& x) { return iterator(_searchR(_root, x)); }
	    	const_iterator			find(const key_type& x) const { return const_iterator(_searchR(_root, x)); }
	    	nodePtr					lower_bound(const key_type& x) { return _lower_bound(x); }
			nodePtr					lower_bound(const key_type& x) const { return _lower_bound(x); }
	    	nodePtr					upper_bound(const key_type& x) { return _upper_bound(x); }
			nodePtr					upper_bound(const key_type& x) const { return _upper_bound(x); }
	    	pair<iterator, iterator>				equal_range(const key_type& x) { return ft::make_pair(iterator(lower_bound(x)), iterator(upper_bound(x))); }
	    	pair<const_iterator, const_iterator>	equal_range(const key_type& x) const { return ft::make_pair(const_iterator(lower_bound(x)), const_iterator(upper_bound(x))); }
	};

}