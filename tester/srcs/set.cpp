#if !defined(USING_STD)
# include "set.hpp"
# define TESTED_NAMESPACE ft
#else
# include <set>
# define TESTED_NAMESPACE std
#endif

# include <iostream>
# include <string>
# include <list>

#define TESTED_TYPE int

void    printSet(TESTED_NAMESPACE::set<TESTED_TYPE> m)
{
    TESTED_NAMESPACE::set<TESTED_TYPE>::iterator it = m.begin(), ite = m.end();
    std::cout << "print set: " << std::endl;
    for (; it != ite; it++)
        std::cout << *it << " " << *it << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::list<TESTED_TYPE> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(TESTED_TYPE(lst_size - i));

	TESTED_NAMESPACE::set<TESTED_TYPE> st(lst.begin(), lst.end());
	TESTED_NAMESPACE::set<TESTED_TYPE>::iterator it = st.begin(), ite = st.end();
    TESTED_NAMESPACE::set<TESTED_TYPE> st2(it, ite);

    printSet(st);
    printSet(st2);

    std::cout << *(st.lower_bound(2)) << " " << *(st.lower_bound(2)) << std::endl;
    std::cout << *(st.lower_bound(3)) << " " << *(st.lower_bound(3)) << std::endl;
    std::cout << *(st.lower_bound(4)) << " " << *(st.lower_bound(4)) << std::endl;
    std::cout << *(st.upper_bound(2)) << " " << *(st.upper_bound(2)) << std::endl;
    std::cout << *(st.upper_bound(3)) << " " << *(st.upper_bound(3)) << std::endl;
    std::cout << *(st.upper_bound(4)) << " " << *(st.upper_bound(4)) << std::endl;

    lst.clear();
    std::cout << st.empty() << std::endl;

    st.erase(st.begin());
    st.erase(--(st.end()--));
    st.erase(st.begin(), st.begin()++);
    st2.erase(st2.begin()++);
    st2.erase(st2.begin()++);
   
    std::cout << (st == st2) << std::endl;
    std::cout << (st != st2) << std::endl;
    std::cout << (st >  st2) << std::endl;
    std::cout << (st <  st2) << std::endl;
    std::cout << (st >= st2) << std::endl;
    std::cout << (st <= st2) << std::endl;

    
    st.insert(25);
	st.insert(19);

	st2.insert(404);
	st2.insert(502);

    std::cout << *st.find(2) << std::endl;
    std::cout << (st.find(-6) == st.end()) << std::endl;
    std::cout << st2.count(2) << std::endl;

    std::cout << (st == st2) << std::endl;
    std::cout << (st != st2) << std::endl;
    std::cout << (st >  st2) << std::endl;
    std::cout << (st <  st2) << std::endl;
    std::cout << (st >= st2) << std::endl;
    std::cout << (st <= st2) << std::endl;

    printSet(st);
    printSet(st2);

	TESTED_NAMESPACE::set<TESTED_TYPE>::const_iterator cit = st.begin();

	TESTED_NAMESPACE::set<TESTED_TYPE>::reverse_iterator rit(it);

	TESTED_NAMESPACE::set<TESTED_TYPE>::const_reverse_iterator crit(rit);
	TESTED_NAMESPACE::set<TESTED_TYPE>::const_reverse_iterator crit_(it);
	TESTED_NAMESPACE::set<TESTED_TYPE>::const_reverse_iterator crit_2(cit);
	crit_ = crit;

    st2.swap(st);

    printSet(st);
    printSet(st2);

    return 0;
}