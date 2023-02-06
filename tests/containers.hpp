#ifndef FT_CONTAINERS_HPP
# define FT_CONTAINERS_HPP

#include <iostream>

#ifdef _STL
	#include <vector>
	#include <utility>
	#include <map>
	#include <stack>
	#include <set>
	namespace ft = std;
	#define VERSION "stl"
#else
	#include <vector.hpp>
	#include <pair.hpp>
	#include <map.hpp>
	#include <stack.hpp>
	#include <set.hpp>
	#define VERSION "ft"
#endif

void test_vector(void);
void test_pair(void);
void test_map(void);
void test_stack(void);
void test_set(void);

#endif