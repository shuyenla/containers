#pragma once

#include "set_iterator.hpp"
namespace ft {

	template<class set_iterator>
	class set_reverse_iterator: public class rbt_reverse_iterator
	{
		public:

			typedef set_iterator                            	                iterator;
			typedef set_reverse_iterator										reverse_iterator;
			typedef typename ft::iterator_traits<set_iterator>::iterator_category   iterator_category;
			typedef typename ft::iterator_traits<set_iterator>::value_type          value_type;
			typedef typename ft::iterator_traits<set_iterator>::difference_type     difference_type;
			typedef typename ft::iterator_traits<set_iterator>::reference           reference;
			typedef typename ft::iterator_traits<set_iterator>::pointer             pointer;		
			typedef typename iterator::const_iterator							const_iterator;
			typedef typename iterator::nodePtr									nodePtr;
			typedef typename iterator::cmp										Compare;

		protected:

			nodePtr		_rit;

		private:
			Compare		_cmp;


		public:

			operator set_reverse_iterator<const_iterator>() const
			{ return set_reverse_iterator<const_iterator>(iterator(_rit)); }

			set_reverse_iterator():_rit(NULL) {}
			
			explicit set_reverse_iterator(iterator x):_rit(x.getNode()) {}

			template <class U>
				set_reverse_iterator& operator=(const set_reverse_iterator<U>& u) {
					if (*this != u)
						_rit = u.base();
					return *this;
				}

			iterator base() const { return iterator(_rit); }

			reference operator*() const { return (--base()).operator*(); }
			pointer operator->() const { return (--base()).operator->(); }
			reverse_iterator& operator++() {
				if (_rit != _rit->TNULL)
						_rit = __lower_bound(_rit->data.first, *(_rit->root), _cmp);
					else
						_rit = max(*(_rit->root));
				return *this; }
			reverse_iterator  operator++(int) {
				reverse_iterator rit = *this;
				++(*this);
				return rit; }
			reverse_iterator& operator--() { _rit = __upper_bound(_rit->data.first, *(_rit->root), _cmp); return *this; }
			reverse_iterator  operator--(int) {
				reverse_iterator rit = *this;
				--(*this);
				return rit; }

			friend bool operator==(const reverse_iterator &x, const reverse_iterator &y)
			{ return x._rit == y._rit; }
			friend bool operator!=(const reverse_iterator &x, const reverse_iterator &y)
			{ return !(x._rit == y._rit); }

	};

}