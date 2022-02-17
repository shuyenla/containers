namespace ft {
  template<class Iter>
  class reverse_iterator {
  public:
    using iterator_type     = Iter;
    using iterator_concept  = /* see description */;
    using iterator_category = /* see description */;
    using value_type        = iter_value_t<Iter>;
    using difference_type   = iter_difference_t<Iter>;
    using pointer           = typename iterator_traits<Iter>::pointer;
    using reference         = iter_reference_t<Iter>;
 
    constexpr reverse_iterator();
    constexpr explicit reverse_iterator(Iter x);
    template<class U> constexpr reverse_iterator(const reverse_iterator<U>& u);
    template<class U> constexpr reverse_iterator& operator=(const reverse_iterator<U>& u);
 
    constexpr Iter base() const;
    constexpr reference operator*() const;
    constexpr pointer   operator->() const requires /* see description */;
 
    constexpr reverse_iterator& operator++();
    constexpr reverse_iterator  operator++(int);
    constexpr reverse_iterator& operator--();
    constexpr reverse_iterator  operator--(int);
 
    constexpr reverse_iterator  operator+ (difference_type n) const;
    constexpr reverse_iterator& operator+=(difference_type n);
    constexpr reverse_iterator  operator- (difference_type n) const;
    constexpr reverse_iterator& operator-=(difference_type n);
    constexpr /* unspecified */ operator[](difference_type n) const;
 
    friend constexpr iter_rvalue_reference_t<Iter>
      iter_move(const reverse_iterator& i) noexcept(/* see description */);
    template<indirectly_swappable<Iter> Iter2>
      friend constexpr void
        iter_swap(const reverse_iterator& x,
                  const reverse_iterator<Iter2>& y) noexcept(/* see description */);
 
  protected:
    Iter current;
  };
}