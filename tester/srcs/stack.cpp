#if !defined(USING_STD)
# include "stack.hpp"
# define TESTED_NAMESPACE ft
#else
# include <stack>
# define TESTED_NAMESPACE std
#endif

# include <iostream>
# include <string>
# include <list>

#define TESTED_TYPE int
typedef TESTED_NAMESPACE::stack<TESTED_TYPE>::container_type container_type;

int main()
{
    container_type	c;

	c.push_back(21);
	c.push_back(42);
	c.push_back(1996);
	c.push_back(2012);
	c.push_back(548);
	c.push_back(1392);

    TESTED_NAMESPACE::stack<TESTED_TYPE>    s(c);

	std::cout << "empty: " << s.empty() << std::endl;
	std::cout << "size: " << s.size() << std::endl;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(6);

    std::cout << "empty: " << s.empty() << std::endl;
    std::cout << "size: " << s.size() << std::endl;

    TESTED_NAMESPACE::stack<TESTED_TYPE>    s2(s);

    std::cout << "empty: " << s2.empty() << std::endl;
    std::cout << "size: " << s2.size() << std::endl;

    std::cout << (s == s2) << std::endl;
    std::cout << (s != s2) << std::endl;
    std::cout << (s >  s2) << std::endl;
    std::cout << (s <  s2) << std::endl;
    std::cout << (s >= s2) << std::endl;
    std::cout << (s <= s2) << std::endl;
    
    s.pop();
    std::cout << (s == s2) << std::endl;
    std::cout << (s != s2) << std::endl;
    std::cout << (s >  s2) << std::endl;
    std::cout << (s <  s2) << std::endl;
    std::cout << (s >= s2) << std::endl;
    std::cout << (s <= s2) << std::endl;

    std::cout << "top: " << s.top() << std::endl;
    std::cout << "top: " << s2.top() << std::endl;

    std::cout << "empty: " << s.empty() << std::endl;
    std::cout << "size: " << s.size() << std::endl;

    std::cout << "empty: " << s2.empty() << std::endl;
    std::cout << "size: " << s2.size() << std::endl;
    return 0;
}