#ifndef _VECTOR_H_
# define _VECTOR_H_

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


namespace ft {

	
  	template<class T, class Allocator = std::allocator<T> >
  	class vector {

  	public:
    	// types
    	typedef T 												value_type;
    	typedef Allocator 										allocator_type;
    	typedef typename allocator_type::pointer				pointer;
    	typedef typename allocator_type::const_pointer			const_pointer;
    	typedef value_type& 									reference;
    	typedef const value_type&								const_reference;
    	typedef size_t											size_type;
    	typedef size_t						 					difference_type;
    	typedef ft::iterator<T>						 			iterator;
    	typedef ft::iterator<const T>							const_iterator;
    	typedef ft::reverse_iterator<iterator>					reverse_iterator;
    	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	
		private:

			value_type		*_ptr;
			size_type		_size;
			size_type		_cap;
			allocator_type	_allocator;

		public:

    	// construct/copy/destroy
    	explicit vector(const allocator_type& alloc = allocator_type()):_ptr(NULL), _size(0), _cap(0), _allocator(alloc) {
			_ptr = _allocator.allocate(0);
		}

		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc)
		{
			_ptr = _allocator.allocate(n);
			for (size_type i = 0; i < n; i++)
				_allocator.construct(_ptr + i, val);
			_size = n;
			_cap = n;
		}

