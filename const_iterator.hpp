#ifndef _CONST_ITERATOR_H_
# define _CONST_ITERATOR_H_

namespace ft {
    // primitives:
    template<class iterator> struct iterator_traits;
    template<class T> struct iterator_traits<T*>;
	template<class T> struct iterator_traits<const T*>;
    template<class Category, class T, class Distance = ptrdiff_t,
    class Const_pointer = T*, class Reference = T&> class const_iterator
	{
		public:
    		typedef Category    		const_iterator_category;
			typedef T           		value_type;
    		typedef Distance    		difference_type;
    		typedef Const_pointer     	const_pointer;
    		typedef Reference   		reference;
	
			const_iterator() { _ptr = NULL; }

    	    // explicit const_iterator(const_pointer x) { _ptr = x; }
    	    // template <class U> const_iterator(const const_iterator<const_iterator_category, U> & u) {}
    	    // template <class U> const_iterator& operator=(const const_iterator<const_iterator_category, U> & u) {}

    	    reference operator*() const { return *_ptr; }
    	    const_pointer operator->() const { return _ptr; }
    	    const_iterator& operator++() { _ptr++; return *this; }
    	    const_iterator  operator++(int) {
				const_iterator it = *this;
				++(*this);
				return it; }
    	    const_iterator& operator--() { _ptr--; return *this; }
    	    const_iterator  operator--(int) {
				const_iterator it = *this;
				--(*this);
				return it; }
    	    const_iterator  operator+ (difference_type n) const {	return _ptr + n; }
    	    const_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
    	    const_iterator  operator- (difference_type n) const {	return _ptr - n; }
    	    const_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }

    	    const_iterator& operator[](difference_type n) const { return _ptr + n; }

    	protected:
    	    const_pointer *_ptr;
    	private:


	};

}

#endif