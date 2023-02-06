#include "containers.hpp"
#include <iostream>
#include <ostream>
#include <set>

#define KO "\033[1;31mKO\033[0m"
#define OK "\033[1;32mOK\033[0m"

template <typename T, typename U, typename V>
std::ostream& operator<<(std::ostream& out, const ft::set<T, U, V>& the_set){
	out << "[ ";
	typename ft::set<T>::iterator iter = the_set.begin();
	while (iter != the_set.end()){
		out << *iter;
		++iter;
		if (iter != the_set.end())
			out << ", ";
		else
			out << " ";
	}
	out << " ]";
	return out;
}

//class compare the opposito of std::less
template<typename T>
class CustomComparator{
	public:
		bool operator()(T lhs, T rhs) const{
			return lhs > rhs;
		}
};

static void test_default_constructor(){
		std::cout << "Testing set" << std::endl;
		{
			std::cout << "Constructors" << std::endl;
			ft::set<int> set1;
			ft::set<int> set2;
			set2 = set1;
			ft::set<int> set3(set2);
			std::cout << "size: " << set1.size() << std::endl;
			std::cout << "empty: " << set1.empty() << std::endl;
			set1.clear();
			set1.swap(set2);
		}
	std::cout << "------------------------------------" << std::endl;
}

static void test_range_constructor(){
	std::cout << "test_range_constructor" << std::endl;
	ft::vector<int> intvec;
	for (int i = 0; i < 10; i++){
		intvec.push_back(i);
	}
	ft::set<int> smallset(intvec.begin(), intvec.end());
	ft::set<int> SetCopy(smallset.begin(), smallset.end());
	std::cout << "size: " << smallset.size() << std::endl;
	std::cout << "set" << smallset << std::endl;
	std::cout << "copy" << SetCopy << std::endl;
	if (ft::equal(smallset.begin(), smallset.end(), SetCopy.begin()))
		std::cout << OK " ";
	else
		std::cout << KO " ";
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;
}
static void test_copy_constructor() {
	std::cout << "test set copy constructor" << std::endl;

	ft::vector<int> intvec;
	for (int i = 10; i > 0; i--) {
		intvec.push_back(i);
	}
	ft::set<int> small_set(intvec.begin(), intvec.end());
	ft::set<int> copy_set(small_set);
	std::cout << "set: " << copy_set << std::endl;
}

