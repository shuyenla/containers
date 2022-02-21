#ifndef _REVERSE_ITERATOR_H_
# define _REVERSE_ITERATOR_H_

namespace ft {
    template <class iterator>
    class reverse_iterator {
        public:
            typedef iterator                                                iterator_type;
            typedef typename iterator_traits<iterator>::iterator_category   iterator_category;
            typedef typename iterator_traits<iterator>::value_type          value_type;
            typedef typename iterator_traits<iterator>::difference_type     difference_type;
            typedef typename iterator_traits<iterator>::reference           reference;
            typedef typename iterator_traits<iterator>::pointer             pointer;

            reverse_iterator() { _rit = NULL; }
            explicit reverse_iterator(iterator x) { _rit = x; }
            template <class U> reverse_iterator(const reverse_iterator<U>& u) { _rit = u._rit; }
            template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u) { _rit = u.rit; }

            iterator base() const {return _rit + 1;}
            reference operator*() const { return *_rit; }
            pointer operator->() const { return _rit; }

            reverse_iterator& operator++() { _rit--; return *this; }
            reverse_iterator  operator++(int) {
    			iterator it = *this;
    			--(*this);
    			return it; }
            reverse_iterator& operator--() { _rit++; return *this; }
            reverse_iterator  operator--(int) {
    			iterator it = *this;
    			++(*this);
    			return it; }
            reverse_iterator  operator+ (difference_type n) const {	return _rit - n; }
            reverse_iterator& operator+=(difference_type n) { _rit -= n; return *this; }
            reverse_iterator  operator- (difference_type n) const {	return _rit + n; }
            reverse_iterator& operator-=(difference_type n) { _rit += n; return *this; }

            reverse_iterator& operator[](difference_type n) const { return _rit - n; }
        protected:
            iterator *_rit;

    };
}

#endif