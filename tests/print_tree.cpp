#include "containers.hpp"

int main(void)
{
	ft::map<int, int> notEmptyMap;

	notEmptyMap.insert(ft::make_pair(5, 1));
	notEmptyMap.insert(ft::make_pair(6, 1));
	notEmptyMap.insert(ft::make_pair(4, 1));
	notEmptyMap.insert(ft::make_pair(8, 1));
	notEmptyMap.insert(ft::make_pair(9, 1));
	notEmptyMap.insert(ft::make_pair(10, 1));
	notEmptyMap.insert(ft::make_pair(10, 1));

	notEmptyMap.print_tree();

	ft::map<std::string, std::string> notEmptyMap3;

	notEmptyMap3.insert(ft::make_pair("a", "anis"));
	notEmptyMap3.insert(ft::make_pair("b", "banana"));
	notEmptyMap3.insert(ft::make_pair("c", "carambola"));
	notEmptyMap3.insert(ft::make_pair("d", "damasco"));
	notEmptyMap3.insert(ft::make_pair("h", "cambuci"));
	notEmptyMap3.insert(ft::make_pair("i", "caju"));
	notEmptyMap3.insert(ft::make_pair("k", "caja"));
	notEmptyMap3.insert(ft::make_pair("f", "favo"));
	notEmptyMap3.insert(ft::make_pair("g", "goiaba"));
	notEmptyMap3.insert(ft::make_pair("j", "jaca"));

	notEmptyMap3.print_tree();

	ft::map<double, int> notEmptyMap4;

	notEmptyMap4.insert(ft::make_pair(520.2, 1));
	notEmptyMap4.insert(ft::make_pair(60.4, 1));
	notEmptyMap4.insert(ft::make_pair(444, 1));
	notEmptyMap4.insert(ft::make_pair(8.5, 1));
	notEmptyMap4.insert(ft::make_pair(98.6, 1));
	notEmptyMap4.insert(ft::make_pair(10.1, 1));
	notEmptyMap4.insert(ft::make_pair(10.3, 1));

	notEmptyMap4.print_tree();

}
