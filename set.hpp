#pragma once

# include <memory>
# include <cstddef>
# include <algorithm>
# include <cmath>
# include <iostream>
# include <ostream>

#include "enable_if.hpp"
#include "equal.hpp"
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "tree.hpp"
# include "set_iterator.hpp"
#include "value_compare.hpp"

namespace ft {
    // class template set
    template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set
    {
        public:
            // types
            typedef Key                                                                         key_type;
            typedef Compare                                                                     key_compare;
            typedef Key                                                                         value_type;
            typedef Compare                                                                     value_compare;
            typedef Allocator                                                                   allocator_type;
            typedef ft::pair<Key, value_type>								                 	pair_type;
            typedef ft::value_compare<pair_type, Compare>                                       pair_compare;


        public:

            typedef typename allocator_type::pointer				                        	pointer;
	    	typedef typename allocator_type::const_pointer		                        		const_pointer;
	    	typedef value_type&									                        		reference;
	    	typedef const value_type& 					                        				const_reference;
	    	typedef size_t              	                        	        				size_type;
	    	typedef ptrdiff_t                   				                                difference_type;

			typedef node<pair_type>																node_type;
			typedef node_type*																	nodePtr;
	    	typedef ft::set_iterator<pair_type, const key_type, nodePtr, Compare>					    iterator;
	   		typedef ft::set_iterator<pair_type, const key_type, nodePtr, Compare>		    const_iterator;
            typedef ft::rbt_reverse_iterator<iterator>			            					reverse_iterator;
			typedef ft::rbt_reverse_iterator<const_iterator>			            			const_reverse_iterator;

        private:

			typedef RedBlackTree<pair_type, key_type, key_type, Compare, pair_compare, ft::set<Key, Compare> >		tree_type;

		private:

			tree_type		*_rbt;
			value_compare	_vc;
			allocator_type	_a;

        public:

            // construct/copy/destroy
            set():_vc(Compare()), _a(Allocator()) { _rbt = new tree_type(); }
            explicit set(const Compare& comp, const Allocator& = Allocator()):_vc(comp), _a(Allocator()) {_rbt = new tree_type(); }
            template<class InputIt>
                set(InputIt first, InputIt last,
                    const Compare& comp = Compare(), const Allocator& = Allocator()):_vc(comp), _a(Allocator()) { _rbt = new tree_type(); insert(first, last); }
            set(const set& x): _vc(x._vc), _a(x._a) { _rbt = new tree_type(); insert(x.begin(), x.end()); }
            ~set() {}

            set& operator=(const set& x)
            {
				if (this != &x)
				{
					_rbt->clear();
					_vc = x._vc;
					_a = x._a;
					insert(x.begin(), x.end());
				}
				return *this;
			}
           
            allocator_type get_allocator() const { return Allocator(); }
        
            // iterators
            iterator				begin() { return _rbt->begin(); }
	    	const_iterator			begin() const { return _rbt->begin(); }
	    	iterator				end() { return _rbt->end(); }
	    	const_iterator			end() const { return _rbt->end(); }

	    	reverse_iterator		rbegin() { return _rbt->rbegin(); }
	    	const_reverse_iterator	rbegin() const { return _rbt->rbegin(); }
	    	reverse_iterator		rend() { return _rbt->rend(); }
	    	const_reverse_iterator	rend() const { return _rbt->rend(); }

            // capacity
            bool					empty() const { return _rbt->size() == 0 ? 1 : 0; }
	    	size_type				size() const { return _rbt->size(); }
	    	size_type				max_size() const { return _rbt->max_size(); }

            // modifiers
	    	ft::pair<iterator, bool>	insert(const Key& x) { return _rbt->insert(ft::make_pair(x, x)); }
	    	iterator				    insert(const_iterator position, const Key& x) { return _rbt->insert(position, ft::make_pair(x, x)); }
	    	template<class InputIt>
	    		void				    insert(InputIt first, InputIt last)
                {
                    for (; first != last; ++first)
						insert(*first);
                }
	    	void					erase(iterator position) { return _rbt->erase(position); }
			void					erase(iterator first, iterator last) { return _rbt->erase(first, last); }
	    	size_type				erase(const key_type& x) { return _rbt->erase(x); }
	    	void					swap(set& x)
            {
				std::swap(_rbt, x._rbt);
				std::swap(_vc, x._vc);
				std::swap(_a, x._a);
			}
	    	void					clear() { _rbt->clear(); }
        
            // observers
	    	key_compare				key_comp() const { return _vc; }
	    	value_compare			value_comp() const { return _vc; }
        
            // set operations
	    	iterator				find(const key_type& x) { return _rbt->find(x); }
	    	const_iterator			find(const key_type& x) const { return _rbt->find(x); }
	    	size_type				count(const key_type& x) const { return _rbt->find(x) != _rbt->end(); }
	    	iterator				lower_bound(const key_type& x) { return iterator(_rbt->lower_bound(x)); }
	    	const_iterator			lower_bound(const key_type& x) const { return const_iterator(_rbt->lower_bound(x)); }
	    	iterator				upper_bound(const key_type& x) { return iterator(_rbt->upper_bound(x)); }
	    	const_iterator			upper_bound(const key_type& x) const { return const_iterator(_rbt->upper_bound(x)); }
	    	pair<iterator, iterator>				equal_range(const key_type& x) { return _rbt->equal_range(x); }
	    	pair<const_iterator, const_iterator>	equal_range(const key_type& x) const { return _rbt->equal_range(x); }
	};

        // swap
        template<class Key, class Compare, class Allocator>
            void swap(ft::set<Key, Compare, Allocator>& x,
                    ft::set<Key, Compare, Allocator>& y)
        { x.swap(y); }

        // overload operator
        template<class Key, class Compare, class Allocator>
            bool operator==(const ft::set<Key, Compare, Allocator>& x,
                            const ft::set<Key, Compare, Allocator>& y)
            { return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }
        template<class Key, class Compare, class Allocator>
            bool operator!=(const ft::set<Key, Compare, Allocator>& x,
                            const ft::set<Key, Compare, Allocator>& y)
            { return !(x == y); }
        template<class Key, class Compare, class Allocator>
            bool operator< (const ft::set<Key, Compare, Allocator>& x,
                            const ft::set<Key, Compare, Allocator>& y)
            { return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
        template<class Key, class Compare, class Allocator>
            bool operator<=(const ft::set<Key, Compare, Allocator>& x,
                            const ft::set<Key, Compare, Allocator>& y)
            { return x < y || x == y; }
        template<class Key, class Compare, class Allocator>
            bool operator> (const ft::set<Key, Compare, Allocator>& x,
                            const ft::set<Key, Compare, Allocator>& y)
            { return !(x <= y); }
        template<class Key, class Compare, class Allocator>
            bool operator>=(const ft::set<Key, Compare, Allocator>& x,
                            const ft::set<Key, Compare, Allocator>& y)
            { return !(x < y) || x == y; }
}