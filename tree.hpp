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

			void		insertFix(nodePtr newbee)
			{
				
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

				// why
				if (newbee->parent->parent == nullptr)
					return ;

				insertFix(newbee);
			}

			void		deleteNode(T data);
			nodePtr		search(T data);
			nodePtr		getRoot() { return _root; }
			void		printTree();
	};

}

#endif