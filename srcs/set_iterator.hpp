#pragma once

# include "node.hpp"
# include "tree.hpp"
# include "iterator_traits.hpp"
# include "rbt_iterator.hpp"

namespace ft {

	template<class P, class Mapped, class nodePointer, class Compare>
	class set_iterator
	{
		public:
			typedef std::bidirectional_iterator_tag 								iterator_category;
			typedef P           													value_type;
			typedef Mapped           												mapped_type;
			typedef nodePointer														nodePtr;
			typedef	Compare															cmp;
			typedef ptrdiff_t    													difference_type;
			typedef mapped_type*		     										pointer;
			typedef mapped_type&			   										reference;
			typedef ft::set_iterator<P, const mapped_type, nodePtr, cmp>			iterator;
			typedef ft::set_iterator<P, const mapped_type, nodePtr, cmp>			const_iterator;

			operator set_iterator<P, const Mapped, nodePtr, cmp>() const
			{ return set_iterator<P, const Mapped, nodePtr, cmp>(_it); }

		protected:
			nodePtr		_it;
			cmp			_cmp;

		public:
			set_iterator():_it(), _cmp(Compare()) {}
			explicit set_iterator(nodePtr n):_it(n), _cmp(Compare()) {}
			set_iterator(const iterator &x):_it(x._it), _cmp(x._cmp) {}

			reference operator*() const { return _it->data.first; }
			pointer operator->() const { return &(_it->data.first); }

			iterator& operator++()
			{
				_it = __upper_bound(_it->data.first, *(_it->root), _cmp);
				return *this;
			}

			iterator  operator++(int)
			{
				iterator it = *this;
				++(*this);
				return it;
			}

			iterator& operator--()
			{
				if (_it != _it->TNULL)
					_it = __lower_bound(_it->data.first, *(_it->root), _cmp);
				else
					_it = max(*(_it->root));
				return *this;
			}

			iterator  operator--(int)
			{
				iterator it = *this;
				--(*this);
				return it;
			}

			nodePtr		getNode() const { return _it; }

			friend bool operator==(const iterator &x, const iterator &y)
			{ return x._it == y._it; }
			friend bool operator!=(const iterator &x, const iterator &y)
			{ return x._it != y._it; }
	};
}
