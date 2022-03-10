#if !defined(USING_STD)
# include "vector.hpp"
# define TESTED_NAMESPACE ft
#else
# include <vector>
# define TESTED_NAMESPACE std
#endif

# include <iostream>
# include <string>
# include <list>
# define TESTED_TYPE int

template <typename T>
void	printVector(TESTED_NAMESPACE::vector<T> const &vct)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator it(vct.begin());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite(vct.end());
	for (; it != ite; it++)
		std::cout << *it << std::endl;
}

int main()
{
    std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

    TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2(4);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct3;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct4;
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct5(lst.begin(), lst.end());

    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it(vct.begin());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite(vct.end());

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct2.size(); ++i)
		vct2[i] = (vct2.size() - i) * 5;

	printVector(vct);
	printVector(vct2);

	vct3.assign(vct.begin(), vct.end());
	vct.assign(vct2.begin(), vct2.end());
	vct2.assign(2, 42);
	vct4.assign(4, 21);

	printVector(vct);
	printVector(vct2);
	printVector(vct3);
	printVector(vct4);

	vct.pop_back();
	vct2.pop_back();

    std::cout << "front(): " << vct.front() << " " << vct2.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct2.back() << std::endl;

    lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	printVector(vct);

    for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}

    vct5.insert(vct5.end() - 2, 42);
    vct5.erase(vct5.end() - 3, vct5.end() - 1);
	printVector(vct5);

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit(it);
    TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit(rit);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_(it);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit2(cit);

    vct.swap(vct2);
	printVector(vct);
	printVector(vct2);

    for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}

	return 0;
}