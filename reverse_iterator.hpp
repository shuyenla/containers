#ifndef _REVERSE_ITERATOR_H_
# define _REVERSE_ITERATOR_H_

namespace ft {
  template <class Iterator>
    class reverse_iterator : public
        iterator<typename iterator_traits<Iterator>::iterator_category,
        typename iterator_traits<Iterator>::value_type,
        typename iterator_traits<Iterator>::difference_type,
        typename iterator_traits<Iterator>::pointer,
        typename iterator_traits<Iterator>::reference> {
    public:
        typedef Iterator                                            iterator_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::reference       reference;
        typedef typename iterator_traits<Iterator>::pointer         pointer;

        reverse_iterator() { _ptr = NULL; }
        explicit reverse_iterator(Iterator x) { _ptr = x; }
        // template <class U> reverse_iterator(const reverse_iterator<U>& u);
        // template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u);

        Iterator base() const; // explicit
        reference operator*() const { return *_ptr; }
        pointer operator->() const { return _ptr; }

        reverse_iterator& operator++() { _ptr--; return *this; }
        reverse_iterator  operator++(int) {
			iterator it = *this;
			--(*this);
			return it; }
        reverse_iterator& operator--() { _ptr++; return *this; }
        reverse_iterator  operator--(int) {
			iterator it = *this;
			++(*this);
			return it; }
        reverse_iterator  operator+ (difference_type n) const {	return _ptr - n; }
        reverse_iterator& operator+=(difference_type n) { _ptr -= n; return *this; }
        reverse_iterator  operator- (difference_type n) const {	return _ptr + n; }
        reverse_iterator& operator-=(difference_type n) { _ptr += n; return *this; }

        reverse_iterator& operator[](difference_type n) const { return _ptr - n; }
    protected:
        Iterator *_ptr;
    private:
    };
}

#endif