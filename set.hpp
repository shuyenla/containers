#pragma once

# include <memory>
# include <cstddef>
# include <algorithm>
# include <cmath>
# include <iostream>
# include <ostream>

#include "enable_if.hpp"
#include "equal.hpp"
#include "rbt_iterator.hpp"
#include "iterator_traits.hpp"
#include "rbt_reverse_iterator.hpp"
#include "ft::pair.hpp"
#include "tree.hpp"

namespace ft {
    // class template set
    template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
    class set 
    {
        public:
            // types
            typedef  Key                                                        key_type;
            typedef  Compare                                                    key_compare;
            typedef  Key                                                        value_type;
            typedef  Compare                                                    value_compare;
            typedef  Allocator                                                  allocator_type;

        private:

			typedef RedBlackTree<value_type, key_type, mapped_type, Compare>		tree_type;

        public:
 			typedef typename allocator_type::pointer					pointer;
	    	typedef typename allocator_type::const_pointer				const_pointer;
	    	typedef value_type&											reference;
	    	typedef const value_type& 									const_reference;
	    	typedef typename tree_type::size_type 						size_type;
	    	typedef typename tree_type::difference_type 				difference_type;
	    	typedef typename tree_type::iterator						iterator;
	    	typedef typename tree_type::const_iterator					const_iterator;
	    	typedef typename tree_type::reverse_iterator				reverse_iterator;
	    	typedef typename tree_type::const_reverse_iterator			const_reverse_iterator;
			typedef typename tree_type::node_type						node_type;

		private:

			tree_type		_rbt;
			value_compare	_vc;
			allocator_type	_a;

            // construct/copy/destroy
            set():_rbt(), _vc(Compare()), _a(Allocator()) { }
            explicit set(const Compare& comp, const Allocator& = Allocator()):_rbt(),_vc(comp), _a(Allocator()) {}
            template<class InputIt>
                set(InputIt first, InputIt last,
                    const Compare& comp = Compare(), const Allocator& = Allocator()):_rbt(), _vc(comp), _a(Allocator()) { insert(first, last); }
            set(const set& x):_rbt(), _vc(x._vc), _a(x._a) { insert(x.begin(), x.end()); }
           
            ~set() {}
            set& operator=(const set& x)
            {
				if (this != &x)
				{
					_rbt.clear();
					_vc = x._vc;
					_a = x._a;
					_rbt.insert(x.begin(), x.end());
				}
				return *this;
			}
           
            allocator_type get_allocator() const { return Allocator(); }
        
            // iterators
            iterator				begin() { return _rbt.begin(); }
	    	const_iterator			begin() const { return _rbt.begin(); }
	    	iterator				end() { return _rbt.end(); }
	    	const_iterator			end() const { return _rbt.end(); }

	    	reverse_iterator		rbegin() { return _rbt.rbegin(); }
	    	const_reverse_iterator	rbegin() const { return _rbt.rbegin(); }
	    	reverse_iterator		rend() { return _rbt.rend(); }
	    	const_reverse_iterator	rend() const { return _rbt.rend(); }
            // capacity
            bool					empty() const { return _rbt.size() == 0 ? 1 : 0; }
	    	size_type				size() const { return _rbt.size(); }
	    	size_type				max_size() const { return _a.max_size(); }

            // modifiers
	    	pair<iterator, bool>	insert(const value_type& x) { return _rbt.insert(x); }
	    	iterator				insert(const_iterator position, const value_type& x) { return _rbt.insert(position, x); }
	    	template<class InputIt>
	    		void				insert(InputIt first, InputIt last) { return _rbt.insert(first, last); }
	    	void					erase(iterator position) { return _rbt.erase(position); }
			void					erase(iterator first, iterator last) { return _rbt.erase(first, last); }
	    	size_type				erase(const key_type& x) { return _rbt.erase(x); }
	    	void					swap(map& x) { std::swap(_rbt, x._rbt); }
	    	void					clear() { _rbt.clear();}
        
            // observers
	    	key_compare				key_comp() const { return _vc.comp; }
	    	value_compare			value_comp() const { return _vc; }
        
            // set operations
	    	iterator				find(const key_type& x) { return _rbt.find(x); }
	    	const_iterator			find(const key_type& x) const { return _rbt.find(x); }
	    	size_type				count(const key_type& x) const { return _rbt.find(x) != _rbt.end(); }
	    	iterator				lower_bound(const key_type& x) { return iterator(_rbt.lower_bound(x)); }
	    	const_iterator			lower_bound(const key_type& x) const { return const_iterator(_rbt.lower_bound(x)); }
	    	iterator				upper_bound(const key_type& x) { return iterator(_rbt.upper_bound(x)); }
	    	const_iterator			upper_bound(const key_type& x) const { return const_iterator(_rbt.upper_bound(x)); }
	    	pair<iterator, iterator>				equal_range(const key_type& x) { return _rbt.equal_range(x); }
	    	pair<const_iterator, const_iterator>	equal_range(const key_type& x) const { return _rbt.equal_range(x); }
	};
        
        template<class InputIt,
                class Compare = less</*iter-value-type*/<InputIt>>,
                class Allocator = allocator</*iter-value-type*/<InputIt>>>
            set(InputIt, InputIt,
                Compare = Compare(), Allocator = Allocator())
            -> set</*iter-value-type*/<InputIt>, Compare, Allocator>;

        
        template<class InputIt, class Allocator>
            set(InputIt, InputIt, Allocator)
            -> set</*iter-value-type*/<InputIt>,
                    less</*iter-value-type*/<InputIt>>, Allocator>;
      
        // swap
        template<class Key, class Compare, class Allocator>
            void swap(ft::set<Key, Compare, Allocator>& x,
                    ft::set<Key, Compare, Allocator>& y)
            ((x.swap(y)));
    }

 
  template<class Key, class Compare, class Allocator, class Predicate>
    typename ft::set<Key, Compare, Allocator>::size_type
      erase_if(ft::set<Key, Compare, Allocator>& c, Predicate pred);

      // swap
	template<class Key, class T, class Compare, class Allocator>
		void	swap(map<Key, T, Compare, Allocator>& x,
	    			 map<Key, T, Compare, Allocator>& y) { std::swap(x, y); }

	// overload operator
	template< class Key, class T, class Compare, class Alloc >
		bool operator==(const ft::set<Key, Compare, Allocator>& x,
                		const ft::set<Key, Compare, Allocator>& y)
		{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator!=(const ft::set<Key, Compare, Allocator>& x,
                		const ft::set<Key, Compare, Allocator>& y)
		{ return !(x == y); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator< (const ft::set<Key, Compare, Allocator>& x,
                		const ft::set<Key, Compare, Allocator>& y)
		{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator<=(const ft::set<Key, Compare, Allocator>& x,
                 		const ft::set<Key, Compare, Allocator>& y)
		{ return x < y || x == y; }
	template< class Key, class T, class Compare, class Alloc >
		bool operator> (const ft::set<Key, Compare, Allocator>& x,
        				const ft::set<Key, Compare, Allocator>& y)
		{ return !(x <= y); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator>=(const ft::set<Key, Compare, Allocator>& x,
                		const ft::set<Key, Compare, Allocator>& y)
		{ return !(x < y) || x == y; }

}