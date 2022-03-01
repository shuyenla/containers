#ifndef _RBT_ITERATOR_H_
# define _RBY_ITERATOR_H_

namespace ft {

	template<typename N>
	struct rbt_iterator
	{
		typedef bidirectional_iterator_tag 				iterator_category;
		typedef N           							value_type;
    	typedef ptrdiff_t    							difference_type;
    	typedef N*		     							pointer;
    	typedef N&			   							reference;
		typedef rbt_iterator<N>							iterator;
		typedef node<N>*								nodePtr;

		nodePtr		_it;

		rbt_iterator():_it(NULL) {}
		explicit rbt_iterator(nodePtr N):_it(N) {}
		

		reference operator*() const { return *_it; }
    	pointer operator->() const { return _it; }
    	iterator& operator++() { _it++; return *this; }
    	iterator  operator++(int) {
			iterator it = *this;
			++(*this);
			return it; }
    	iterator& operator--() { _it--; return *this; }
    	iterator  operator--(int) {
			iterator it = *this;
			--(*this);
			return it; }


	};

}

#endif