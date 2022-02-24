namespace ft {
  // class template map
  template<class Key, class T, class Compare = less<Key>,
           class Allocator = allocator<pair<const Key, T>>>
    class map
	{
		public:
    // types
    typedef Key															key_type;
    typedef nT															mapped_type;
    typedef pair<const Key, T>											value_type ;
    typedef Compare														key_compare;
    typedef Allocator													allocator_type;
    typedef typename allocator_traits<Allocator>::pointer				pointer;
    typedef typename allocator_traits<Allocator>::const_pointer			const_pointer;
    typedef value_type&													reference;
    typedef const value_type& 											const_reference;
    typedef /* implementation-defined */ 								size_type;
    typedef /* implementation-defined */ 								difference_type;
    typedef /* implementation-defined */ 								iterator;
    typedef /* implementation-defined */ 								const_iterator;
    typedef ft::reverse_iterator<iterator>								reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
    typedef /* unspecified */											node_type;
    typedef /*insert-return-type*/<iterator, node_type>					insert_return_type;
 
    class value_compare {
      friend class map;
    protected:
      Compare comp;
      value_compare(Compare c) : comp(c) {}
    public:
      bool operator()(const value_type& x, const value_type& y) const {
        return comp(x.first, y.first);
      }
    };
 
    // construct/copy/destroy
    map() : map(Compare()) { }
    explicit map(const Compare& comp, const Allocator& = Allocator());
    template<class InputIt>
      map(InputIt first, InputIt last,
          const Compare& comp = Compare(), const Allocator& = Allocator());
    map(const map& x);

    ~map();
    map& operator=(const map& x);
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
    bool empty() const;
    size_type size() const;
    size_type max_size() const;
 
    // element access
    mapped_type& operator[](const key_type& x);
    mapped_type&       at(const key_type& x);
    const mapped_type& at(const key_type& x) const;
 
    // modifiers

    pair<iterator, bool> insert(const value_type& x);
    iterator insert(const_iterator position, const value_type& x);
    template<class InputIt>
      void insert(InputIt first, InputIt last);
 
    iterator  erase(iterator position);
    size_type erase(const key_type& x);
    iterator  erase(iterator first, iterator last);
    void      swap(map& x)
;
    void      clear();
 
    // observers
    key_compare key_comp() const;
    value_compare value_comp() const;
 
    // map operations
    iterator       find(const key_type& x);
    const_iterator find(const key_type& x) const;
 
    size_type      count(const key_type& x) const;
 
    iterator       lower_bound(const key_type& x);
    const_iterator lower_bound(const key_type& x) const;
 
    iterator       upper_bound(const key_type& x);
    const_iterator upper_bound(const key_type& x) const;
 
    pair<iterator, iterator>               equal_range(const key_type& x);
    pair<const_iterator, const_iterator>   equal_range(const key_type& x) const;
  };
 
  template<class InputIt, class Compare = less</*iter-key-type*/<InputIt>>,
           class Allocator = allocator</*iter-to-alloc-type*/<InputIt>>>
    map(InputIt, InputIt, Compare = Compare(), Allocator = Allocator())
      -> map</*iter-key-type*/<InputIt>, /*iter-mapped-type*/<InputIt>,
             Compare, Allocator>;
 
  template<class Key, class T, class Compare = less<Key>,
           class Allocator = allocator<pair<const Key, T>>>
    map(initializer_list<pair<Key, T>>, Compare = Compare(), Allocator = Allocator())
      -> map<Key, T, Compare, Allocator>;
 
  template<class InputIt, class Allocator>
    map(InputIt, InputIt, Allocator)
      -> map</*iter-key-type*/<InputIt>, /*iter-mapped-type*/<InputIt>,
             less</*iter-key-type*/<InputIt>>, Allocator>;
 
  template<class Key, class T, class Allocator>
    map(initializer_list<pair<Key, T>>, Allocator) -> map<Key, T, less<Key>, Allocator>;
 
  // swap
  template<class Key, class T, class Compare, class Allocator>
    void swap(map<Key, T, Compare, Allocator>& x,
              map<Key, T, Compare, Allocator>& y)
     ((x.swap(y)));
}
	}
 
  template<class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key, T, Compare, Allocator>& x,
                    const map<Key, T, Compare, Allocator>& y);
 
  template<class Key, class T, class Compare, class Allocator>
    void swap(map<Key, T, Compare, Allocator>& x,
              map<Key, T, Compare, Allocator>& y)
     ((x.swap(y)));

}