#include "containers.hpp"

template<class T1, class T2>
void print_map_values(ft::map<T1, T2> &map, std::string str)
{
	typename ft::map<T1, T2>::iterator it;
	it = map.begin();
	std::cout << "- " << str << std::endl;
	while (it != map.end()) {
		std::cout << "pair"<< "[" << it->first << ", " << it->second << "] \n";
		it++;
	}
	std::cout << "size: " << map.size() << std::endl;
}

template<typename T, typename U>
static std::ostream& operator<<(std::ostream& out, const ft::pair<T, U>&p){
	out << "  pair[" << p.first << ", " << p.second << "]";
	return out;
}

template<typename T, typename U, typename V>
static std::ostream& operator<<(std::ostream& out, ft::map<T, U, V>& map){
	typename ft::map<T, U, V>::iterator it = map.begin();
	while (it != map.end()){
		out << *it << std::endl;
		++it;
	}
	return out;
}

void test_map(void)
{
	std::cout << "====================================" << std::endl;
	std::cout << "                 map                " << std::endl;
	std::cout << "====================================" << std::endl;
	/*	Constructors*/
	std::cout << "[ CONSTRUCTORS ]" << std::endl;
	std::cout << "test map default constructor" << std::endl;
	ft::map<int, int> int_map;
	ft::map<std::string, int> string_map;
	std::cout << "int_map.size() - " << int_map.size() << std::endl;
	std::cout << "string_map.size() - " << string_map.size() << std::endl;
	
	ft::map<int, int> int_map2((std::less<int>()));
	ft::map<std::string, int> string_map2((std::less<std::string>()), std::allocator<ft::pair<std::string, int> >());
	std::cout << "int_map2.size() - " << int_map2.size() << std::endl;
	std::cout << "string_map2.size() - " << string_map2.size() << std::endl;
	std::cout << "at least it compile" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	ft::map<int, int> emptyMap;
	ft::map<int, int> notEmptyMap;
	ft::pair<ft::map<int, int>::iterator, bool> insert_pair1;
	ft::pair<ft::map<int, int>::iterator, bool> insert_pair2;

	notEmptyMap.insert(ft::make_pair(5, 1));
	notEmptyMap.insert(ft::make_pair(6, 1));
	notEmptyMap.insert(ft::make_pair(4, 1));
	notEmptyMap.insert(ft::make_pair(8, 1));
	notEmptyMap.insert(ft::make_pair(9, 1));
	notEmptyMap.insert(ft::make_pair(10, 1));
	notEmptyMap.insert(ft::make_pair(10, 1));
	insert_pair1 = notEmptyMap.insert(ft::make_pair(1, 1));
	insert_pair2 = notEmptyMap.insert(ft::make_pair(15, 1));
	std::cout << "notEmptyMap constructor\n" << notEmptyMap << std::endl;
	std::cout << "------------------------------------" << std::endl;
		
	/* Iterators*/
	std::cout << "[ ITERATORS ]" <<std::endl;
	ft::map<int, int>::iterator it_begin(insert_pair1.first);
	ft::map<int, int>::iterator it_last = insert_pair2.first;
	ft::map<int, int>::iterator it;
	std::cout << "assigment operator" << std::endl;
	it = it_begin;
	std::cout << "it = it_begin: " << it->first << std::endl;
	it = it_last;
	std::cout << "it = it_last: " << it->first << std::endl;

	std::cout << "\nequality / inequality operators" << std::endl;
	std::cout << "(it != it_begin): " << (it != it_begin) << std::endl;
	std::cout << "(it == it_begin): " << (it == it_begin) << std::endl;
	std::cout << "(it != it_last): " << (it != it_last) << std::endl;
	std::cout << "(it == it_last): " << (it == it_last) << std::endl;
	std::cout << "(it_begin != it_last): " << (it_begin != it_last) << std::endl;
	std::cout << "(it_begin == it_last): " << (it_begin == it_last) << std::endl;

	std::cout << "\ndereference" << std::endl;
	std::cout << "it->first: " << it->first << std::endl;
	std::cout << "it_begin->fisrt: " << it_begin->first << std::endl;
	std::cout << "it_last->fisrt: " << it_last->first << std::endl;
	ft::pair<int, int> my_pair = *it;
	std::cout << "*it: " << my_pair.first << std::endl;
	my_pair = *it_begin;
	std::cout << "*it_begin: " << my_pair.first << std::endl;
	my_pair = *it_last;
	std::cout << "*it_last: " << my_pair.first << std::endl;
	
	std::cout << "\ndereferenced as an lvalue" << std::endl;
	ft::map<int, int>::iterator it2 = it;
	it2->second = 20;
	std::cout << "it2->first: " << it2->first << std::endl;
	std::cout << "it2->second: " << it2->second << std::endl;

	std::cout << "\nincrement and decrement" << std::endl;
	it = it_begin;
	std::cout << "post increment: ";
	while (it != it_last) {
		std::cout << it->first << ", ";
		it++;
	}
	std::cout << it->first << std::endl;
	std::cout << "post decrement: ";
	while (it != it_begin) {
		std::cout << it->first << ", ";
		it--;
	}
	std::cout << it->first << std::endl;
	std::cout << "pre increment: ";
	std::cout << it->first;
	while (it != it_last) {
		it++;
		std::cout << ", " << it->first;
	}
	std::cout << std::endl;
	std::cout << "pre decrement: ";
	std::cout << it->first;
	while (it != it_begin) {
		it--;
		std::cout << ", " << it->first;
	}
	std::cout << std::endl;
	std::cout << "post dereferenced increment: ";
	while (it != it_last) {
		std::cout << it->first << ", ";
		*it++;
	}
	std::cout << it->first << std::endl;
	std::cout << "post dereferenced decrement: ";
	while (it != it_begin) {
		std::cout << it->first << ", ";
		*it--;
	}
	std::cout << it->first << std::endl;
	std::cout << "const iterator" << std::endl;
	const ft::map<int, int> const_map(notEmptyMap);
	ft::map<int, int>::const_iterator const_it = const_map.begin();
	std::cout << const_it->first << std::endl;
	const_it = notEmptyMap.begin();
	const_it++;
	std::cout << const_it->first << std::endl;
	std::cout << "------------------------------------" << std::endl;
	/*	Constructors that need iterators*/
	std::cout << "[ Constructors that need iterators ]" << std::endl;
	std::cout << "original container: ";
	it = notEmptyMap.begin();
	while (it != notEmptyMap.end()) {
		std::cout << it->first << ", ";
		it++;
	}
	std::cout << std::endl;
	ft::map<int, int> rangeMap(notEmptyMap.begin(), notEmptyMap.end());
	std::cout << "range constructor: ";
	it = rangeMap.begin();
	while (it != rangeMap.end()) {
		std::cout << it->first << ", ";
		it++;
	}
	std::cout << std::endl;

	ft::vector<ft::pair<int, int> > int_vec;
	for (int i = 0; i < 5; i++){
		int_vec.push_back(ft::make_pair(5 - i, i));
	}
	ft::map<int, int> int_mapInt(int_vec.begin(), int_vec.end());
	print_map_values(int_mapInt, "map: ");
	std::cout << "------------------------------------" << std::endl;

	std::cout << "[ test map assignment operator ]" << std::endl;
	ft::map<std::string, int> empty_map;
	ft::map<std::string, int, std::less<std::string> > strint_map;

	strint_map.insert(ft::make_pair("mathematics", 92));
	strint_map.insert(ft::make_pair("languages", 52));
	strint_map.insert(ft::make_pair("physics", 82));
	strint_map.insert(ft::make_pair("logic", 72));
	strint_map.insert(ft::make_pair("history", 42));
	strint_map.insert(ft::make_pair("science", 32));

	ft::map<std::string, int, std::less<std::string> > map_copy;
	ft::map<std::string, int> empty_copy;
	map_copy = strint_map;
	empty_copy = empty_map;

	std::cout << "the empty copy:\n" << empty_copy << std::endl;
	std::cout << "the copy:\n" << map_copy << std::endl;
	std::cout << "the copy size:\n" << map_copy.size() << std::endl;
	std::cout << "------------------------------------" << std::endl;

	std::cout << "[ copy constructor ]: ";
	ft::map<int, int> copyMap(notEmptyMap);
	it = copyMap.begin();
	while (it != copyMap.end()) {
		std::cout << it->first << ", ";
		it++;
	}
	std::cout << std::endl;

	/*Iterator Methods */
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Iterator Methods ]" << std::endl;
	it = copyMap.begin();
	std::cout << "copyMap.begin(): " << it->first << std::endl;

	ft::map<int, int>::iterator it_end = copyMap.end();
	it_end--;
	std::cout << "copyMap.end()--: " << it_end->first << std::endl;
	it_end++;
	std::cout << "accessing copyMap using begin and end: ";
	it = copyMap.begin();
	while (it != it_end) {
		std::cout << it->first << ", ";
		it++;
	}
	std::cout << std::endl;
	ft::map<int, int> const_it_map(copyMap.begin(), copyMap.end());
	ft::map<int, int>::const_iterator const_begin = const_it_map.begin();
	std::cout << "const copyMap.begin(): " << const_begin->first << std::endl;
	ft::map<int, int>::const_iterator const_end = const_it_map.end();
	const_end--;
	std::cout << "const copyMap.end()--: " << const_end->first << std::endl;
	const_end++;
	std::cout << "accessing const_it_map using begin and end: ";
	while (const_begin != const_end) {
		std::cout << const_begin->first << ", ";
		const_begin++;
	}
	std::cout << std::endl;
	ft::map<int, int>::reverse_iterator reverse_it = copyMap.rbegin();
	std::cout << "copyMap.rbegin(): " << reverse_it->first << std::endl;
	reverse_it = copyMap.rend();
	reverse_it--;
	std::cout << "copyMap.rend()--: " << reverse_it->first << std::endl;

	std::cout << "accessing copyMap using reverse begin and end: ";
	reverse_it = copyMap.rbegin();
	while (reverse_it != copyMap.rend()) {
		std::cout << reverse_it->first << ", ";
		reverse_it++;
	}
	std::cout << std::endl;

	ft::map<int, int>::const_reverse_iterator creverse_it = copyMap.rbegin();
	std::cout << "const copyMap.rbegin(): " << creverse_it->first << std::endl;

	creverse_it = copyMap.rend();
	creverse_it--;
	std::cout << "const copyMap.rend(): " << creverse_it->first << std::endl;

	std::cout << "accessing copyMap using const_reverse begin and end: ";
	creverse_it = copyMap.rbegin();
	while (creverse_it != copyMap.rend()) {
		std::cout << creverse_it->first << ", ";
		creverse_it++;
	}
	std::cout << std::endl;

	/*
	**	Capacity Methods
	*/
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Capacity Methods ]" << std::endl;
	std::cout << "empty" << std::endl;
	std::cout << "emptyMap.empty(): " << emptyMap.empty() << std::endl;
	std::cout << "notEmptyMap.empty(): " << notEmptyMap.empty() << std::endl;
	std::cout << "copyMap.empty(): " << copyMap.empty() << std::endl;
	std::cout << "rangeMap.empty(): " << rangeMap.empty() << std::endl;

	emptyMap.insert(ft::make_pair(1, 1));
	std::cout << "emptyMap.empty() after insert(1, 1): " << emptyMap.empty() << std::endl;

	ft::map<int, int> emptyMap2;
	std::cout << "emptyMap2.empty(): " << emptyMap2.empty() << std::endl;
	emptyMap2.insert(ft::make_pair(1, 3));
	emptyMap2.insert(ft::make_pair(1, 5));
	std::cout << "emptyMap2.empty() after insert(1,3) and (1,5): " << emptyMap2.empty() << std::endl;

	std::cout << "\nsize" << std::endl;
	std::cout << "emptyMap.size(): " << emptyMap.size() << std::endl;
	std::cout << "emptyMap2.size(): " << emptyMap2.size() << std::endl;
	std::cout << "notEmptyMap.size(): " << notEmptyMap.size() << std::endl;
	std::cout << "copyMap.size(): " << copyMap.size() << std::endl;
	std::cout << "rangeMap.size(): " << rangeMap.size() << std::endl;

	std::cout << "\nmax_size:" << std::endl;
	std::cout << "emptyMap.max_size(): " << emptyMap.max_size() << std::endl;
	std::cout << "emptyMap2.max_size(): " << emptyMap2.max_size() << std::endl;
	std::cout << "notEmptyMap.max_size(): " << notEmptyMap.max_size() << std::endl;
	std::cout << "copyMap.max_size(): " << copyMap.max_size() << std::endl;
	std::cout << "rangeMap.max_size(): " << rangeMap.max_size() << std::endl;

	/*Element Access */
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Element Access ]" << std::endl;
	std::cout << "at" << std::endl;
	std::cout << "emptyMap.at(1): " << emptyMap.at(1) << std::endl;
	try
	{
		int my_value = emptyMap.at(2);
		std::cout << "emptyMap.at(2): " << my_value << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	std::cout << "operator []" << std::endl;
	std::cout << "emptyMap[1]: " << emptyMap[1] << std::endl;
	std::cout << "emptyMap[5]: " << emptyMap[5] << std::endl;

	emptyMap[5] = 16;
	emptyMap[3] = 17;
	std::cout << "emptyMap[5]: " << emptyMap[5] << std::endl;
	std::cout << "emptyMap[3]: " << emptyMap[3] << std::endl;
	std::cout << "emptyMap.size(): " << emptyMap.size() << std::endl; 

	/*
	**	Modifiers Methods
	*/
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Modifiers Methods ]" << std::endl;
	print_map_values(emptyMap, "emptyMap before inserts: ");
	insert_pair1 = emptyMap.insert(ft::make_pair(2, 2));
	it = insert_pair1.first;
	insert_pair1 = emptyMap.insert(ft::make_pair(2, 2));
	it = insert_pair1.first;
	insert_pair1 = emptyMap.insert(ft::make_pair(2, 2));
	it = insert_pair1.first;
	insert_pair1 = emptyMap.insert(ft::make_pair(8, 4));
	it = insert_pair1.first;
	insert_pair1 = emptyMap.insert(ft::make_pair(12, 2));
	it = insert_pair1.first;
	print_map_values(emptyMap, "emptyMap after inserts: ");
	std::cout << std::endl;
	std::cout << "test map insert with hint" << std::endl;
	print_map_values(emptyMap, "emptyMap before insert with position: ");
	it = emptyMap.insert(it, ft::make_pair(13, 5));
	it = emptyMap.insert(it, ft::make_pair(13, 6));
	it = emptyMap.insert(it, ft::make_pair(21, 5));
	it = emptyMap.insert(it, ft::make_pair(20, 2));
	print_map_values(emptyMap, "emptyMap after insert with position: ");

	std::cout << "[ --- erase ]" << std::endl;
	print_map_values(emptyMap, "emptyMap before erase begin: ");
	emptyMap.erase(emptyMap.begin());
	print_map_values(emptyMap, "emptyMap after erase begin: ");
	
	std::cout << "[ --- erase key_type ]" << std::endl;
		print_map_values(emptyMap, "emptyMap before erase 2: ");
	std::cout << "emptyMap.erase(2): " << emptyMap.erase(2) << std::endl;
	print_map_values(emptyMap, "emptyMap after erase 2: ");

	std::cout << "[ --- erase range ]" << std::endl;
	print_map_values(notEmptyMap, "notEmptyMap before erase range: ");
	std::cout << "notEmptyMap.erase(notEmptyMap.begin(), notEmptyMap.end()): " << std::endl;
	notEmptyMap.erase(++notEmptyMap.begin(), --notEmptyMap.end());
	print_map_values(notEmptyMap, "notEmptyMap after erase range: ");

	std::cout << "[ --- swap ]" << std::endl;
	it = notEmptyMap.begin();
	print_map_values(notEmptyMap, "notEmptyMap before swap: ");
	print_map_values(rangeMap, "rangeMap before swap: ");
	notEmptyMap.swap(rangeMap);
	print_map_values(notEmptyMap, "notEmptyMap after swap ");
	print_map_values(rangeMap, "rangeMap after swap ");

	std::cout << "[ --- clear ]" << std::endl;
	print_map_values(notEmptyMap, "notEmptyMap before clear: ");
	notEmptyMap.clear();
	print_map_values(notEmptyMap, "notEmptyMap after clear: ");
	print_map_values(emptyMap, "emptyMap before clear: ");
	emptyMap.clear();
	print_map_values(emptyMap, "emptyMap after clear: ");
	print_map_values(copyMap, "copyMap before clear: ");
	copyMap.clear();
	print_map_values(copyMap, "copyMap after clear: ");
	
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Operations Methods ]" << std::endl;

	notEmptyMap[1] = 2;
	notEmptyMap[5] = 10;
	notEmptyMap[9] = 18;
	ft::map<int, int>::iterator itInt;
	ft::map<int, int>::iterator itInt2;
	itInt = notEmptyMap.find(5);
	itInt2 = notEmptyMap.find(9);
	std::cout << "it: " << itInt->first << std::endl;
	std::cout << "it2: "<< itInt2->first << std::endl;
	
	ft::map<int, int>::value_compare val_comp = notEmptyMap.value_comp();
	ft::map<int, int>::key_compare key_comp = notEmptyMap.key_comp();

	std::cout << "val_comp it e it2: " << val_comp(*itInt, *itInt2) << '\n';
	std::cout << "val_comp it e it: " << val_comp(*itInt, *itInt) << '\n';
	std::cout << "key_comp it e it2: " << key_comp(itInt->first, itInt2->first) << '\n';
	std::cout << "key_comp it e it: " << key_comp(itInt->first, itInt->first) << '\n';

	std::cout << "[ find ]" << std::endl;
	print_map_values(notEmptyMap, "notEmptyMap values: ");
	std::cout << "notEmptyMap.find(1)->second: " << notEmptyMap.find(1)->second << std::endl;
	std::cout << "notEmptyMap.find(5)->second: " << notEmptyMap.find(5)->second << std::endl;
	std::cout << "notEmptyMap.find(9)->second: " << notEmptyMap.find(9)->second << std::endl;
	std::cout << "notEmptyMap.find(10) == notEmptyMap.end(): " << (notEmptyMap.find(10) == notEmptyMap.end())  << std::endl;
	std::cout << "notEmptyMap.find(2) == notEmptyMap.end(): " << (notEmptyMap.find(2) == notEmptyMap.end())  << std::endl;
	std::cout << "notEmptyMap.find(1) == notEmptyMap.end(): " << (notEmptyMap.find(1) == notEmptyMap.end())  << std::endl;


	std::cout << "[ count ]" << std::endl;
	std::cout << "notEmptyMap.count(1): " << notEmptyMap.count(1) << std::endl;
	std::cout << "notEmptyMap.count(2): " << notEmptyMap.count(2) << std::endl;
	std::cout << "notEmptyMap.count(5): " << notEmptyMap.count(5) << std::endl;
	std::cout << "notEmptyMap.count(9): " << notEmptyMap.count(9) << std::endl;
	std::cout << "notEmptyMap.count(10): " << notEmptyMap.count(10) << std::endl;
	
	std::cout << "[ equal_range ]" << std::endl;
	std::cout << *notEmptyMap.equal_range(0).first << '\n';
	std::cout << *notEmptyMap.equal_range(1).first << '\n';
	std::cout << *notEmptyMap.equal_range(2).first << '\n';
	std::cout << *notEmptyMap.equal_range(4).first << '\n';
	std::cout << *notEmptyMap.equal_range(5).first << '\n';
	std::cout << *notEmptyMap.equal_range(9).first << '\n';
	
	std::cout << "[ lower_bound ]" << std::endl;
	std::cout << "notEmptyMap.lower_bound(1): " << notEmptyMap.lower_bound(1)->first << std::endl;
	std::cout << "notEmptyMap.lower_bound(2): " << notEmptyMap.lower_bound(2)->first << std::endl;
	std::cout << "notEmptyMap.lower_bound(5): " << notEmptyMap.lower_bound(5)->first << std::endl;
	std::cout << "notEmptyMap.lower_bound(9): " << notEmptyMap.lower_bound(9)->first << std::endl;
	std::cout << "notEmptyMap.lower_bound(10) == notEmptyMap.end(): " 
			<< (notEmptyMap.lower_bound(10) ==  notEmptyMap.end()) << std::endl;  

	std::cout << "[ upper_bound ]" << std::endl;
	std::cout << "notEmptyMap.upper_bound(0): " << notEmptyMap.upper_bound(0)->first << std::endl;
	std::cout << "notEmptyMap.upper_bound(1): " << notEmptyMap.upper_bound(1)->first << std::endl;
	std::cout << "notEmptyMap.upper_bound(2): " << notEmptyMap.upper_bound(2)->first << std::endl;
	std::cout << "notEmptyMap.upper_bound(5): " << notEmptyMap.upper_bound(5)->first << std::endl;
	std::cout << "notEmptyMap.upper_bound(9) == notEmptyMap.end(): " 
			<< (notEmptyMap.upper_bound(9) ==  notEmptyMap.end()) << std::endl;
	
	

	/*
	**	Allocator
	*/
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Allocator ]" << std::endl;
	
	ft::map<int, int>::allocator_type allocator = notEmptyMap.get_allocator();
	ft::pair<const int, int> *pair_ptr = allocator.allocate(5);
	allocator.construct(pair_ptr, ft::make_pair(1, 2));
	allocator.construct(pair_ptr + 1, ft::make_pair(2, 2));
	allocator.construct(pair_ptr + 2, ft::make_pair(3, 2));
	allocator.construct(pair_ptr + 3, ft::make_pair(4, 2));
	allocator.construct(pair_ptr + 4, ft::make_pair(5, 2));

	std::cout << "pairs allocated using allocator: " <<  std::endl;
	for (int i = 0; i < 5; i++) {
		std::cout << "[" << (pair_ptr + i)->first << "] = " << (pair_ptr + i)->second << std::endl;
	}

	for (int i = 0; i < 5; i++){
		allocator.destroy(pair_ptr + i);
	}
	allocator.deallocate(pair_ptr, 5);

	/*
	**	Non-member Opeartors Overload
	*/
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ Non-member Operators Overload ]" << std::endl;
	ft::map<int, int> copy_map2(notEmptyMap);

	std::cout << "notEmptyMap == rangeMap: " << (notEmptyMap == rangeMap) << std::endl;
	std::cout << "notEmptyMap != rangeMap: " << (notEmptyMap != rangeMap) << std::endl;
	std::cout << "notEmptyMap < rangeMap: " << (notEmptyMap < rangeMap) << std::endl;
	std::cout << "notEmptyMap <= rangeMap: " << (notEmptyMap <= rangeMap) << std::endl;
	std::cout << "notEmptyMap > rangeMap: " << (notEmptyMap > rangeMap) << std::endl;
	std::cout << "notEmptyMap >= rangeMap: " << (notEmptyMap >= rangeMap) << std::endl;

	std::cout << "emptyMap == rangeMap: " << (emptyMap == rangeMap) << std::endl;
	std::cout << "emptyMap != rangeMap: " << (emptyMap != rangeMap) << std::endl;
	std::cout << "emptyMap < rangeMap: " << (emptyMap < rangeMap) << std::endl;
	std::cout << "emptyMap <= rangeMap: " << (emptyMap <= rangeMap) << std::endl;
	std::cout << "emptyMap > rangeMap: " << (emptyMap > rangeMap) << std::endl;
	std::cout << "emptyMap >= rangeMap: " << (emptyMap >= rangeMap) << std::endl;

	std::cout << "copy_map2 == rangeMap: " << (copy_map2 == rangeMap) << std::endl;
	std::cout << "copy_map2 != rangeMap: " << (copy_map2 != rangeMap) << std::endl;
	std::cout << "copy_map2 < rangeMap: " << (copy_map2 < rangeMap) << std::endl;
	std::cout << "copy_map2 <= rangeMap: " << (copy_map2 <= rangeMap) << std::endl;
	std::cout << "copy_map2 > rangeMap: " << (copy_map2 > rangeMap) << std::endl;
	std::cout << "copy_map2 >= rangeMap: " << (copy_map2 >= rangeMap) << std::endl;

	std::cout << "copy_map2 == notEmptyMap: " << (copy_map2 == notEmptyMap) << std::endl;
	std::cout << "copy_map2 != notEmptyMap: " << (copy_map2 != notEmptyMap) << std::endl;
	std::cout << "copy_map2 < notEmptyMap: " << (copy_map2 < notEmptyMap) << std::endl;
	std::cout << "copy_map2 <= notEmptyMap: " << (copy_map2 <= notEmptyMap) << std::endl;
	std::cout << "copy_map2 > notEmptyMap: " << (copy_map2 > notEmptyMap) << std::endl;
	std::cout << "copy_map2 >= notEmptyMap: " << (copy_map2 >= notEmptyMap) << std::endl;
	std::cout << "------------------------------------" << std::endl;
}
