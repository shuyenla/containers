namespace ft {
  template<class I>
  struct iterator_traits {
    typedef /* see description */ iterator_category;
    typedef /* see description */ value_type;
    typedef /* see description */ difference_type;
    typedef /* see description */ pointer;
    typedef /* see description */ reference;
  };
 
  template<class T>
    requires is_object_v<T>
  struct iterator_traits<T*> {
    typedef contiguous_iterator_tag     iterator_concept;
    typedef random_access_iterator_tag  iterator_category;
    typedef remove_cv_t<T>              value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
  };
}