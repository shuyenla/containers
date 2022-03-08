
	    	typedef Key																			key_type;
	    	typedef T																			mapped_type;
	    	typedef pair<Key, T>																value_type;
	    	typedef Compare																		key_compare;
	    	typedef Allocator																	allocator_type;

			typedef node<P>																		node_type;
			typedef node_type*																	nodePtr;
	    	typedef ft::rbt_iterator<value_type, mapped_type, nodePtr, Compare>					iterator;
	   		typedef ft::rbt_iterator<const value_type, const mapped_type, nodePtr, Compare>		const_iterator;
	    	typedef ft::rbt_reverse_iterator<iterator>											reverse_iterator;
	    	typedef ft::rbt_reverse_iterator<const_iterator>									const_reverse_iterator;