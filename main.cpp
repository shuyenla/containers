#include "vector.hpp"
#include <iostream>
#include <vector>

int main()
{

	ft::vector<int> v(5, 1);
	std::vector<int> stdv(5, 1);

	std::cout << *(v.begin() + 3) << std::endl ;
	v.resize(8, 20);
	std::cout << *(v.begin()) << std::endl;
	std::cout << v.size() << std::endl << std::endl;

	std::cout << *(stdv.begin() + 3) << std::endl ;
	stdv.resize(8, 20);
	std::cout << *(stdv.begin()) << std::endl;
	std::cout << stdv.size() << std::endl;
	return 0;
}