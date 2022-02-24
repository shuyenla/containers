#ifndef _PAIR_H_
# define _PAIR_H_

namespace ft {
  template<class T1, class T2>
  struct pair {
    typedef T1 		first_type;
    typedef T2 		second_type;
 
    T1 first;
    T2 second;
 
    pair();
    pair(const T1& x, const T2& y);
    template<class U1, class U2>
    pair(const pair<U1, U2>& p);

    pair& operator=(const pair& p);
  };

	template<class T1, class T2>
    ft::pair<T1, T2> make_pair(T1&&, T2&&);

	template< class T1, class T2 >
		bool operator==( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{}
	template< class T1, class T2 >
		bool operator!=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{}
	template< class T1, class T2 >
		bool operator<( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{}
	template< class T1, class T2 >
		bool operator<=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{}
	template< class T1, class T2 >
		bool operator>( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{}
	template< class T1, class T2 >
		bool operator>=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{}
}


#endif