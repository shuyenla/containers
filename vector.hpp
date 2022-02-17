#ifndef _VECTOR_H_
# define _VECTOR_H_

#include <memory>
#include <cstddef>
#include <algorithm>

namespace ft {
  template<class T, class Allocator = std::allocator<T> >
  class vector {


  public:
    // types
    typedef T 														value_type;
    typedef Allocator 												allocator_type;
    typedef typename allocator_type::pointer						pointer;
    typedef typename allocator_type::const_pointer					const_pointer;
    typedef value_type& 											reference;
    typedef const value_type&										const_reference;
    typedef size_t													size_type;
    typedef size_t						 							difference_type;
    // typedef std::iterator<T> 											iterator;
    // typedef std::iterator<T>									const_iterator;
    // typedef std::reverse_iterator<std::iterator<T> >					reverse_iterator;
    // typedef std::reverse_iterator<std::const_iterator<T> >				const_reverse_iterator;
 
	private:

		value_type		*_ptr;
		size_type		_size;
		size_type		_cap;
		allocator_type	_allocator;

	public:

    // construct/copy/destroy
    explicit vector (const allocator_type& alloc = allocator_type())
	{

	}

	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : allocator(alloc)
	{
	
		_ptr = allocator.allocate(n);
		
		size_type i = 0;
		while (i < n)
		{
			allocator.construct(_ptr + i, val);
			i++;
		}
		_size = n;
		_cap = n;

	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	{

	}

	vector (const vector& x)
	{

	}

    ~vector()
	{
		delete _ptr;
	}

    vector& operator=(const vector& x)
	{
		if (this != &x)
		{
			ptr = ;
		}
		return *this;
	}

    template<class InputIt>
      void assign(InputIt first, InputIt last)
	  {

	  }
	
    void assign(size_type n, const T& u)
	{

	}

    allocator_type get_allocator() const
	{
		return _allocator;
	}
 
    // iterators
    // iterator               begin();
    // const_iterator         begin() const;
    // iterator               end();
    // const_iterator         end() const;
    // reverse_iterator       rbegin();
    // const_reverse_iterator rbegin() const;
    // reverse_iterator       rend();
    // const_reverse_iterator rend() const;
 
    // capacity
    bool		empty() const
	{
		return (_size == 0 ? 1 : 0);
	}

    size_type	size() const
	{
		return _size;
	}
	
    size_type	max_size() const
	{
		return allocator.max_size();
	}
	
    size_type	capacity() const
	{
		return _cap;
	}

    void resize(size_type n, value_type val = value_type())
	{
		size_type i;
		if (n <= _size)
			i = n;
		else
			i = _size;
		while (i < n)
		{
			push_back(val);
			i++;
		}
	}
	
    void     	reserve(size_type n)
	{
		if (n > _cap)
		{
			size_type c = 0;
			while (pow(c, 2) < n)
				i = pow(c, 2);
			value_type *tmp = allocator.allocate(c);
			_cap = c;
			size_type i = 0;
			while (i < _size)
			{
				allocator.construct(_tmp + i, _ptr[i]);
				i++;
			}
			allocator.destroy(_ptr);
			_ptr = _tmp;
		}
	}
	
 
    // element access
    reference       operator[](size_type n)
	{
		
	}
	
    const_reference operator[](size_type n) const
	{
		
	}
	
    const_reference at(size_type n) const
	{
		
	}
	
    reference       at(size_type n)
	{
		
	}
	
    reference       front()
	{
		
	}
	
	const_reference front() const
	{
		
	}
	
    reference       back()
	{
		
	}
	
    const_reference back() const
	{
		
	}
	
 
    // modifiers
    void push_back(const value_type& val);
	{
		reserve(_size + 1);
		allocator.construct(_ptr + _size, val);
		_size++;
	}
	
    void pop_back()
	{
		_ptr[_size - 1] = 0;
		_size--;
	}
	
   	// iterator insert(const_iterator position, const T& x);
    // iterator insert(const_iterator position, T&& x);
    // iterator insert(const_iterator position, size_type n, const T& x);
    // template<class InputIt>
    //   iterator insert(const_iterator position,
                                // InputIt first, InputIt last);
    // iterator insert(const_iterator position, initializer_list<T> il);
    // iterator erase(const_iterator position);
    // iterator erase(const_iterator first, const_iterator last);
    void     swap(vector&)
	{
		
	}
	
    void     clear()
	{
		while (_size > 0)
		{
			_ptr[_size] = 0;
			_size--;
		}
	}
	
  };
 
  // swap
  template<class T, class Allocator>
    void swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
	{
		
	}
	
}

#endif