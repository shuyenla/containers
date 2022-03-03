#pragma once

namespace ft {

	template<class P>
	struct node {

		P		data;
		node	*parent;
		node	*left;
		node	*right;
		int		color;
	};
}