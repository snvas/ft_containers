#include "containers.hpp"
#include <iostream>
#include <ostream>
#include <set>

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

template <typename T>
void print(const T& x){
	std::cout << x << " ";
	std::cout << std::endl;
}

static void test_default_constructor(){
		std::cout << "[ Testing set ]" << std::endl;
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
	std::cout << "[ test_range_constructor ]" << std::endl;
	ft::vector<int> intvec;
	for (int i = 0; i < 10; i++){
		intvec.push_back(i);
	}
	ft::set<int> smallset(intvec.begin(), intvec.end());
	ft::set<int> SetCopy(smallset.begin(), smallset.end());
	std::cout << "size: " << smallset.size() << std::endl;
	std::cout << "set" << smallset << std::endl;
	std::cout << "copy" << SetCopy << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;
}
static void test_copy_constructor() {
	std::cout << "[ test set copy constructor ]" << std::endl;

	ft::vector<int> intvec;
	for (int i = 10; i > 0; i--) {
		intvec.push_back(i);
	}
	ft::set<int> small_set(intvec.begin(), intvec.end());
	std::cout << "small_set: " << small_set << std::endl;
	ft::set<int> copy_set(small_set);
	std::cout << "set: " << copy_set << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

static void test_assignment_operator(){
	std::cout << "[ test assignment operator ]" << std::endl;
	ft::vector<int> intvec;
	for (int i = 10; i > 0; i--){
		intvec.push_back(i);
	}
	ft::set<int> small_set(intvec.begin(), intvec.end());
	ft::set<int> copy_set;
	copy_set = small_set;
	std::cout << "copy_set" << copy_set << std::endl;
	std::cout << "small_set" << small_set << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_begin(){
	std::cout << "[ test begin() ]" << std::endl;
	ft::set<int> set;
	std::set<int> originalSet;

	for (int i = 1; i < 10; i++){
		set.insert(1000 / i);
		originalSet.insert(1000 / i);
	}
	std::cout << "set:\n"<< set << std::endl;
	ft::set<int>::iterator it = set.begin();
	ft::set<int>::const_iterator itC = set.begin();
	std::set<int>::iterator Oit = originalSet.begin();
	std::set<int>::const_iterator OitC = originalSet.begin();

	std::cout << "iterator: " << *it << std::endl;	
	std::cout << "const_iterator: " << *itC << std::endl;
	std::cout << "Original iterator: " << *Oit << std::endl;
	std::cout << "Original const_iterator: " << *OitC << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_end(){
	std::cout << "[ Test set end ]" << std::endl;
	ft::set<int> set;
	std::set<int> originalSet;
	for (int i = 1; i < 15; i++){
		set.insert(1000 / i);
		originalSet.insert(1000 / i);
	}	
	for (ft::set<int>::iterator end = --set.end(); end != set.begin(); --end){
		std::cout << "element: " << *end << std::endl;
	}

	ft::set<int>::iterator it = --set.end();
	ft::set<int>::const_iterator itC = --set.end();
	std::set<int>::iterator Oit = --originalSet.end();
	std::set<int>::const_iterator OitC = --originalSet.end();
	std::cout << "iterator: " << *it << std::endl;	
	std::cout << "const_iterator: " << *itC << std::endl;
	std::cout << "Original iterator: " << *Oit << std::endl;
	std::cout << "Original const_iterator: " << *OitC << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_rbegin(){
	std::cout << "[ test rbegin ]" << std::endl;
	ft::set<std::string> strset;
	std::set<std::string> ostrSet;

	strset.insert("a"), ostrSet.insert("a");
	strset.insert("b"), ostrSet.insert("b");
	strset.insert("c"), ostrSet.insert("c");
	strset.insert("d"), ostrSet.insert("d");
	
	ft::set<std::string>::reverse_iterator itR = strset.rbegin();
	std::set<std::string>::reverse_iterator OitR = ostrSet.rbegin();
	ft::set<std::string>::const_reverse_iterator itCR = strset.rbegin();
	std::set<std::string>::const_reverse_iterator OitCR = ostrSet.rbegin();
	std::cout << "Set: " << strset << std::endl;
	std::cout << "reverse_iterator: " << *itR << std::endl;	
	std::cout << "const_reverse_iterator: " << *itCR << std::endl;
	std::cout << "Original reverse_iterator: " << *OitR << std::endl;
	std::cout << "Original const_reverse_iterator: " << *OitCR << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_rend(){
	std::cout << "[ test rend ]" << std::endl;
	ft::set<int> intset;

	intset.insert(1);
	intset.insert(2);
	intset.insert(3);
	intset.insert(4);
	
	ft::set<int>::reverse_iterator itR = intset.rend();
	ft::set<int>::const_reverse_iterator const_itR = intset.rend();

	for (itR = intset.rbegin(); itR != intset.rend(); ++itR)
		std::cout << *itR << std::endl;
	std::cout << std::endl;
	for (const_itR = intset.rbegin(); const_itR != intset.rend(); ++const_itR)
		std::cout << *const_itR << std::endl;
	std::cout << std::endl;
	std::cout << "itR == const_itR: " << (itR == const_itR) << std::endl;
	std::cout << "it == it: " << (itR == itR) << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

static ft::set<int> generate_int_set(){
	ft::set<int> intset;
	for (int i = -5; i < 5; i++){
		intset.insert(i * 10);
	}
	return intset;
}

static void test_empty(){
	std::cout << "[ empty set ]" << std::endl;
	ft::set<int> intset;

	std::cout << "set is empty: " << intset.empty() << std::endl;

	intset = generate_int_set();
	std::cout << "set is empty: " << intset.empty() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

static void test_size() {
	std::cout << "[ test set size ]" << std::endl;

	ft::set<int> intset;
	std::cout << "empty size: " << intset.size() << std::endl;
	intset.insert(4);
	std::cout << "single size: " << intset.size() << std::endl;
	intset = generate_int_set();
	std::cout << "generated size: " << intset.size() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}


static void test_max_size(){
	std::cout << "[ test max size ]" << std::endl;
	ft::set<int> intset =  generate_int_set();

	std::cout << "max size != 0: " << (intset.max_size() == 0) << std::endl;
	ft::set<std::string> string_set;

	std::cout << "int set max_size != string set max_size: " << (intset.max_size() != string_set.max_size()) << std::endl;
	std::cout << "------------------------------------" << std::endl;
}


static void test_insert(){
	std::cout << "[ test insert ]" << std::endl;

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

static void test_insert_hint(){
	std::cout << "[ test insert hint]" << std::endl;
	ft::set<int> myset;
	myset.insert(100);
	ft::set<int>::iterator it = myset.begin();
	myset.insert (it, 300);  
	myset.insert (it, 400);  
	std::cout << "iterator: " << *it << std::endl;
	std::cout << "myset contains: " << myset << std::endl;
	ft::pair<ft::set<int>::iterator, bool> ret;
	ret = myset.insert(400);
	if (ret.second == false){
		std::cout << "element already existed";
		std::cout << " with a value of " << *(ret.first) << std::endl;
	} 
	std::cout << "------------------------------------" << std::endl;
}

static void test_insert_range(){
	std::cout << "[ test insert range ]" << std::endl;
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
	std::cout << "[ test set erase ]" << std::endl;

	ft::set<int> intset;
	for (int i = 0; i < 15; i++){
		intset.insert(i * i * 2);
	}
	std::cout << "initial set" << intset << std::endl;
	intset.erase(intset.begin());
	std::cout << "delete begin()" << intset << std::endl;
	intset.erase(intset.begin());
	std::cout << "delete begin()" << intset << std::endl;

	std::cout << "delete 99" << std::endl;
	intset.erase(intset.find(98));
	std::cout << intset << std::endl;
	std::cout << "delete everything" << std::endl;
	while (intset.size() > 0)
		intset.erase(intset.begin());
	std::cout << "set: " << intset << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_erase_value(){
	std::cout << "[ test set erase by key ]" << std::endl;
	ft::set<float> intset;
	int size = 9;
	for (float i = 1; i < size; i++){
		float float_to_insert = i/10 * i;
		intset.insert(float_to_insert);
	}
	std::cout << "initial set" << intset << std::endl;
	ft::set<int>::size_type result = intset.erase(0.1);
	std::cout << "delete 0.1: " << intset << std::endl;
	std::cout << "result: " << result << std::endl;
	result = intset.erase(0.4);
	std::cout << "delete 0.4: " << intset << std::endl;
	std::cout << "result: " << result << std::endl;
	result = intset.erase(6.4);
	std::cout << "delete 6.4: " << intset << std::endl;
	std::cout << "result: " << result << std::endl;
	result = intset.erase(0.2);
	std::cout << "delete 0.2: " << intset << std::endl;
	std::cout << "result: " << result << std::endl;
	std::cout << "delete all" << std::endl;
	while (intset.size() > 0)
		intset.erase(--intset.end());
	std::cout << "set: " << intset << std::endl;
	std::cout << "------------------------------------" << std::endl;
	
}

static void test_erase_range(){
	std::cout << "[ test set erase range ]" << std::endl;
	ft::set<int> intset;
	intset.insert(1);
	intset.insert(2);
	intset.insert(3);
	intset.insert(4);
	intset.insert(5);
	intset.erase(++intset.begin(), --intset.end());
	print(intset);
	ft::set<float> set;
	int size = 9;
	for (float i = 1; i < size; i++){
		float float_to_insert = i/10 * i;
		set.insert(float_to_insert);
	}
	std::cout << "set: " << set << std::endl;
	set.erase(++set.begin(), --set.end());
	std::cout << "set: " << set << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_clear(){
	std::cout << "[ test set clear ]" << std::endl;
	ft::set<int> intset;

	intset.insert(1);
	intset.insert(2);
	intset.insert(3);
	intset.insert(4);
	intset.insert(5);
	std::cout << "set: " << intset << std::endl;
	intset.clear();
	std::cout << "set: " << intset << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_swap(){
	std::cout << "[ test set swap ]" << std::endl;
	ft::set<int> intset;
	ft::set<int> otherintset;
	intset.insert(1);
	intset.insert(2);
	intset.insert(3);
	intset.insert(4);
	
	otherintset.insert(5);
	otherintset.insert(6);
	otherintset.insert(7);
	std::cout << "before swap intset: " << intset << std::endl;
	std::cout << "before swap otherintset: " << otherintset << std::endl;
	intset.swap(otherintset);

	std::cout << "after swap intset: " << intset << std::endl;
	std::cout << "after swap otherintset: " << otherintset << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_value_comp(){
	std::cout << "[ test set value_comp ]" << std::endl;
	ft::set<int> intset;

	ft::set<int>::value_compare mycomp = intset.value_comp();
	for (int i = 0; i <= 5; i++)
		intset.insert(i);
	std::cout << "intset contains ";
	int highest = *intset.rbegin();
	ft::set<int>::iterator it = intset.begin();
	while (mycomp(*(it), highest))
	{
		std::cout << ' ' << *it;
		it++;
	}
	std::cout << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_key_comp(){
	std::cout << "[ test set key_comp ]" << std::endl;
	ft::set<int> intset;
	ft::set<int> intsetCopy;

	ft::set<int>::key_compare intset_comp = intset.key_comp();

	intset.insert(146);
	intsetCopy.insert(2421);

	std::cout << intset_comp(*intset.begin(), *intsetCopy.begin()) << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

static void test_find(){
	std::cout << "[ test set find ]" << std::endl;
	ft::set<std::string> strset;

	strset.insert("a");
	print(strset.find("a") == strset.begin());
	print(strset.find("a") == strset.end());
	print(strset.find("b") == strset.end());
	print(strset.find("b") == strset.begin());
	std::cout << "------------------------------------" << std::endl;
}

static void test_count(){
	std::cout << "[ test set count ]" << std::endl;
	ft::set<std::string> strset;

	strset.insert("a");
	print(strset.count("a") == 1);
	print(strset.count("b") == 0);
	std::cout << "------------------------------------" << std::endl;
}

static void test_lower_bound(){
	std::cout << "[ test set lower bound ]" << std::endl;
	ft::set<std::string> strset;
	strset.insert("a");
	strset.insert("b");
	strset.insert("c");
	strset.insert("d");

	print(*strset.lower_bound("b"));
	std::cout << "------------------------------------" << std::endl;
}

static void test_upper_bound(){
	std::cout << "[ test set upper bound ]" << std::endl;
	ft::set<std::string> strset;
	strset.insert("a");
	strset.insert("b");
	strset.insert("c");
	strset.insert("d");

	print(*strset.upper_bound("c"));
	std::cout << "------------------------------------" << std::endl;
}

static void test_equal_range(){
	std::cout << "[ test set equal range ]" << std::endl;
	ft::set<std::string> strset;
	strset.insert("a");
	strset.insert("b");
	strset.insert("c");
	strset.insert("d");

	ft::pair<ft::set<std::string>::iterator, ft::set<std::string>::iterator> itP;
	itP = strset.equal_range("a");
	print(*itP.first);
	print(*itP.second);

	itP = strset.equal_range("c");
	print(*itP.first);
	print(*itP.second);

	std::cout << "------------------------------------" << std::endl;
}

static void test_allocator(){
	std::cout << "[ test set get_allocator ]" << std::endl;
	ft::set<std::string> strset;
	strset.insert("a");
	strset.insert("b");
	strset.insert("c");
	strset.insert("d");

	ft::set<std::string> strsetCopy(strset.key_comp(), strset.get_allocator());

	strsetCopy.insert("a");
	strsetCopy.insert("b");
	strsetCopy.insert("c");
	strsetCopy.insert("d");
	std::cout << strsetCopy << std::endl;
	std::cout << "------------------------------------" << std::endl;

}

template <typename T1>
void comparison(ft::set<T1> &foo, ft::set<T1> &bar){
	std::cout << "foo: "<< foo << std::endl;
	std::cout << "bar: "<< bar << std::endl;
	if (foo < bar)
		std::cout << "foo is less than bar" << std::endl;
	if (foo > bar)
		std::cout << "foo is greater than bar" << std::endl;
	if (foo <= bar)
		std::cout << "foo is less than or equal to bar" << std::endl;
	if (foo >= bar)
		std::cout << "foo is greater than or equal to bar" << std::endl;
}


static void test_comparison(){
	std::cout << "[ test set operator comparation ]" << std::endl;
	ft::set<std::string> strset1;
	ft::set<std::string> strset2;
	std::cout << "Same size and values" << std::endl;
	strset1.insert("a");
	strset1.insert("b");
	strset2.insert("a");
	strset2.insert("b");
	comparison(strset1, strset2);
	std::cout << std::endl;
	std::cout << "Same size and values" << std::endl;
	strset1.insert("c");
	strset2.insert("d");
	comparison(strset1, strset2);
	std::cout << std::endl;
	std::cout << "Same values, different sizes" << std::endl;
	strset2.insert("c");
	comparison(strset1, strset2);

	std::cout << "------------------------------------" << std::endl;
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
		test_rbegin();
		test_rend();
		test_empty();
		test_size();
		test_max_size();
		test_insert();
		test_insert_hint();
		test_insert_range();
		test_erase();
		test_erase_value();
		test_erase_range();
		test_clear();
		test_swap();
		test_value_comp();
		test_key_comp();
		test_find();
		test_count();
		test_lower_bound();
		test_upper_bound();
		test_equal_range();
		test_allocator();
		test_comparison();
}