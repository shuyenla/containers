#ifndef _RBT_REVERSE_ITERATOR_H_
# define _RBT_REVERSE_ITERATOR_H_

namespace ft {

	template<class rbt_iterator>
	class rbt_reverse_iterator
	{
		typedef rbt_iterator                            	                iterator_type;
		typedef rbt_reverse_iterator										reverse_iterator;
        typedef typename iterator_traits<rbt_iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<rbt_iterator>::value_type          value_type;
        typedef typename iterator_traits<rbt_iterator>::difference_type     difference_type;
        typedef typename iterator_traits<rbt_iterator>::reference           reference;
        typedef typename iterator_traits<rbt_iterator>::pointer             pointer;		
		typedef typename ft::rbt_iterator::nodePtr							nodePtr;

		nodePtr		_rit;

		rbt_reverse_iterator():_rit(NULL) {}
		explicit rbt_reverse_iterator(iterator x):_rit(x) {}

		iterator_type base() const { return _rit; }

		reference operator*() const { return *((_rit)->data); }
    	pointer operator->() const { return (base()--).operator->(); }
    	reverse_iterator& operator++() { _rit = lower_bound(_rit); return *this; }
    	reverse_iterator  operator++(int) {
			iterator rit = *this;
			++(*this);
			return rit; }
    	reverse_iterator& operator--() { _rit = upper_bound(_rit); return *this; }
    	reverse_iterator  operator--(int) {
			iterator rit = *this;
			--(*this);
			return rit; }

		friend bool operator==(const reverse_iterator &x, const reverse_iterator &y)
		{ return x._it == y._it; }
  		friend bool operator!=(const reverse_iterator &x, const reverse_iterator &y)
		{ return x._it != y._it; }

	};

}

#endif