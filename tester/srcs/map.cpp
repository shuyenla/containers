#if !defined(USING_STD)
# include "map.hpp"
# define TESTED_NAMESPACE ft
#else
# include <map>
# define TESTED_NAMESPACE std
#endif

# include <iostream>
# include <string>
# include <list>

#define T1 int
#define T2 int

typedef TESTED_NAMESPACE::pair<const T1, T2> T;

void    printMap(TESTED_NAMESPACE::map<T1, T2> m)
{
    TESTED_NAMESPACE::map<T1, T2>::iterator it = m.begin(), ite = m.end();
    std::cout << "print map: " << std::endl;
    for (; it != ite; it++)
        std::cout << it->first << " " << it->second << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::list<T> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T(lst_size - i, i));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();
    TESTED_NAMESPACE::map<T1, T2> mp2(it, ite);

    printMap(mp);

    for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

    printMap(mp);
    printMap(mp2);

    std::cout << (mp.lower_bound(2))->first << " " << (mp.lower_bound(2))->second << std::endl;
    std::cout << (mp.lower_bound(3))->first << " " << (mp.lower_bound(3))->second << std::endl;
    std::cout << (mp.lower_bound(4))->first << " " << (mp.lower_bound(4))->second << std::endl;
    std::cout << (mp.upper_bound(2))->first << " " << (mp.upper_bound(2))->second << std::endl;
    std::cout << (mp.upper_bound(3))->first << " " << (mp.upper_bound(3))->second << std::endl;
    std::cout << (mp.upper_bound(4))->first << " " << (mp.upper_bound(4))->second << std::endl;

    lst.clear();
    std::cout << mp.empty() << std::endl;

    mp.erase(mp.begin());
    mp.erase(--(mp.end()--));
    mp.erase(mp.begin(), mp.begin()++);
    mp2.erase(mp2.begin()++);
    mp2.erase(mp2.begin()++);
    mp[2] = 45;
    mp[476] = 234;

    std::cout << (mp == mp2) << std::endl;
    std::cout << (mp != mp2) << std::endl;
    std::cout << (mp >  mp2) << std::endl;
    std::cout << (mp <  mp2) << std::endl;
    std::cout << (mp >= mp2) << std::endl;
    std::cout << (mp <= mp2) << std::endl;

    mp2[24] = 32;
    mp2[-3] = 35;
    mp.insert(T(42, 25));
	mp.insert(T(42, 19));

	mp2.insert(T(50, 404));
	mp2.insert(T(35, 502));
    std::cout << mp.find(2)->first << std::endl;
    std::cout << (mp.find(-6) == mp.end()) << std::endl;
    std::cout << mp2.count(2) << std::endl;

    std::cout << (mp == mp2) << std::endl;
    std::cout << (mp != mp2) << std::endl;
    std::cout << (mp >  mp2) << std::endl;
    std::cout << (mp <  mp2) << std::endl;
    std::cout << (mp >= mp2) << std::endl;
    std::cout << (mp <= mp2) << std::endl;

    printMap(mp);
    printMap(mp2);

	TESTED_NAMESPACE::map<T1, T2>::const_iterator cit = mp.begin();

	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator rit(it);

	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit(rit);
	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit_(it);
	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator crit_2(cit);
	crit_ = crit;

    mp2.swap(mp);

    printMap(mp);
    printMap(mp2);

    return 0;
}