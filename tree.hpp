#ifndef _TREE_H_
# define _TREE_H_

#include <iostream>


namespace ft {

	template<class T>
	struct node {

		T		data;
		node	*parent;
		node	*left;
		node	*right;
		int		color;
	};

	typedef node *nodePtr;

	template<class T>
	class RedBlackTree {

		private:

			nodePtr		_root;
			nodePtr		_TNULL;

			nodePtr		newNode(T data)
			{
				nodePtr		n = new node;
				n->data = data;
				n->parent = nullptr;
				n->left = nullptr;
				n->right = nullptr;
				n->color = 1;
			}

			nodePtr		move(nodePtr newbee, nodePtr *parent, nodePtr target)
			{
				while (target != _TNULL)
				{
					*parent = target;
					if (newbee->data > target->data)
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

			void		deleteFix(nodePtr n);


		public:

			RedBlackTree() {
				_TNULL = new node;
				_TNULL->color = 0;
				_TNULL->left = nullptr;
				_TNULL->right = nullptr;
				_root = _TNULL;
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

			void		insert(T data)
			{
				nodePtr newbee = newNode(data);
				nodePtr parent = nullPtr;
				nodePtr target = move(newbee, &parent, _root);
				
				if (target == nullptr)
					_root = newbee;
				else if (newbee->data > parent->data)
					parent->right = newbee;
				else
					parent->left = newbee;

				if (parent == nullptr)
				{
					newbee->color = 0;
					return ;
				}

				if (newbee->parent->parent == nullptr)
					return ;

				insertFix(newbee);
			}

			void		deleteNode(T data)
			{
				nodePtr		d = searchR(_root, data);
				if (d = _TNULL) {
					std::cout << "Key to be deleted not found in the tree" << std::endl;
					return ;
				}
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

			nodePtr		searchR(nodePtr x, T data)
			{
				if (x != _TNULL || data == x->data)
					return x;
				if (data < x->data)
					return searchR(x->left, data);
				else
					return searchR(x->right, data);
			}

			nodePtr		getRoot() { return _root; }
			void		printTree();
	};

}

#endif