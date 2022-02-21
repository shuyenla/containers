#ifndef _ITERATOR_H_
# define _ITERATOR_H_

namespace ft {
    // primitives:
    template<class iterator> struct iterator_traits;
    template<class T> struct iterator_traits<T*>;
	template<class T> struct iterator_traits<const T*>;

    template< class T, class Category = std::random_access_iterator_tag,class Distance = ptrdiff_t,
    class Pointer = T*, class Reference = T&> class iterator
	{
		public:
    		typedef std::random_access_iterator_tag    		iterator_category;
			typedef T           		value_type;
    		typedef Distance    		difference_type;
    		typedef Pointer     		pointer;
    		typedef Reference   		reference;
	
			iterator() { _it = NULL; }

    	    explicit iterator(pointer x) { _it = x; }
    	    template <class U> iterator(const iterator<U> & u) { _it = u._it; }
    	    template <class U> iterator& operator=(const iterator<U> & u) { _it = u._it; }

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
    	    iterator  operator+ (difference_type n) const {	return *(_it + n); }
    	    iterator& operator+=(difference_type n) { _it += n; return *this; }
    	    iterator  operator- (difference_type n) const {	return *(_it - n); }
    	    iterator& operator-=(difference_type n) { _it -= n; return *this; }
    	    iterator& operator[](difference_type n) const { return *(_it + n); }

    	protected:
    	    pointer _it;
    	private:


	};


    template< class iterator1, class iterator2 >
    bool operator==( const iterator<iterator1>& lhs,
    const iterator<iterator2>& rhs ) { return lhs == rhs; }

    template< class iterator1, class iterator2 >
    bool operator!=( const iterator<iterator1>& lhs,
    const iterator<iterator2>& rhs ) { return lhs != rhs; }

    template< class iterator1, class iterator2 >
    bool operator<( const iterator<iterator1>& lhs,
    const iterator<iterator2>& rhs ) { return lhs > rhs; }

    template< class iterator1, class iterator2 >
    bool operator<=( const iterator<iterator1>& lhs,
    const iterator<iterator2>& rhs ) { return lhs >= rhs; }

    template< class iterator1, class iterator2 >
    bool operator>( const iterator<iterator1>& lhs,
    const iterator<iterator2>& rhs ) { return lhs < rhs; }

    template< class iterator1, class iterator2 >
    bool operator>=( const iterator<iterator1>& lhs,
    const iterator<iterator2>& rhs ) { return lhs <= rhs; }


}

#endif