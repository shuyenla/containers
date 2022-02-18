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

        reverse_iterator();
        explicit reverse_iterator(Iterator x);
        template <class U> reverse_iterator(const reverse_iterator<U>& u);
        template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u);

        Iterator base() const; // explicit
        reference operator*() const;
        pointer operator->() const;

        reverse_iterator& operator++();
        reverse_iterator  operator++(int);
        reverse_iterator& operator--();
        reverse_iterator  operator--(int);

        reverse_iterator  operator+ (difference_type n) const;
        reverse_iterator& operator+=(difference_type n);
        reverse_iterator  operator- (difference_type n) const;
        reverse_iterator& operator-=(difference_type n);

        /*unspecified*/ operator[](difference_type n) const;
    protected:
        Iterator current;
    private:
        Iterator deref_tmp; // exposition only
    };
}

#endif