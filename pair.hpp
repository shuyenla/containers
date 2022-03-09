#pragma once

namespace ft {

	template<class T1, class T2>
	struct pair
	{
		typedef T1 		first_type;
		typedef T2 		second_type;
	
		T1 first;
		T2 second;
	
		pair():first(), second() {}
		pair(const T1& x, const T2& y):first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2>& p):first(p.first), second(p.second) {}
		
		operator pair<const T1, const T2>() const { return pair<const T1, const T2>(first, second); }

		pair( const pair& p ):first(p.first), second(p.second) {}

		pair& operator=(const pair& p)
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
    ft::pair<T1, T2> make_pair(T1 t, T2 u) { return pair<T1, T2>(t, u); }

	template<class T1, class T2>
		bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{ return lhs.first == rhs.first && lhs.second == rhs.second; }
	template<class T1, class T2>
		bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{ return !lhs == rhs; }
	template<class T1, class T2>
		bool operator< (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{ return lhs.first < rhs.first || (!(lhs.first < rhs.first) && lhs.second < rhs.second); }
	template<class T1, class T2>
		bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{ return lhs < rhs || lhs == rhs; }
	template<class T1, class T2>
		bool operator> (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{ return rhs < lhs; }
	template<class T1, class T2>
		bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{ return lhs == rhs || !lhs < rhs; }

	template<class T1, class T2>
		bool operator==(const ft::pair<T1,T2>& lhs, const T1& rhs)
		{ return lhs.first == rhs; }
	template<class T1, class T2>
		bool operator!=(const ft::pair<T1,T2>& lhs, const T1& rhs)
		{ return !lhs == rhs; }
	template<class T1, class T2>
		bool operator< (const ft::pair<T1,T2>& lhs, const T1& rhs)
		{ return lhs.first < rhs; }
	template<class T1, class T2>
		bool operator<=(const ft::pair<T1,T2>& lhs, const T1& rhs)
		{ return lhs < rhs || lhs == rhs; }
	template<class T1, class T2>
		bool operator> (const ft::pair<T1,T2>& lhs, const T1& rhs)
		{ return rhs < lhs.first; }
	template<class T1, class T2>
		bool operator>=(const ft::pair<T1,T2>& lhs, const T1& rhs)
		{ return lhs == rhs || !lhs < rhs; }
}