static void test_assignment_operator(){
	std::cout << "test assignment operator" << std::endl;
	ft::vector<int> intvec;
	for (int i = 10; i > 0; i--){
		intvec.push_back(i);
	}
	ft::set<int> small_set(intvec.begin(), intvec.end());
	ft::set<int> copy_set;
	copy_set = small_set;
	std::cout << "copy_set" << copy_set << std::endl;
	std::cout << "small_set" << small_set << std::endl;
	if (ft::equal(small_set.begin(), small_set.end(), copy_set.begin()))
		std::cout << OK " ";
	else
		std::cout << KO " ";
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_begin(){
	std::cout << "test begin()" << std::endl;
	ft::set<int> set;

	for (int i = 1; i < 30; i++)
		set.insert(1000 / i);
	std::cout << "set:\n"<< set << std::endl;
	std::cout << "begin: "<< *set.begin() << std::endl;
	
	ft::set<std::string> MySet;
	std::set<std::string> OriginalSet;

	MySet.insert("a"), OriginalSet.insert("a");
	MySet.insert("b"), OriginalSet.insert("b");
	MySet.insert("c"), OriginalSet.insert("c");
	MySet.insert("d"), OriginalSet.insert("d");
	MySet.insert("e"), OriginalSet.insert("e");

	ft::set<std::string>::iterator it = MySet.begin();
	ft::set<std::string>::const_iterator itC = MySet.begin();
	std::set<std::string>::const_iterator OitC = OriginalSet.begin();
	std::set<std::string>::iterator Oit = OriginalSet.begin();

	if (*it == *Oit)
		std::cout << "iterator:  " << OK " ";
	else
		std::cout << KO " ";
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;

	if (*itC == *OitC)
		std::cout  << "const_iterator: " << OK " ";
	else
		std::cout << KO " ";
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_end(){
	std::cout << "Test set end" << std::endl;
	ft::set<int> set;
	for (int i = 1; i <30; i++){
		set.insert(1000 / i);
	}	
	for (ft::set<int>::iterator end = --set.end(); end != set.begin(); --end){
		std::cout << "element: " << *end << std::endl;
	}
	ft::set<std::string> MySet;
	std::set<std::string> OriginalSet;

	MySet.insert("a"), OriginalSet.insert("a");
	MySet.insert("b"), OriginalSet.insert("b");
	MySet.insert("c"), OriginalSet.insert("c");
	MySet.insert("d"), OriginalSet.insert("d");
	MySet.insert("e"), OriginalSet.insert("e");

	ft::set<std::string>::iterator it = --MySet.end();
	ft::set<std::string>::const_iterator itC = --MySet.end();
	std::set<std::string>::iterator Oit = --OriginalSet.end();
	std::set<std::string>::const_iterator OitC = --OriginalSet.end();
	if (*it == *Oit)
		std::cout << "iterator:  " << OK " ";
	else
		std::cout << KO " ";
	std::cout << std::endl;

	if (*itC == *OitC)
		std::cout  << "const_iterator: " << OK " ";
	else
		std::cout << KO " ";
	std::cout << std::endl;

}

static ft::set<int> generate_int_set(){
	ft::set<int> intset;
	for (int i = -5; i < 5; i++){
		intset.insert(i * 10);
	}
	return intset;
}

static void test_empty(){
	std::cout << "empty set" << std::endl;
	ft::set<int> intset;

	std::cout << "set is empty: " << intset.empty() << std::endl;

	intset = generate_int_set();
	std::cout << "set is empty: " << intset.empty() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

static void test_size() {
	std::cout << "test set size" << std::endl;

	ft::set<int> intset;
	std::cout << "empty size: " << intset.size() << std::endl;
	intset.insert(4);
	std::cout << "single size: " << intset.size() << std::endl;
	intset = generate_int_set();
	std::cout << "generated size: " << intset.size() << std::endl;
}


static void test_max_size(){
	std::cout << "test max size" << std::endl;
	ft::set<int> intset =  generate_int_set();

	std::cout << "max size != 0: " << (intset.max_size() == 0) << std::endl;
	ft::set<std::string> string_set;

	std::cout << "int set max_size != string set max_size: " << (intset.max_size() != string_set.max_size()) << std::endl;
	std::cout << "------------------------------------" << std::endl;
}


static void test_insert(){
	std::cout << "test insert" << std::endl;

	std::cout << "insert a pair on an empty set" << std::endl;
	ft::set<std::string> strset;

	ft::pair<ft::set<std::string>::iterator, bool> p = strset.insert("arara");
	std::cout << "set:\n" << strset << std::endl;
	std::cout << "set return " << *p.first << " " << p.second << std::endl;
	p = strset.insert("macaco");
	std::cout << "set:\n" << strset << std::endl;
	std::cout << "set success " << p.second << std::endl;
	std::cout << "set return " << (p.first != strset.end() ? *p.first : "end") << " " << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_insert_custom(){
	std::cout << "test insert with custom comparator" << std::endl;

	std::cout << "insert a pair on an empty set" << std::endl;
	ft::set<std::string, CustomComparator<std::string> > strset;
	strset.insert("arara");
	std::cout << "set:\n" << strset << std::endl;
	std::cout << "------------------------------------" << std::endl;

	std::cout << "test the return value of the insertion" << std::endl;
	ft::pair<ft::set<std::string, std::string>::iterator, bool> result;
	result = strset.insert("carro");
	std::cout << "result->first" << *result.first << "\nresult->second: " << result.second << std::endl;

	std::cout << "insert an item with an already existing key" << std::endl;
	result = strset.insert("moto");
	std::cout << "result->first" << *result.first << "\nresult->second: " << result.second << std::endl;
}

static void test_insert_range(){
	std::cout << "test insert range" << std::endl;
	ft::vector<int> intvec;

	for(int i = 0; i < 15; i++){
		intvec.push_back(i * i - 1);
	}
	std::cout << "insert in an empty set" << std::endl;
	{
		ft::set<int> intset;

		intset.insert(intvec.begin(), intvec.end());
		std::cout << "set size: " << intset.size() << std::endl;
		std::cout << "intset: " << intset << std::endl;
	}
	std::cout << "------------------------------------" << std::endl;
}

static void test_erase(){
	std::cout << "test set erase" << std::endl;

	ft::set<int> intset;
	for (int i = 0; i < 15; i++){
		intset.insert(i * i * 2);
	}
	std::cout << "initial set" << intset << std::endl;
	//intset.erase(intset.begin());
	/*std::cout << "delete begin()" << intset << std::endl;
	intset.erase(intset.begin());
	std::cout << "delete begin()" << intset << std::endl;

	std::cout << "delete 99" << std::endl;
	intset.erase(intset.find(98));
	std::cout << intset << std::endl;
	std::cout << "delete everything" << std::endl;
	while (intset.size() > 0)
		intset.erase(intset.begin()++);
	std::cout << "set: " << intset << std::endl;*/
}

void test_set(void){
	std::cout << "====================================" << std::endl;
	std::cout << "                SET                 " << std::endl;
	std::cout << "====================================" << std::endl;
		test_default_constructor();
		test_range_constructor();
		test_copy_constructor();
		test_assignment_operator();
		test_begin();
		test_end();
		test_empty();
		test_size();
		test_max_size();
		test_insert();
		test_insert_custom();
		test_insert_range();
		test_erase();
}