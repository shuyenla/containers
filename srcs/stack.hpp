#pragma once

#include "vector.hpp"

namespace ft {

	template<class T, class Container = vector<T> > class stack
	{
		public:
			typedef typename Container::value_type			value_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;
			typedef typename Container::size_type			size_type;
			typedef Container								container_type;

		protected:
			Container c;

		public:
			explicit stack(const Container& cont = Container()):c(cont) {}
			~stack() {}
			bool empty() const					{ return c.empty(); }
			size_type size()  const             { return c.size(); }
			reference         top()             { return c.back(); }
			const_reference   top() const       { return c.back(); }
			void push(const value_type& x)      { c.push_back(x); }
			void pop()                          { c.pop_back(); }

			
			friend bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
			{ return x.c == y.c; }
			friend bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
			{ return x.c < y.c; }
	};

	template<class T, class Container>
		bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
		{ return !(x == y); }
	template<class T, class Container>
		bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
		{ return !(x <= y); }
	template<class T, class Container>
		bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
		{ return x < y || x == y; }
	template<class T, class Container>
		bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
		{ return !(x < y) || x == y; }
  };
