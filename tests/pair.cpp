#include "containers.hpp"
#include <ostream>

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ft::pair<T, U>& pair){
	out << "pair[" << pair.first << ", " << pair.second << "]";
	return out;
}

static void test_constructor(){
	std::cout << "[ test pair default constructor ]" << std::endl;
	ft::pair<const int, int> item;
	std::cout << item << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_initialize_constructor(){
	std::cout << "[ test_initialization_constructor ]" << std::endl;
	ft::pair<const std::string, int> item("first", 42);
	std::cout << item << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

//this operator is useless in c++98
static void test_assignment(){
	std::cout << "[ test assignment operator ]" << std::endl;
	ft::pair<std::string, int> item("first", 42);
	ft::pair<const std::string, int> other("second", 84);
	item = other;
	std::cout << item << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_relational_oper(){
	std::cout << "[ Testing relational operators ]" << std::endl;
	ft::pair<std::string, int> empty;
	ft::pair<std::string, int> some("a handfull", 30);
	ft::pair<std::string, int> greater_key("greater", 30);
	ft::pair<std::string, int> greater_value("greater", 42);

	std::cout << "empty == empty -> " << (empty == empty) << std::endl;
	std::cout << "empty == some -> " << (empty == some) << std::endl;
	std::cout << "different value are equal -> " << (greater_key == greater_value) << std::endl;

	std::cout << "empty != empty -> " << (empty != empty) << std::endl;
	std::cout << "empty != some -> " << (empty != some) << std::endl;
	std::cout << "different value are differents -> " << (greater_key != greater_value) << std::endl;

	std::cout << "empty < empty -> " 				<< (empty < empty) << std::endl;
	std::cout << "empty < some -> " 				<< (empty < some) << std::endl;
	std::cout << "some < empty -> " 				<< (some < empty) << std::endl;
	std::cout << "greater key < some -> " 			<< (greater_key < some) << std::endl;
	std::cout << "some < greater key -> " 			<< (some < greater_key) << std::endl;
	std::cout << "greater key < greater value -> "	<< (greater_key < greater_value) << std::endl;
	std::cout << "greater value < greater key -> " 	<< (greater_value < greater_key) << std::endl;

	std::cout << "empty <= empty -> " 				<< (empty <= empty) << std::endl;
	std::cout << "empty <= some -> " 				<< (empty <= some) << std::endl;
	std::cout << "some <= empty -> " 				<< (some <= empty) << std::endl;
	std::cout << "greater key <= some -> " 			<< (greater_key <= some) << std::endl;
	std::cout << "some <= greater key -> " 			<< (some <= greater_key) << std::endl;
	std::cout << "greater key <= greater value -> "	<< (greater_key <= greater_value) << std::endl;
	std::cout << "greater value <= greater key -> " 	<< (greater_value <= greater_key) << std::endl;

	std::cout << "empty > empty -> " 				<< (empty > empty) << std::endl;
	std::cout << "empty > some -> " 				<< (empty > some) << std::endl;
	std::cout << "some > empty -> " 				<< (some > empty) << std::endl;
	std::cout << "greater key > some -> " 			<< (greater_key > some) << std::endl;
	std::cout << "some > greater key -> " 			<< (some > greater_key) << std::endl;
	std::cout << "greater key > greater value -> "	<< (greater_key > greater_value) << std::endl;
	std::cout << "greater value > greater key -> " 	<< (greater_value > greater_key) << std::endl;

	std::cout << "empty >= empty -> " 				<< (empty >= empty) << std::endl;
	std::cout << "empty >= some -> " 				<< (empty >= some) << std::endl;
	std::cout << "some >= empty -> " 				<< (some >= empty) << std::endl;
	std::cout << "greater key >= some -> " 			<< (greater_key >= some) << std::endl;
	std::cout << "some >= greater key -> " 			<< (some >= greater_key) << std::endl;
	std::cout << "greater key >= greater value -> "	<< (greater_key >= greater_value) << std::endl;
	std::cout << "greater value >= greater key -> " << (greater_value >= greater_key) << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

static void test_cpp_operator(){
	ft::pair<int, char> foo (10, 'z');
	ft::pair<int, char> bar (90, 'a');
	if (foo == bar) std::cout << "foo and bar are equal" << std::endl;
	if (foo != bar) std::cout << "foo and bar are not equal" << std::endl;
	if (foo < bar) std::cout << "foo is less than bar" << std::endl;
	if (foo > bar) std::cout << "foo is greater than bar" << std::endl;
	if (foo <= bar) std::cout << "foo is less than or equal to bar" << std::endl;
	if (foo >= bar) std::cout << "foo is greater than or equal to bar" << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

static void test_make_pair(){
	std::cout << "[ Testing make_pair ]" << std::endl;
	ft::pair<int, int> result = ft::make_pair(10, 20);
	std::cout << "ft::make_pair(10, 20): " << result << std::endl;
	ft::pair<int, std::string> bar = ft::make_pair(90, "art and culture");
	std::cout << "ft::make_pair(90, a): " << bar << std::endl;
	ft::pair<float, std::string> foo = ft::make_pair(42.2f, "coding");
	std::cout << "ft::make_pair(42.2f, coding): " << foo << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

void test_pair(void){
	std::cout << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "                 pair                " << std::endl;
	std::cout << "====================================" << std::endl;
	test_constructor();
	test_initialize_constructor();
	test_assignment();
	test_relational_oper();
	test_cpp_operator();
	test_make_pair();
}
