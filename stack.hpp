namespace ft {

  template<class T, class Container = deque<T>> class stack
  {
	public:
	   typedef typename Container::value_type			value_type;
	   typedef typename Container::reference			reference;
	   typedef typename Container::const_reference		const_reference;
	   typedef typename Container::size_type			size_type;
	   typedef Container								container_type;

	protected:
	   Container c;

	public:
		stack() : stack(Container()) {}
		explicit stack(const Container& cont = Container());
		~stack();
		bool empty() const { return c.empty(); }
		size_type size()  const             { return c.size(); }
		reference         top()             { return c.back(); }
		const_reference   top() const       { return c.back(); }
		void push(const value_type& x)      { c.push_back(x); }
		void pop()                          { c.pop_back(); }
	 };
	// template<class Container>
    // stack(Container) -> stack<typename Container::value_type, Container>;
 
	// template<class InputIt>
	// stack(InputIt, InputIt) -> stack</*iter-value-type*/<InputIt>>;

	// template<class Container, class Allocator>
	// stack(Container, Allocator) -> stack<typename Container::value_type, Container>;

	// template<class InputIt, class Allocator>
	// stack(InputIt, InputIt, Allocator)
	//     -> stack</*iter-value-type*/<InputIt>, deque</*iter-value-type*/<InputIt>,
	//              Allocator>>;

	// template<class T, class Container, class Alloc>
    // struct uses_allocator<stack<T, Container>, Alloc>
    //   : uses_allocator<Container, Alloc>::type { };
  }
 
  template<class T, class Container>
    bool operator==(const stack<T, Container>& x, const stack<T, Container>& y);
  template<class T, class Container>
    bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y);
  template<class T, class Container>
    bool operator< (const stack<T, Container>& x, const stack<T, Container>& y);
  template<class T, class Container>
    bool operator> (const stack<T, Container>& x, const stack<T, Container>& y);
  template<class T, class Container>
    bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y);
  template<class T, class Container>
    bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y);

}