		template <class InputIt>
		vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const allocator_type& alloc = allocator_type()): _ptr(NULL), _size(0), _cap(0), _allocator(alloc)
		{
			for (; first != last; first++)
				push_back(*first);
		}

		vector(const vector& x)
		{
			_allocator = x.get_allocator();
			_size = x.size();
			_cap = x.capacity();
			_ptr = _allocator.allocate(_cap);
			size_type i = 0;
			for (const_iterator it = x.begin(); it != x.end(); it++, i++)
				_allocator.construct(_ptr + i, *it);
		}

    	~vector() { _allocator.deallocate(_ptr, _cap); }

    	vector& operator=(const vector& x)
		{
			if (this != &x)
			{
				if (_ptr)
					_allocator.deallocate(_ptr, _cap);
				_allocator = x.get_allocator();
				_size = x.size();
				_cap = x.capacity();
				_ptr = _allocator.allocate(_cap);
				size_type i = 0;
				for (const_iterator it = x.begin(); it != x.end(); it++, i++)
					_allocator.construct(_ptr + i, *it);
			}
			return *this;
		}

		template <class InputIt>
    	void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
		{
			size_type n = 0;
			for (InputIt it = first; it != last; it++)
				n++;
			this->resize(n);
			for (size_type n = 0; first != last; first++, n++)
				_ptr[n] = *first;
		}

    	void assign(size_type n, const value_type& val)
		{
			this->resize(n, val);
			for (size_type i = 0; i < n; i++)
				_ptr[i] = val;
		}

    	allocator_type get_allocator() const { return _allocator; }

    	// iterators
    	iterator               begin() { return iterator(_ptr); }
    	const_iterator         begin() const { return const_iterator(_ptr); }
    	iterator               end() { return iterator(_ptr + _size); }
    	const_iterator         end() const { return const_iterator(_ptr + _size); }
    	reverse_iterator       rbegin() { return reverse_iterator(_ptr + _size); }
    	const_reverse_iterator rbegin() const { return reverse_iterator(_ptr + _size); }
    	reverse_iterator       rend() { return reverse_iterator(_ptr); }
    	const_reverse_iterator rend() const { return reverse_iterator(_ptr); }

    	// capacity
    	bool		empty() const { return (_size == 0); }
    	size_type	size() const { return _size; }
    	size_type	max_size() const { return _allocator.max_size(); }
    	size_type	capacity() const { return _cap; }

    	void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				while (n < _size)
					pop_back();
			}
			else
			{
				while (n > _size)
					push_back(val);
			}
		}

    	void     	reserve(size_type n)
		{
			if (n > _cap)
			{
				value_type *tmp = _allocator.allocate(n);
				_cap = n;
				if (_ptr)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(tmp + i, _ptr[i]);
					_allocator.deallocate(_ptr, _cap);
				}
				_ptr = tmp;
			}
		}

    	// element access
    	reference       operator[](size_type n)
		{
			if (n > _size)
				throw(std::out_of_range("out_of_range"));
			return _ptr[n];
		}

    	const_reference operator[](size_type n) const
		{
			if (n > _size)
				throw(std::out_of_range("out_of_range"));
			return _ptr[n];
		}

    	const_reference at(size_type n) const
		{
			if (n > _size)
				throw(std::out_of_range("out_of_range"));
			return _ptr[n];
		}

    	reference       at(size_type n)
		{
			if (n > _size)
				throw(std::out_of_range("out_of_range"));
			return _ptr[n];
		}

    	reference       front() { return _ptr[0]; }
		const_reference front() const { return _ptr[0]; }
    	reference       back() { return _ptr[_size - 1]; }
    	const_reference back() const { return _ptr[_size - 1]; }
	
    	// modifiers
    	void push_back(const value_type& val)
		{
			reserve(_size + 1);
			_allocator.construct(_ptr + _size, val);
			_size++;
		}

    	void pop_back()
		{
			_allocator.destroy(_ptr + _size);
			_size--;
		}

   		iterator insert(const_iterator position, const T& x)
		{
			size_type pos = 0;
			for (const_iterator cit = this->begin(); cit != position; cit++)
				pos++;
			reserve(_size + 1);
			for (iterator it = this->begin() + pos, ite = this->end(); it != ite; --ite)
				*(ite) = *(ite - 1);
			_size++;
			*(this->begin() + pos) = x;
			return this->begin() + pos;
		}

    	iterator insert(const_iterator position, size_type n, const T& x)
		{
			size_type pos = 0;
			for (const_iterator cit = this->begin(); cit != position; cit++)
				pos++;
			reserve(_size + n);
			for (iterator it = this->begin() + pos, ite = this->end(); it != ite; it++)
				*(it + n) = *it;
			size_type n_ = n;
			_size += n;
			for (iterator it = this->begin() + pos; n_ > 0; it++, n_--)
				*it = x;
			return this->begin() + pos;
		}

    	template<class InputIt>
    	iterator insert(const_iterator position,
    	typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
		{
			size_type n = 0;
			size_type pos = 0;
			for (const_iterator cit = this->begin(); cit != position; cit++)
				pos++;
			for (iterator it = first; it != last; it++)
				n++;
			reserve(_size + n);
			for (iterator it = this->begin() + pos, ite = this->end(); it != ite; it++)
				*(it + n) = *it;
			_size += n;
			for (iterator it = this->begin() + pos; first != last; it++, first++)
				*it = *first;
			return this->begin() + pos;
		}

    	iterator erase(iterator position)
		{
			size_type pos = 0;
			for (iterator it = this->begin(); it != position; it++)
				pos++;
			_allocator.destroy(_ptr + pos);
			for (iterator it = this->begin() + pos; it != this->end(); it++)
				*(it) = *(it + 1);
			_size--;
			return iterator(_ptr + pos);
		}

    	iterator erase(iterator first, iterator last)
		{
			size_type pos = 0;
			size_type n = 0;
			for (iterator cit = this->begin(); cit != first; cit++)
				pos++;
			for (iterator cit = first; cit != last; cit++)
				n++;
			if (n > 0)
			{
				for (size_type n_ = n; n_ > 0; n_--, pos++)
					_allocator.destroy(_ptr + pos);
				_size -= n;
				if (iterator(_ptr + pos) == this->end())
					return this->end();
				return (iterator(_ptr + pos));
			}
			return last;
		}

    	void     swap(vector& x)
		{
			value_type		*_tmpPtr = _ptr;
			size_type		_tmpSize = _size;
			size_type		_tmpCap = _cap;
			allocator_type	_tmpAllocator = _allocator;

			_ptr = x._ptr;
			_size = x._size;
			_cap = x._cap;
			_allocator = x._allocator;
			x._ptr = _tmpPtr;
			x._size = _tmpSize;
			x._cap = _tmpCap;
			x._allocator = _tmpAllocator;
		}

    	void     clear()
		{
			while (_size > 0)
				erase(iterator(_ptr + _size));
		}
  	};	
	
  		//	 swap
  		template<class T, class Allocator>
    	void swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
		{
			T				*_tmpPtr = x._ptr;
			size_t			_tmpSize = x.size();
			size_t			_tmpCap = x.cap();
			Allocator		_tmpAllocator = x.get_allocator();

			x._ptr = y._ptr;
			x._size = y.size();
			x._cap = y.cap();
			x._allocator = y.get_allocator();
			y._ptr = _tmpPtr;
			y._size = _tmpSize;
			y._cap = _tmpCap;
			y._allocator = _tmpAllocator;
		}

		// overload operator
	    template <class T, class Allocator>
	        bool operator==(const vector<T,Allocator>& x,const vector<T,Allocator>& y)
			{ return equal(x.begin(), x.end(), y.begin()); }
	    template <class T, class Allocator>
	        bool operator< (const vector<T,Allocator>& x,const vector<T,Allocator>& y)
			{ return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
	    template <class T, class Allocator>
	        bool operator!=(const vector<T,Allocator>& x,const vector<T,Allocator>& y)
			{ return !equal(x.begin(), x.end(), y.begin()); }
	    template <class T, class Allocator>
	        bool operator> (const vector<T,Allocator>& x,const vector<T,Allocator>& y)
			{ return !lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
	    template <class T, class Allocator>
	        bool operator>=(const vector<T,Allocator>& x,const vector<T,Allocator>& y)
			{ return !lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
	    template <class T, class Allocator>
	        bool operator<=(const vector<T,Allocator>& x,const vector<T,Allocator>& y)
			{ return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

	    template <class Allocator> class vector<bool,Allocator>;

	
}

#endif