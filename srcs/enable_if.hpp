#pragma once
namespace ft {

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class T>
	struct is_integral {
	    const static bool value = false;
	};

	template<> struct is_integral<int> { const static bool value = true; };
	template<> struct is_integral<bool> { const static bool value = true; };
	template<> struct is_integral<char> { const static bool value = true; };
	template<> struct is_integral<wchar_t> { const static bool value = true; };
	template<> struct is_integral<short> { const static bool value = true; };
	template<> struct is_integral<long> { const static bool value = true; };
	template<> struct is_integral<long long> { const static bool value = true; };
}
