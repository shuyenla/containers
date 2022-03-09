namespace ft {

    template<class value_type, class Compare>
	class value_compare
	{
	    friend class map;
	    protected:
	    	Compare comp;
	    public:
			value_compare(Compare c):comp(c) {}
	    	bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
	};    
}