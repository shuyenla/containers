#if !defined(USING_STD)
# include "vector.hpp"
# define TESTED_NAMESPACE ft
# define OW "FT"
#else
# include <vector>
# define TESTED_NAMESPACE std
# define OW "STD"
#endif

# include <iostream>
# include <string>
# include <list>
# define TESTED_TYPE int

int main()
{
    std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

    TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_2(4);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_3;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_4;
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_5(lst.begin(), lst.end());


    TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it(vct.begin());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite(vct.end());

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_2.size(); ++i)
		vct_2[i] = (vct_2.size() - i) * 5;
    
	vct_3.assign(vct.begin(), vct.end());
	vct.assign(vct_2.begin(), vct_2.end());
	vct_2.assign(2, 42);
	vct_4.assign(4, 21);

	vct.pop_back();
	vct_2.pop_back();

    std::cout << "front(): " << vct.front() << " " << vct_2.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_2.back() << std::endl;

    lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());

    for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
    vct_5.insert(vct_5.end() - 2, 42);
    vct_5.erase(vct_5.end() - 3, vct_5.end() - 1);

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
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crit_2(cit);

    vct.swap(vct_2);

    for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}

	// std::cout << "namespace: " <<  OW << std::endl;

}