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

namespace ft {

	template<class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<Key, T> > >
    class map
	{
		public:

	    	typedef Key																			key_type;
	    	typedef T																			mapped_type;
	    	typedef pair<Key, T>																value_type;
	    	typedef Compare																		key_compare;
	    	typedef Allocator																	allocator_type;

			typedef node<value_type>															node_type;
			typedef node_type*																	nodePtr;
	    	typedef ft::rbt_iterator<value_type, mapped_type, nodePtr, Compare>					iterator;
	   		typedef ft::rbt_iterator<const value_type, const mapped_type, nodePtr, Compare>		const_iterator;
	    	typedef ft::rbt_reverse_iterator<iterator>											reverse_iterator;
	    	typedef ft::rbt_reverse_iterator<const_iterator>									const_reverse_iterator;

			class value_compare
			{
	    		friend class map;
	    		protected:
	    			Compare comp;
	    		public:
					value_compare(Compare c):comp(c) {}
	    			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
	    	};

		private:

			typedef RedBlackTree
			<value_type, key_type, mapped_type ,Compare, value_compare, ft::map<Key, T, Compare> >		tree_type;

		public:
 			typedef typename allocator_type::pointer											pointer;
	    	typedef typename allocator_type::const_pointer										const_pointer;
	    	typedef value_type&																	reference;
	    	typedef const value_type& 															const_reference;
	    	typedef typename tree_type::size_type 												size_type;
	    	typedef typename tree_type::difference_type 										difference_type;

		private:

			tree_type		*_rbt;
			value_compare	_vc;
			allocator_type	_a;

		public:

	    	// construct/copy/destroy
	    	map():_vc(Compare()), _a(Allocator()) {_rbt = new tree_type();}
	    	explicit map(const Compare& comp, const Allocator& = Allocator()):_vc(comp), _a(Allocator()) {_rbt = new tree_type();}
	    	template<class InputIt>
	    		map(InputIt first, InputIt last,
	    	    const Compare& comp = Compare(), const Allocator& = Allocator()): _vc(comp), _a(Allocator()) { _rbt = new tree_type();insert(first, last);}
	    	map(const map& x): _vc(x._vc), _a(x._a) { _rbt = new tree_type();insert(x.begin(), x.end()); }
	    	~map() {delete _rbt;}
	    	map& operator=(const map& x)
			{
				if (this != &x)
				{
					_rbt->clear();
					_vc = x._vc;
					_a = x._a;
					_rbt->insert(x.begin(), x.end());
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

	    	// element access
	    	mapped_type& 			operator[](const key_type& x) { return _rbt->operator[](x).second; }
	    	mapped_type&			at(const key_type& x) { return _rbt->at(x); }
	    	const mapped_type&		at(const key_type& x) const { return _rbt->at(x); }

	    	// modifiers
	    	pair<iterator, bool>	insert(const value_type& x) { return _rbt->insert(x); }
	    	iterator				insert(const_iterator position, const value_type& x) { return _rbt->insert(position, x); }
	    	template<class InputIt>
	    		void				insert(InputIt first, InputIt last) { return _rbt->insert(first, last); }
	    	void					erase(iterator position) { return _rbt->erase(position); }
			void					erase(iterator first, iterator last) { return _rbt->erase(first, last); }
	    	size_type				erase(const key_type& x) { return _rbt->erase(x); }
	    	void					swap(map& x)
			{
				std::swap(_rbt, x._rbt);
				std::swap(_vc, x._vc);
				std::swap(_a, x._a);
			}
	    	void					clear() { _rbt->clear();}

	    	// observers
	    	key_compare				key_comp() const { return _vc.comp; }
	    	value_compare			value_comp() const { return _vc; }

	    	// map operations
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
	template<class Key, class T, class Compare, class Allocator>
		void	swap(ft::map<Key, T, Compare, Allocator>& x,
	    			 ft::map<Key, T, Compare, Allocator>& y) { x.swap(y); }

	// overload operator
	template< class Key, class T, class Compare, class Alloc >
		bool operator==(const ft::map<Key,T,Compare,Alloc>& x,
                		const ft::map<Key,T,Compare,Alloc>& y)
		{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator!=(const ft::map<Key,T,Compare,Alloc>& x,
                		const ft::map<Key,T,Compare,Alloc>& y)
		{ return !(x == y); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator< (const ft::map<Key,T,Compare,Alloc>& x,
                		const ft::map<Key,T,Compare,Alloc>& y)
		{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator<=(const ft::map<Key,T,Compare,Alloc>& x,
                 		const ft::map<Key,T,Compare,Alloc>& y)
		{ return x < y || x == y; }
	template< class Key, class T, class Compare, class Alloc >
		bool operator> (const ft::map<Key,T,Compare,Alloc>& x,
        				const ft::map<Key,T,Compare,Alloc>& y)
		{ return !(x <= y); }
	template< class Key, class T, class Compare, class Alloc >
		bool operator>=(const ft::map<Key,T,Compare,Alloc>& x,
                		const ft::map<Key,T,Compare,Alloc>& y)
		{ return !(x < y) || x == y; }
}
