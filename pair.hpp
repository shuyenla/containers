#ifndef _PAIR_H_
# define _PAIR_H_

namespace ft {

  template<class T1, class T2>
  struct pair {
    typedef T1 		first_type;
    typedef T2 		second_type;
 
    T1 first;
    T2 second;
 
    pair():first(), second() {}
    pair(const T1& x, const T2& y):first(x), second(y) {}
    template<class U1, class U2>
    pair(const pair<U1, U2>& p):first(p.first), second(p.second) {}

    pair& operator=(const pair<T1, T2>& p)
	{
		if (this != &p)
		{
			first = p.first;
			second = p.second;
		}
		return *this;
	}
  };

	template<class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 t, T2 u) { pair<T1, T2> p(t, u); return p; }

	template< class T1, class T2 >
		bool operator==( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{ return std::less<T1>(lhs.first, rhs.first); }
	template< class T1, class T2 >
		bool operator!=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
		// { return ; }
	template< class T1, class T2 >
		bool operator<( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
		{ return std::less<T1>(lhs.first, rhs.first); }
	template< class T1, class T2 >
		bool operator<=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
		// { return ; }
	template< class T1, class T2 >
		bool operator>( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
		// { return ; }
	template< class T1, class T2 >
		bool operator>=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
		// { return ; }
}


#endif