namespace ft {
  template<class T, class Allocator = std::allocator<T>>
  class vector {
  public:
    // types
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_traits<Allocator>::pointer pointer;
    typedef typename allocator_traits<Allocator>::const_pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef /* implementation-defined */ size_type;
    typedef /* implementation-defined */ difference_type;
    typedef /* implementation-defined */ iterator;
    typedef /* implementation-defined */ const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
 
    // construct/copy/destroy
    explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	vector (const vector& x);

    ~vector();
    vector& operator=(const vector& x);
    template<class InputIt>
      void assign(InputIt first, InputIt last);
    void assign(size_type n, const T& u);
    allocator_type get_allocator() const;
 
    // iterators
    iterator               begin();
    const_iterator         begin() const;
    iterator               end();
    const_iterator         end() const;
    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator       rend();
    const_reverse_iterator rend() const;
 
    // capacity
    [[nodiscard]] bool empty() const;
    size_type size() const;
    size_type max_size() const;
    size_type capacity() const;
    void      resize(size_type sz);
    void      resize(size_type sz, const T& c);
    void      reserve(size_type n);
 
    // element access
    reference       operator[](size_type n);
    const_reference operator[](size_type n) const;
    const_reference at(size_type n) const;
    reference       at(size_type n);
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;
 
    // modifiers
    void push_back(const T& x);
    void push_back(T&& x);
    void pop_back();
 
    iterator insert(const_iterator position, const T& x);
    iterator insert(const_iterator position, T&& x);
    iterator insert(const_iterator position, size_type n, const T& x);
    template<class InputIt>
      iterator insert(const_iterator position,
                                InputIt first, InputIt last);
    iterator insert(const_iterator position, initializer_list<T> il);
    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);
    void     swap(vector&)
     (allocator_traits<Allocator>::propagate_on_container_swap::value ||
               allocator_traits<Allocator>::is_always_equal::value);
    void     clear();
  };
 
  template<class InputIt, class Allocator = allocator</*iter-value-type*/<InputIt>>>
    vector(InputIt, InputIt, Allocator = Allocator())
      -> vector</*iter-value-type*/<InputIt>, Allocator>;
 
  // swap
  template<class T, class Allocator>
    void swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
     (noexcept(x.swap(y)));
}