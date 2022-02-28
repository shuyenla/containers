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

			nodePtr		move(nodePtr n, nodePtr *y, nodePtr x)
			{
				while (x != _TNULL)
				{
					*y = x;
					if (n->data < x->data)
						x = x->left;
					else
						x = x->right;
				}
				return x;
			}
			void		leftRotate(nodePtr n);
			void		rightRotate(nodePtr n);
			void		insertFix(nodePtr n);
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
				nodePtr n = newNode(data);
				nodePtr y = nullPtr;
				nodePtr x = move(n, &y, _root);
				
				
				
			}

			void		deleteNode(T data);
			nodePtr		search(T data);
			nodePtr		getRoot() { return _root; }
			void		printTree();
	};

}

#endif