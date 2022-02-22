#include "vector.hpp"
#include <iostream>
#include <vector>

int main()
{

	// ft::vector<int> v(5, 1);
	// std::vector<int> stdv(5, 1);
	// ft::vector<int> v2(3, 10);

	// std::cout << *(v.begin() + 3) << std::endl ;
	// v.assign(v2.begin(), v2.end());
	// std::cout << *(v.begin()) << std::endl;
	// std::cout << v.at(2) << std::endl;
	// std::cout << v.front() << std::endl;
	// std::cout << v.back() << std::endl;
	// std::cout << v.size() << std::endl;
	// v.push_back(25);
	// std::cout << v.back() << std::endl;
	// v.pop_back();
	// v.pop_back();
	// std::cout << v.size() << std::endl << std::endl;

	// std::cout << *(stdv.begin() + 3) << std::endl ;
	// stdv.assign(v2.begin(), v2.end());
	// std::cout << *(stdv.begin()) << std::endl;
	// std::cout << stdv.at(2) << std::endl;
	// std::cout << stdv.front() << std::endl;
	// std::cout << stdv.back() << std::endl;
	// std::cout << stdv.size() << std::endl;
	// stdv.push_back(25);
	// std::cout << stdv.back() << std::endl;
	// stdv.pop_back();
	// stdv.pop_back();
	// std::cout << stdv.size() << std::endl << std::endl;

	std::vector<int> vct(5);
	std::vector<int>::iterator it = vct.begin(), ite = vct.end();
	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);
	std::cout << *it.base();
	return 0;
}