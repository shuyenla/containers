#pragma once

#include "rbt_iterator.hpp"
namespace ft {

	template<class rbt_iterator>
	class rbt_reverse_iterator
	{
		public:
			typedef rbt_iterator                            	                	iterator;
			typedef rbt_reverse_iterator											reverse_iterator;
			typedef typename ft::iterator_traits<rbt_iterator>::iterator_category   iterator_category;
			typedef typename ft::iterator_traits<rbt_iterator>::value_type          value_type;
			typedef typename ft::iterator_traits<rbt_iterator>::difference_type     difference_type;
			typedef typename ft::iterator_traits<rbt_iterator>::reference           reference;
			typedef typename ft::iterator_traits<rbt_iterator>::pointer             pointer;		
			typedef typename iterator::const_iterator								const_iterator;
			typedef typename iterator::nodePtr										nodePtr;
			typedef typename iterator::cmp											Compare;

		protected:
			nodePtr		_rit;
			Compare		_cmp;


		public:
			operator rbt_reverse_iterator<const_iterator>() const
			{ return rbt_reverse_iterator<const_iterator>(iterator(_rit)); }

			rbt_reverse_iterator():_rit() {}
			explicit rbt_reverse_iterator(iterator x):_rit(x.getNode()) {}

			template <class U>
				rbt_reverse_iterator& operator=(const rbt_reverse_iterator<U>& u)
				{
					if (*this != u)
						_rit = u.base();
					return *this;
				}

			iterator base() const { return iterator(_rit); }

			reference operator*() const { return (--base()).operator*(); }
			pointer operator->() const { return (--base()).operator->(); }

			reverse_iterator& operator++()
			{
				if (_rit != _rit->TNULL)
						_rit = __lower_bound(_rit->data.first, *(_rit->root), _cmp);
					else
						_rit = max(*(_rit->root));
				return *this;
			}

			reverse_iterator  operator++(int)
			{
				reverse_iterator rit = *this;
				++(*this);
				return rit;
			}

			reverse_iterator& operator--() { _rit = __upper_bound(_rit->data.first, *(_rit->root), _cmp); return *this; }

			reverse_iterator  operator--(int)
			{
				reverse_iterator rit = *this;
				--(*this);
				return rit;
			}

			friend bool operator==(const reverse_iterator &x, const reverse_iterator &y)
			{ return x._rit == y._rit; }
			friend bool operator!=(const reverse_iterator &x, const reverse_iterator &y)
			{ return !(x._rit == y._rit); }
	};
}