#ifndef _ENABLE_IF_H_
# define _ENABLE_IF_H_

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type;  };

	template<class T>
	struct is_integral {
	    const static bool value = false;
	};
	template<>
	struct is_integral<int> {
		const static bool value = true;
	};
}

#endif