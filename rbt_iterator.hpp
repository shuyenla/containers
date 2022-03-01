#ifndef _RBT_ITERATOR_H_
# define _RBY_ITERATOR_H_

namespace ft {

	template<typename T>
	struct rbt_iterator
	{
		typedef bidirectional_iterator_tag 				iterator_category;
		typedef T           							value_type;
    	typedef ptrdiff_t    							difference_type;
    	typedef T*		     							pointer;
    	typedef T&			   							reference;
		typedef rbt_iterator<T>							iterator;
		typedef node<T>*								nodePtr;

		nodePtr		_ptr;


	};

}

#endif