#ifndef _RBT_ITERATOR_H_
# define _RBT_ITERATOR_H_

namespace ft {

	template<struct rbt_iterator>
	struct rbt_reverse_iterator
	{
		typedef bidirectional_iterator_tag 				iterator_category;
		typedef P           							value_type;
    	typedef ptrdiff_t    							difference_type;
    	typedef P*		     							pointer;
    	typedef P&			   							reference;
		typedef rbt_iterator<P>							iterator;
		typedef node<P>*								nodePtr;

		nodePtr		_it;

		rbt_iterator():_it(NULL) {}
		explicit rbt_iterator(nodePtr N):_it(P) {}

		reference operator*() const { return *(_it->data); }
    	pointer operator->() const { return _it->data; }
    	iterator& operator++() { _it = upper_bound(_it); return *this; }
    	iterator  operator++(int) {
			iterator it = *this;
			it = upper_bound(_it);
			return it; }
    	iterator& operator--() { _it = lower_bound(_it); return *this; }
    	iterator  operator--(int) {
			iterator it = *this;
			it = lower_bound(_it);
			return it; }

		friend bool operator==(const iterator &x, const iterator &y)
		{ return x._it == y._it; }
  		friend bool operator!=(const iterator &x, const iterator &y)
		{ return x._it != y._it; }

	};

}

#endif