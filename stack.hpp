#ifndef _STACK_H_
# define _STACK_H_

#include "vector.hpp"

namespace ft {

  template<class T, class Container = ft::vector<T> > class stack
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
	 };
  };
 
  template<class T, class Container>
    bool operator==(const ft::stack<T, Container>& x, const ft::stack<T, Container>& y) {}
  template<class T, class Container>
    bool operator!=(const ft::stack<T, Container>& x, const ft::stack<T, Container>& y);
  template<class T, class Container>
    bool operator< (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y);
  template<class T, class Container>
    bool operator> (const ft::stack<T, Container>& x, const ft::stack<T, Container>& y);
  template<class T, class Container>
    bool operator<=(const ft::stack<T, Container>& x, const ft::stack<T, Container>& y);
  template<class T, class Container>
    bool operator>=(const ft::stack<T, Container>& x, const ft::stack<T, Container>& y);



#endif