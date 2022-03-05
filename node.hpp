#pragma once

namespace ft {

	template<class P>
	struct node {

		P		data;
		node	*parent;
		node	*left;
		node	*right;
		node	**root;
		node	*TNULL;
		int		color;

		node() {}
		node(const P p):data(p) {}
		node(const node & n):data(n.data), parent(n.parent), left(n.parent), right(n.left), root(n.root), TNULL(n.TNULL), color(n.color) { std::cout << "hello!!" << std::endl; }
		node& operator=(const node & n)
			{
				if (this != &n)
				{
					data = n._data;
					*parent = n.parent;
					*left = n.left;
					*right = n.right;
					**root = n.root;
					*TNULL = n.TNULL;
					color = n.color;
				}
				return *this;
			}

	};


}