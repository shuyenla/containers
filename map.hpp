#ifndef _MAP_H_
# define _MAP_H_

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

namespace ft {

	template<class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
	{
		public:

	    	typedef Key													key_type;
	    	typedef T													mapped_type;
	    	typedef pair<const Key, T>									value_type;
	    	typedef Compare												key_compare;
	    	typedef Allocator											allocator_type;

		private:

			typedef RedBlackTree<key_type, 
			value_type, key_compare, allocator_type>					tree_type;

			tree_type	_rbt;

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
	    	typedef typename tree_type::insert_return_type				insert_return_type;

	    	class value_compare {
	    		friend class map;
	    		protected:
	    			Compare comp;
	    			value_compare(Compare c) : comp(c) {}
	    		public:
	    			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
	    	};

	    	// construct/copy/destroy
	    	map() : map(Compare()) {}
	    	explicit map(const Compare& comp, const Allocator& = Allocator());
	    	template<class InputIt>
	    		map(InputIt first, InputIt last,
	    	    const Compare& comp = Compare(), const Allocator& = Allocator());
	    	map(const map& x);

	    	~map() {}
	    	map& operator=(const map& x);
	    	allocator_type get_allocator() const { return allocator_type(_rbt.get_allocator()); }

	    	// iterators
	    	iterator				begin() { return _rbt.begin(); }
	    	const_iterator			begin() const { return _rbt.begin(); }
	    	iterator				end() { return _rbt.end(); }
	    	const_iterator			end() const { return _rbt.end(); }

	    	reverse_iterator		rbegin() { return _rbt.rbegin(); }
	    	const_reverse_iterator	rbegin() const { return _rbt.rbegin(); }
	    	reverse_iterator		rend() { return _rbt.rbegin(); }
	    	const_reverse_iterator	rend() const { return _rbt.rbegin(); }

	    	// capacity
	    	bool					empty() const { return _rbt.size() == 0; }
	    	size_type				size() const { return _rbt.size(); }
	    	size_type				max_size() const { return _rbt.max_size(); }

	    	// element access
	    	// mapped_type& operator[](const key_type& x);
	    	// mapped_type&			at(const key_type& x);
	    	// const mapped_type&		at(const key_type& x) const;

	    	// modifiers
	    	pair<iterator, bool>	insert(const value_type& x) { return _rbt.insert(x); }
	    	iterator				insert(const_iterator position, const value_type& x) { return _rbt.insert(position, x); }
	    	template<class InputIt>
	    		void				insert(InputIt first, InputIt last) { return _rbt.insert(first, last); }
	    	void					erase(iterator position) { return _rbt.erase(position); }
			void					erase(iterator first, iterator last) { return _rbt.erase(first, last); }
	    	size_type				erase(const key_type& x) { return _rbt.erase(x); }
	    	// void					swap(map& x);
	    	// void					clear();

	    	// observers
	    	// key_compare				key_comp() const;
	    	// value_compare			value_comp() const;

	    	// map operations
	    	iterator				find(const key_type& x) { return _rbt.find(x); }
	    	const_iterator			find(const key_type& x) const { return _rbt.find(x); }
	    	size_type				count(const key_type& x) const { return _rbt.find(x) != _rbt.end(); }
	    	iterator				lower_bound(const key_type& x) { return _rbt.lower_bound(x); }
	    	const_iterator			lower_bound(const key_type& x) const { return _rbt.lower_bound(x); }
	    	iterator				upper_bound(const key_type& x) { return _rbt.upper_bound(x); }
	    	const_iterator			upper_bound(const key_type& x) const { return _rbt.upper_bound(x); }
	    	// pair<iterator, iterator>				equal_range(const key_type& x) { return _rbt.equal_range(x); }
	    	// pair<const_iterator, const_iterator>	equal_range(const key_type& x) const { return _rbt.equal_range(x); }
	};
 
	// swap
	template<class Key, class T, class Compare, class Allocator>
		void	swap(map<Key, T, Compare, Allocator>& x,
	    			 map<Key, T, Compare, Allocator>& y) { std::swap(x, y); }

	// template<class Key, class T, class Compare, class Allocator>
	// 	bool	operator== (const map<Key, T, Compare, Allocator>& x,
	//                 		const map<Key, T, Compare, Allocator>& y);
}

#endif