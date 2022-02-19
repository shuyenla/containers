#ifndef _ITERATOR_TRAITS_H_
# define _ITERATOR_TRAITS_H_

namespace ft {

template<class iterator> struct iterator_traits {
    typedef typename iterator::difference_type      difference_type;
    typedef typename iterator::value_type           value_type;
    typedef typename iterator::pointer              pointer;
    typedef typename iterator::reference            reference;
    typedef typename iterator::iterator_category    iterator_category;
};

template<class T> struct iterator_traits<T*> {
    typedef ptrdiff_t                               difference_type;
    typedef T                                       value_type;
    typedef T*                                      pointer;
    typedef T&                                      reference;
    typedef std::random_access_iterator_tag         iterator_category;
};
 
template<class T> struct iterator_traits<const T*> {
    typedef ptrdiff_t                               difference_type;
    typedef T                                       value_type;
    typedef const T*                                pointer;
    typedef const T&                                reference;
    typedef std::random_access_iterator_tag         iterator_category;
};

}

#endif