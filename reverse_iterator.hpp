#pragma once

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

            operator reverse_iterator < ft::iterator< const typename iterator::value_type > > () const { return reverse_iterator<ft::iterator< const typename iterator::value_type> >(base()); }

            reverse_iterator():_rit(NULL) {}
            explicit reverse_iterator(iterator x):_rit(x) {}
            template <class U>
            reverse_iterator(const reverse_iterator<U>& u):_rit(u.base()) {}
            template <class U>
            reverse_iterator& operator=(const reverse_iterator<U>& u) {
                if (*this != u)
                    _rit = u.base();
                return *this;
            }

            iterator_type base() const { return _rit; }
            reference operator*() const { return *(_rit - 1); }
            pointer operator->() const { return (base() - 1).operator->(); }

            reverse_iterator& operator++() { _rit--; return *this; }
            reverse_iterator  operator++(int) {
    			reverse_iterator rit = *this;
    			++(*this);
    			return rit; }
            reverse_iterator& operator--() { _rit++; return *this; }
            reverse_iterator  operator--(int) {
    			reverse_iterator rit = *this;
    			--(*this);
    			return rit; }
            reverse_iterator  operator+ (difference_type n) const {	return reverse_iterator(base()-n); }
            reverse_iterator& operator+=(difference_type n) { _rit -= n; return *this; }
            reverse_iterator  operator- (difference_type n) const {	return reverse_iterator(base()+n); }
            reverse_iterator& operator-=(difference_type n) { _rit += n; return *this; }

            reference operator[](difference_type n) const { return base()[-n-1]; }
            reverse_iterator& operator= (value_type v) { *_rit = v; return *this; }
        protected:
            iterator _rit;

    };

    template< class Iterator1, class Iterator2 >
    bool operator==( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ) { return lhs.base() == rhs.base(); }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ) { return lhs.base() != rhs.base(); }

    template< class Iterator1, class Iterator2 >
    bool operator<( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ) { return lhs.base() > rhs.base(); }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ) { return lhs.base() >= rhs.base(); }

    template< class Iterator1, class Iterator2 >
    bool operator>( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ) { return lhs.base() < rhs.base(); }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const reverse_iterator<Iterator1>& lhs,
    const reverse_iterator<Iterator2>& rhs ) { return lhs.base() <= rhs.base(); }

    template<class T>
	reverse_iterator<T>  operator+ (ptrdiff_t n, reverse_iterator<T> &lhs) { return reverse_iterator<T>(lhs.base() - n); }
	template<class T>
    reverse_iterator<T>  operator- (ptrdiff_t n, reverse_iterator<T> &lhs) { return reverse_iterator<T>(lhs.base() + n); }
	template<class T>
    typename reverse_iterator<T>::difference_type operator- (const reverse_iterator<T> &lhs, const reverse_iterator<T> &rhs)
    { return rhs.base() - lhs.base(); }
	template<class T, class U>
    typename reverse_iterator<T>::difference_type operator- (const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs)
    { return rhs.base() - lhs.base(); }

	template<class T>
	std::ostream &operator<<( std::ostream& os, reverse_iterator<T> const it ) { std::cout << it.base(); return os; }


}