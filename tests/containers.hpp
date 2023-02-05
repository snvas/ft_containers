#ifndef FT_CONTAINERS_HPP
# define FT_CONTAINERS_HPP

#include <iostream>

#ifdef _STL
	#include <vector>
	namespace ft = std;
	#define VERSION "stl"
#else
	#include <vector.hpp>
	#define VERSION "ft"
#endif

void test_vector(void);

#endif