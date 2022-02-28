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

			void		leftRotate(node n);
			void		rightRotate(node n);
			void		insertFix(node n);
			void		deleteFix(node n);


		public:

			void		insertONode(node n);
			void		deletionNode(node n);
			nodePtr		search(T data);
			nodePtr		getRoot() { return _root; }
			void		printTree();
	};

}

#endif