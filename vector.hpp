namespace ft {
  template<class T, class Allocator = allocator<T>>
  class vector {
  public:
    // types
    typedef value_type              T;
    typedef allocator_type          Allocator;
    typedef pointer                 typename allocator_traits<Allocator>::pointer;
    typedef const_pointer           typename allocator_traits<Allocator>::const_pointer;
    typedef reference               value_type&;
    typedef const_reference         const value_type&;
    typedef size_type               /* implementation-defined */;
    typedef difference_type         /* implementation-defined */;
    typedef iterator                /* implementation-defined */;
    typedef const_iterator          /* implementation-defined */;
    typedef reverse_iterator        std::reverse_iterator<iterator>;
    typedef const_reverse_iterator  std::reverse_iterator<const_iterator>;
 
    // construct/copy/destroy
    vector()((Allocator())) : vector(Allocator()) { }
    explicit vector(const Allocator&);
    explicit vector(size_type n, const Allocator& = Allocator());
    vector(size_type n, const T& value, const Allocator& = Allocator());
    template<class InputIt>
      vector(InputIt first, InputIt last, const Allocator& = Allocator());
    vector(const vector& x);
    vector(vector&&);
    vector(const vector&, const Allocator&);
    vector(vector&&, const Allocator&);
    vector(initializer_list<T>, const Allocator& = Allocator());
    ~vector();
    vector& operator=(const vector& x);
    vector& operator=(vector&& x)
     (allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
               allocator_traits<Allocator>::is_always_equal::value);
    vector& operator=(initializer_list<T>);
    template<class InputIt>
      void assign(InputIt first, InputIt last);
    void assign(size_type n, const T& u);
    void assign(initializer_list<T>);
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