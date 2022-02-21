#ifndef _ITERATOR_H_
# define _ITERATOR_H_

namespace ft {
    // primitives:
    template<class iterator> struct iterator_traits;
    template<class T> struct iterator_traits<T*>;
	template<class T> struct iterator_traits<const T*>;

    template<class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T*, class Reference = T&> class iterator
	{
		public:
    		typedef Category    		iterator_category;
			typedef T           		value_type;
    		typedef Distance    		difference_type;
    		typedef Pointer     		pointer;
    		typedef Reference   		reference;
	
			iterator() { _it = NULL; }

    	    explicit iterator(pointer x) { _it = x; }
    	    template <class U> iterator(const iterator<iterator_category, U> & u) { _it = u._it; }
    	    template <class U> iterator& operator=(const iterator<iterator_category, U> & u) { _it = u._it; }

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
    	    iterator  operator+ (difference_type n) const {	return _it + n; }
    	    iterator& operator+=(difference_type n) { _it += n; return *this; }
    	    iterator  operator- (difference_type n) const {	return _it - n; }
    	    iterator& operator-=(difference_type n) { _it -= n; return *this; }

    	    iterator& operator[](difference_type n) const { return _it + n; }

    	protected:
    	    pointer *_it;
    	private:


	};

}

#endif