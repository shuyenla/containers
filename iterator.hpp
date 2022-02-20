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
	
			iterator() { _ptr = NULL; }

    	    explicit iterator(pointer x) { _ptr = x; }
    	    // template <class U> iterator(const iterator<iterator_category, U> & u) {}
    	    // template <class U> iterator& operator=(const iterator<iterator_category, U> & u) {}

    	    reference operator*() const { return *_ptr; }
    	    pointer operator->() const { return _ptr; }
    	    iterator& operator++() { _ptr++; return *this; }
    	    iterator  operator++(int) {
				iterator it = *this;
				++(*this);
				return it; }
    	    iterator& operator--() { _ptr--; return *this; }
    	    iterator  operator--(int) {
				iterator it = *this;
				--(*this);
				return it; }
    	    iterator  operator+ (difference_type n) const {	return _ptr + n; }
    	    iterator& operator+=(difference_type n) { _ptr += n; return *this; }
    	    iterator  operator- (difference_type n) const {	return _ptr - n; }
    	    iterator& operator-=(difference_type n) { _ptr -= n; return *this; }

    	    iterator& operator[](difference_type n) const { return _ptr + n; }

    	protected:
    	    pointer *_ptr;
    	private:


	};

}

#endif