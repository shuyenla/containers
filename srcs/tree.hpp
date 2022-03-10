#pragma once

# include <iostream>

# include "node.hpp"
# include "rbt_iterator.hpp"
# include "rbt_reverse_iterator.hpp"
# include "pair.hpp"

namespace ft {

	template<class P, class Key, class Mapped, class Compare, class Value_Compare, class Base>
	class RedBlackTree
	{
		public:
			typedef P																value_type;
			typedef Key																key_type;
			typedef Mapped															mapped_type;
			typedef Compare															key_compare;
			typedef Value_Compare													value_compare;
			typedef size_t 															size_type;
			typedef ptrdiff_t					 									difference_type;
			typedef typename Base::node_type										node_type;
			typedef typename Base::nodePtr											nodePtr;
			typedef typename Base::iterator											iterator;
			typedef typename Base::const_iterator									const_iterator;
			typedef typename Base::reverse_iterator									reverse_iterator;
			typedef typename Base::const_reverse_iterator							const_reverse_iterator;
			typedef std::allocator<node_type>										allocator_type;

		private:
			nodePtr			_root;
			nodePtr			_TNULL;
			size_type		_size;
			value_compare	_cmp;
			allocator_type	_allocator;

			nodePtr		newNode(P data)
			{
				nodePtr		n = _allocator.allocate(1);
				node_type	n_;
				n_.data = data;
				n_.parent = _TNULL;
				n_.left = _TNULL;
				n_.right = _TNULL;
				n_.root = &_root;
				n_.TNULL = _TNULL;
				n_.color = 1;
				_allocator.construct(n, n_);
				return n;
			}

