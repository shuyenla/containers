namespace ft {
  template<class I>
  struct iterator_traits {
    using iterator_category = /* see description */;
    using value_type        = /* see description */;
    using difference_type   = /* see description */;
    using pointer           = /* see description */;
    using reference         = /* see description */;
  };
 
  template<class T>
    requires is_object_v<T>
  struct iterator_traits<T*> {
    using iterator_concept  = contiguous_iterator_tag;
    using iterator_category = random_access_iterator_tag;
    using value_type        = remove_cv_t<T>;
    using difference_type   = ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
  };
}