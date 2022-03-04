#ifndef _RBT_ITERATOR_H_
# define _RBT_ITERATOR_H_

# include "node.hpp"
# include "tree.hpp"

namespace ft {

	template<class P>
	class rbt_iterator
	{
		public:

		typedef std::bidirectional_iterator_tag 		iterator_category;
		typedef P           							value_type;
    	typedef ptrdiff_t    							difference_type;
    	typedef P*		     							pointer;
    	typedef P&			   							reference;
		typedef ft::rbt_iterator<P>						iterator;
		typedef node<P>*								nodePtr;

		operator rbt_iterator<const P>() const { return rbt_iterator<const P>(_it); }

		protected:

		nodePtr		_it;

		public:
		rbt_iterator():_it(NULL) {}
		explicit rbt_iterator(nodePtr N):_it(N) {}

		reference operator*() const { return (_it->data); }
    	pointer operator->() const { return &(_it->data); }
    	iterator& operator++() { 
			
			_it = _it->upper_bound(_it->data.first); return *this; }
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
		// template<class U>
		// friend bool operator==(const iterator &x, const ft::rbt_iterator<U> &y)
		// { (void)x, (void)y; return false; }
		// template<class U>
  		// friend bool operator!=(const iterator &x, const ft::rbt_iterator<U> &y)
		// { (void)x, (void)y; return true; }

	};

}

#endif