			nodePtr		move(nodePtr newbee, nodePtr *parent, nodePtr target)
			{
				while (target != _TNULL)
				{
					*parent = target;
					if (!_cmp(newbee->data, target->data))
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

			void		insertFix(nodePtr x)
			{
				nodePtr		gx;
				while (x->parent->color == 1)
				{
					gx = x->parent->parent;
					if (x->parent == gx->left)
					{
						if (gx->right->color == 1)
						{
							x->parent->color = 0;
							gx->right->color = 0; 
							gx->color = 1;
							x = gx;
						}
						else 
						{
							if (x == x->parent->right)
							{
								x = x->parent;
								leftRotate(x);
							}
							x->parent->color = 0;
							gx->color = 1;
							rightRotate(gx);
						}	

					}
					else
					{
						if (gx->left->color == 1)
						{
							gx->left->color = 0;
							x->parent->color = 0;
							gx->color = 1;
							x = gx;
						}
						else
						{
							if (x == x->parent->left)
							{
								x = x->parent;
								rightRotate(x);
							} 			
							x->parent->color = 0;
							gx->color = 1;
							leftRotate(gx);	
						}		
					}
					if (x == _root) {
        				break;
      				}
				}
				_root->color = 0;
			}

			void		transplant(nodePtr x, nodePtr y)
			{
				if (x->parent == _TNULL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->parent = x->parent;
			}

			void		deleteFix(nodePtr x)
			{
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
						if (y->left->color == 0 && y->right->color == 0)
						{
							y->color = 1;
							x = x->parent;
						}
						else {
							if (y->right->color == 0)
							{
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
						if (y->color == 1)
						{
							y->color = 0;
							x->parent->color = 1;
							rightRotate(x->parent);
							y = x->parent->left;
						}
						if (y->right->color == 0 && y->right->color == 0)
						{
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
				for (const_iterator it = begin(); it != end(); it++)
					if (it.getNode()->data.first > k)
						return it.getNode();
				return _TNULL;
			}

			nodePtr		_lower_bound(key_type k) const
			{
				for (const_iterator it = begin(); it != end(); it++)
					if (it.getNode()->data.first > k || it.getNode()->data.first == k)
						return it.getNode();
				return _TNULL;
			}

			iterator	_insert(nodePtr start, value_type data)
			{
				nodePtr newbee = newNode(data);
				nodePtr parent = _TNULL;
				nodePtr target = move(newbee, &parent, start);
				_size++;
				if (target == _TNULL)
					_root = newbee;
				else if (!_cmp(newbee->data, parent->data))
					parent->right = newbee;
				else
					parent->left = newbee;
				if (parent == _TNULL)
				{
					newbee->color = 0;
					return iterator(newbee);
				}
				if (newbee->parent->parent == _TNULL)
				{ return iterator(newbee);}
				insertFix(newbee);
				return iterator(newbee);
			}

			void		_deleteNode(key_type k)
			{
				nodePtr		d = _searchR(_root, k);
				if (d == _TNULL)
						return ;
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
				_allocator.destroy(d);
				_allocator.deallocate(d, 1);
				_size--;
				if (color == 0)
					deleteFix(x);
			}

			nodePtr		_searchR(nodePtr x, key_type k) const
			{
				if (x == x->TNULL || x->data == k)
					return x;
				if (Compare()(k, x->data.first))
					return _searchR(x->left, k);
				else
					return _searchR(x->right, k);
			}

			void		_init()
			{
				_TNULL = _allocator.allocate(1);

				node_type	n_;
				P			p_;
				n_.data = p_;
				n_.parent = _TNULL;
				n_.left = _TNULL;
				n_.right = _TNULL;
				n_.root = &_root;
				n_.TNULL = _TNULL;
				n_.color = 0;
				_allocator.construct(_TNULL, n_);

				_root = _TNULL;
				_root->color = 0;
				_root->left = _TNULL;
				_root->right = _TNULL;
				_root->parent = _TNULL;
				_root->root = &_root;
				_root->TNULL = _TNULL;
				_size = 0;
			}

		public:
			RedBlackTree():_cmp(Compare()), _allocator(allocator_type()) { _init(); }
			
			RedBlackTree(const RedBlackTree &x): _cmp(x._cmp), _allocator(x._allocator) { _init(); insert(x.begin(), x.end()); }

			RedBlackTree& operator=(const RedBlackTree& x)
			{
				if (this != &x)
				{
 					clear();
					_cmp = x._cmp;
					_allocator = x._allocator;
					_init();
					insert(x.begin(), x.end());
				}
				return *this;
			}

			~RedBlackTree() { clear(); _allocator.destroy(_TNULL); _allocator.deallocate(_TNULL, 1); }

			nodePtr min(nodePtr x) const
			{
				if (x == _TNULL)
					return x;
				while (x->left != _TNULL)
					x = x->left;
				return x;
			}

			nodePtr	max(nodePtr x) const
			{
				while (x->right != _TNULL)
					x = x->right;
				return x;
			}

			nodePtr					getRoot() const { return _root; }
			size_type				size() const { return _size; }
			size_type				max_size() const { return _allocator.max_size(); }
			iterator				begin() { return iterator(min(_root)); }
	    	const_iterator			begin() const { return const_iterator(min(_root)); }
	    	iterator				end() { return iterator(_TNULL); }
	    	const_iterator			end() const { return const_iterator(_TNULL); }
			reverse_iterator		rbegin() { return reverse_iterator(end()); }
    		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
    		reverse_iterator		rend() { return reverse_iterator(begin()); }
    		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

			value_type&		 		operator[](const key_type& x)
			{
				nodePtr	n = _searchR(_root, x);
				if (n == _TNULL)
					return *insert(const_iterator(_root), 
					ft::pair<key_type, typename value_type::second_type>(x, typename value_type::second_type()));
				else
					return n->data;
			}

	    	value_type&			at(const key_type& x)
			{
				nodePtr	n = _searchR(_root, x);
				if (n == _TNULL)
					throw(std::out_of_range("out_of_range"));
				else
					return n->data;
			}

	    	const value_type&		at(const key_type& x) const
			{
				nodePtr	n = _searchR(_root, x);
				if (n == _TNULL)
					throw(std::out_of_range("out_of_range"));
				else
					return n->data;
			}

			void	insert(const key_type& x)
			{
				nodePtr old = _searchR(_root, x);
				if (old != _TNULL)
					return ;
				else
					_insert(_root, ft::make_pair(x, x));
			}

			pair<iterator, bool>	insert(const value_type& x)
			{
				nodePtr old = _searchR(_root, x.first);
				if (old != _TNULL)
					return ft::make_pair(iterator(old), false);
				else
					return ft::make_pair(iterator(_insert(_root, x)), true);
			}

	    	iterator				insert(const_iterator position, const value_type& x)
			{ (void)position; return insert(x).first; }

	    	template<class InputIt>
	    		void				insert(InputIt first, InputIt last)
				{ 
					for (; first != last; ++first)
						insert(*first);
				}

	    	void					erase(iterator pos) { erase(pos.getNode()->data.first); }

	    	void					erase(iterator first, iterator last)
			{
				while (first != last)
					erase((first++).getNode()->data.first);
			}

			size_type				erase(const key_type& x)
			{
				if (_searchR(_root, x) == _TNULL)
					return 0;
				else
					_deleteNode(x);
				return 1;
			}

			void					printHelper(nodePtr root, std::string indent, bool last)
			{
				if (root != _TNULL)
				{
					std::cout << indent;
					if (last)
					{
						std::cout << "R----";
						indent += "   ";
					}
					else
					{
						std::cout << "L----";
						indent += "|  ";
					}
					std::string sColor = root->color ? "RED" : "BLACK";
					std::cout << root->data.first << "(" << sColor << ")" << std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
			}

			void printTree()
			{
				if (_root)
					printHelper(this->_root, "", true);
			}

	    	void					clear() { erase(begin(), end()); }

			key_compare				key_comp() const { return _cmp.comp; }
	    	value_compare			value_comp() const { return _cmp; }

	    	iterator				find(const key_type& x) { return iterator(_searchR(_root, x)); }
	    	const_iterator			find(const key_type& x) const { return const_iterator(_searchR(_root, x)); }
	    	nodePtr					lower_bound(const key_type& x) { return _lower_bound(x); }
			nodePtr					lower_bound(const key_type& x) const { return _lower_bound(x); }
	    	nodePtr					upper_bound(const key_type& x) { return _upper_bound(x); }
			nodePtr					upper_bound(const key_type& x) const { return _upper_bound(x); }
	    	pair<iterator, iterator>				equal_range(const key_type& x)
			{ return ft::make_pair(iterator(lower_bound(x)), iterator(upper_bound(x))); }
	    	pair<const_iterator, const_iterator>	equal_range(const key_type& x) const
			{ return ft::make_pair(const_iterator(lower_bound(x)), const_iterator(upper_bound(x))); }
	};

}