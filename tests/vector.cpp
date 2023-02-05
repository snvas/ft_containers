/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:21:21 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 13:51:12 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"

template <class T>
void print_vector(T& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << "\n";
	std::cout << "size: " << vector.size() << "\n";
	std::cout << "capacity: " << vector.capacity() << "\n";
}

template <class T> void print_vector_content(ft::vector<T> &vec) {
	typename ft::vector<T>::iterator begin(vec.begin());
	typename ft::vector<T>::iterator end(vec.end());
	std::cout << "vector content: ";
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "max_size: " << vec.max_size() << std::endl;
}

template <class T> void print_vector_simplecontent(ft::vector<T> &vec) {
	typename ft::vector<T>::iterator begin(vec.begin());
	typename ft::vector<T>::iterator end(vec.end());
	std::cout << "vector content: ";
	while (begin != end) {
		std::cout << *begin << " ";
		begin++;
	}
	std::cout << std::endl;
}

void test_vector(void) {
	std::cout << "====================================" << std::endl;
	std::cout << "                VECTOR              " << std::endl;
	std::cout << "====================================" << std::endl;
{
	std::cout << "TEST: Constructors" << std::endl;
	std::cout << "\n[ CONSTRUCTOR DEFAULT ]\n";
	ft::vector<std::string> emptyVec;
	ft::vector<std::string> notEmptyVec;
	std::cout << "notEmptyVec: ";
	print_vector(notEmptyVec);
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ FILL CONSTRUCTOR ]" << std::endl;
	ft::vector<std::string> fillVec(6, "abc");
	ft::vector<std::string> otherVec(3, "AAA");
	std::cout << "fillVec: ";
	print_vector(fillVec);
	std::cout << "------------------------------------" << std::endl;
	std::cout << "otherVec: ";
	print_vector(otherVec);
	notEmptyVec.push_back("AAA");
	notEmptyVec.push_back("BBB");
	notEmptyVec.push_back("CCC");
	notEmptyVec.push_back("DDD");
	notEmptyVec.push_back("EEE");
	notEmptyVec.push_back("FFF");
	notEmptyVec.push_back("GGG");
	notEmptyVec.push_back("HHH");
	notEmptyVec.push_back("III");
	notEmptyVec.push_back("JJJ");
	notEmptyVec.push_back("KKK");
	notEmptyVec.push_back("LLL");
	notEmptyVec.push_back("MMM");
	std::cout << "------------------------------------" << std::endl;
	std::cout << "notEmptyVec: ";
	print_vector(notEmptyVec);
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ RANGE CONSTRUCTOR ]" << std::endl;
	int n[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	ft::vector<int> MyVec(n, n + 10);
	std::cout << "MyVec: ";
	print_vector(MyVec);
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ COPY CONSTRUCTOR ]\n";
	ft::vector<int> MyVec_copy(MyVec.begin(), MyVec.end());
	std::cout << "MyVec_copy: ";
	print_vector(MyVec_copy);
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ ASSIGNMENT OPERATOR = ]\n";
	ft::vector<int> IntVec = MyVec_copy;
	ft::vector<std::string> NewVec = notEmptyVec;
	std::cout << "\nIntVec: ";
	print_vector(IntVec);
	std::cout << "NewVec: ";
	print_vector(NewVec);

	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ ITERATORS ]" << std::endl;
	ft::vector<std::string>::iterator it;
	ft::vector<std::string>::iterator it2(notEmptyVec.begin());
	ft::vector<std::string>::iterator it3;
	it = it2;
	it3 = it2 + 5;
	std::cout << "assignment operator" << std::endl;
	std::cout << "*it: " << *it << std::endl;
	std::cout << "*it2: " << *it2 << std::endl;
	std::cout << "*it3: " << *it3 << std::endl;
	// equality/inequality operators
	std::cout << "equality/inequality operators" << std::endl;
	std::cout << "equality operator it == it2: " << (it == it2) << std::endl;
	std::cout << "equality operator it == it3: " << (it == it3) << std::endl;
	std::cout << "inequality operator it != it2: " << (it != it2) << std::endl;
	std::cout << "inequality operator it != it3: " << (it != it3) << std::endl;
	std::cout << "------------------------------------" << std::endl;
	// dereference
	std::cout << "dereference" << std::endl;
	std::cout << "*it3: " << *it3 << std::endl;
	// increment and decrement iterator
	std::cout << "------------------------------------" << std::endl;
	std::cout << "increment and decrement iterator" << std::endl;
	std::cout << "*(++it3): " << *(++it3) << std::endl;
	std::cout << "*(it3): " << *(it3) << std::endl;
	std::cout << "*(--it3): " << *(--it3) << std::endl;
	std::cout << "*(it3): " << *(it3) << std::endl;
	std::cout << "*(it3++): " << *(it3++) << std::endl;
	std::cout << "*(it3): " << *(it3) << std::endl;
	std::cout << "*(it3--): " << *(it3--) << std::endl;
	std::cout << "*(it3): " << *(it3) << std::endl;
	std::cout << "------------------------------------" << std::endl;
	// arithmetic operator
	std::cout << "arithmetic operator: " << std::endl;
	it3 = it2 + 6;
	std::cout << "it + 6: " << *it3 << std::endl;
	it2 = it3 - 6;
	std::cout << "it - 6: " << *it2 << std::endl;
	std::cout << "------------------------------------" << std::endl;
	// relational operator
	std::cout << "relational operator: " << std::endl;
	std::cout << "it2 < it3: " << (it2 < it3) << std::endl;
	std::cout << "it2 > it3: " << (it2 > it3) << std::endl;
	std::cout << "it2 <= it3: " << (it2 <= it3) << std::endl;
	std::cout << "it2 >= it3: " << (it2 >= it3) << std::endl;
	std::cout << "it2 <= it: " << (it2 <= it) << std::endl;
	std::cout << "it2 >= it: " << (it2 >= it) << std::endl;
	std::cout << "------------------------------------" << std::endl;
	// compound assignment operations
	std::cout << "compound assignment operations: " << std::endl;
	std::cout << "*(it3 -= 1): " << *(it3 -= 1) << std::endl;
	std::cout << "*it3: " << *it3 << std::endl;
	std::cout << "*(it3 += 1): " << *(it3 += 1) << std::endl;
	std::cout << "*it3: " << *it3 << std::endl;
	std::cout << "------------------------------------" << std::endl;
	// offset dereference operator
	std::cout << "offset dereference operator: " << std::endl;
	std::cout << "it2[6]: " << (it2[6]) << std::endl;
	/* Reverse Iterators*/
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ REVERSE ITERATORS ]" << std::endl;
	std::cout << "notEmptyVec: ";
	print_vector(notEmptyVec);
	ft::vector<std::string>::reverse_iterator reverseit;
	ft::vector<std::string>::reverse_iterator reverseit2(notEmptyVec.rbegin());
	ft::vector<std::string>::reverse_iterator reverseit3;
	reverseit = reverseit2;
	reverseit3 = reverseit2;
	std::cout << "assignment reverseiterator operator: " << *reverseit << std::endl;
	// dereference
	std::cout << "*reverseit3: " << *reverseit3 << std::endl;
	// arithmetic operator
	std::cout << "arithmetic reverseiterator operators" << std::endl;
	reverseit3 = reverseit2 + 4;
	std::cout << "reverseit + 4: " << *reverseit3 << std::endl;
	reverseit2 = reverseit3 - 2;
	std::cout << "reverseit - 2: " << *reverseit2 << std::endl;
	// increment and decrement reverseiterator
	std::cout << "------------------------------------" << std::endl;
	std::cout << "increment and decrement reverseiterator operator" << std::endl;
	std::cout << "*(++reverseit3): " << *(++reverseit3) << std::endl;
	std::cout << "*(reverseit3): " << *(reverseit3) << std::endl;
	std::cout << "*(--reverseit3): " << *(--reverseit3) << std::endl;
	std::cout << "*(reverseit3): " << *(reverseit3) << std::endl;
	std::cout << "*(reverseit3++): " << *(reverseit3++) << std::endl;
	std::cout << "*(reverseit3): " << *(reverseit3) << std::endl;
	std::cout << "*(reverseit3--): " << *(reverseit3--) << std::endl;
	std::cout << "*(reverseit3): " << *(reverseit3) << std::endl;
	// compound assignment operations
	std::cout << "------------------------------------" << std::endl;
	std::cout << "compound assignment reverseiterator operations" << std::endl;
	std::cout << "*(reverseit3 -= 1): " << *(reverseit3 -= 1) << std::endl;
	std::cout << "*reverseit3: " << *reverseit3 << std::endl;
	std::cout << "*(reverseit3 += 1): " << *(reverseit3 += 1) << std::endl;
	std::cout << "*reverseit3: " << *reverseit3 << std::endl;
	// offset dereference operator
	ft::vector<std::string>::reverse_iterator reverseit4(notEmptyVec.rbegin());
	std::cout << "------------------------------------" << std::endl;
	std::cout << "offset dereference reverseiterator operator" << std::endl;
	std::cout << "reverseit4[6]: " << (reverseit4[6]) << std::endl;
	// equality/inequality operators
	std::cout << "equality reverseiterator operator: " << (it == it2) << std::endl;
	std::cout << "equality reverseiterator operator: " << (it == it3) << std::endl;
	std::cout << "inequality reverseiterator operator: " << (it != it2) << std::endl;
	std::cout << "inequality reverseiterator operator: " << (it != it3) << std::endl;
	// relational operator
	std::cout << "relational reverseiterator operator" << std::endl;
	std::cout << "it2 < it3: " << (it2 < it3) << std::endl;
	std::cout << "it2 > it3: " << (it2 > it3) << std::endl;
	std::cout << "it2 <= it3: " << (it2 <= it3) << std::endl;
	std::cout << "it2 >= it3: " << (it2 >= it3) << std::endl;
	std::cout << "it2 <= it: " << (it2 <= it) << std::endl;
	std::cout << "it2 >= it: " << (it2 >= it) << std::endl;
	/*	Constructor that need iterators	*/
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ RANGE CONSTRUCTOR ]" << std::endl;
	ft::vector<int> first(15, 100);
	ft::vector<int> range_vec(first.begin(), first.end());
	ft::vector<int>::iterator range_begin(range_vec.begin());
	ft::vector<int>::iterator range_end(range_vec.end());
	while (range_begin != range_end) {
		std::cout << *range_begin << " ";
		range_begin++;
	}
	std::cout << std::endl;
	std::cout << "range_vec" << std::endl;
	print_vector_content(range_vec);	
	{ // NOTE - Iterator to beginning
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ ITERATOR BEGIN ]" << std::endl;
		ft::vector<int> myvector1;
		for (int i = 1; i <= 5; i++)
			myvector1.push_back(i);
		std::cout << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector1.begin(); it != myvector1.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	{ // NOTE - Iterator to end
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ ITERATOR END ]" << std::endl;
		ft::vector<int> myvector1;
		for (int i = 1; i <= 5; i++)
			myvector1.push_back(i);
		std::cout << "myvector contains:";
		for (ft::vector<int>::iterator it = (myvector1.end() - 1); it != (myvector1.begin() - 1); it--)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	//Member Functions Iterators
	std::cout << "------------------------------------" << std::endl;
	std::cout << "[ MEMBER FUNCTIONS ITERATORS ]" <<std::endl;
	ft::vector<std::string>::iterator it_begin(notEmptyVec.begin());
	std::cout << "it_begin: " << *it_begin << std::endl;
	ft::vector<std::string>::iterator it_end(notEmptyVec.end());
	it_end--;
	std::cout << "it_end--: " << *it_end << std::endl;
	ft::vector<std::string>::const_iterator it_cbegin(notEmptyVec.begin());
	std::cout << "it_const_begin: " << *it_cbegin << std::endl;
	ft::vector<std::string>::const_iterator it_cend(notEmptyVec.end());
	std::cout << "vector content:";
	while (it_cbegin != it_cend)
	{
		std::cout << " " << *it_cbegin;
		it_cbegin++;
	}
	std::cout << std::endl;
	it_cend--;
	std::cout << "it_const_end--: " << *it_cend << std::endl;
	it_cend = it_begin;
	std::cout << "it_const_end assigned to a not const iterator: " << *it_cend << std::endl;
	//reverse iterators
	std::cout << "\nreverse iterators" << std::endl;
	ft::vector<std::string>::reverse_iterator it_rbegin(notEmptyVec.rbegin());
	std::cout << "it_rbegin: " << *it_rbegin << std::endl;
	ft::vector<std::string>::reverse_iterator it_rend(notEmptyVec.rend());
	it_rend--;
	std::cout << "it_rend--: " << *it_rend << std::endl;
	ft::vector<std::string>::const_reverse_iterator it_crbegin(notEmptyVec.rbegin());
	std::cout << "it_const_rbegin: " << *it_crbegin << std::endl;
	ft::vector<std::string>::const_reverse_iterator it_crend(notEmptyVec.rend());
	std::cout << "vector content:";
	while (it_crbegin != it_crend)
	{
		std::cout << " " << *it_crbegin;
		it_crbegin++;
	}
	std::cout << std::endl;
	{// NOTE - Change size
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ CHANGE SIZE ]" << std::endl;
		ft::vector<int> myvector1;
		for (int i = 1; i < 10; i++)
			myvector1.push_back(i);
		myvector1.resize(9);
		print_vector_content(myvector1);
		std::cout << std::endl;
		myvector1.resize(12, 100);
		print_vector_content(myvector1);
		std::cout << std::endl;
		myvector1.resize(15);
		print_vector_content(myvector1);
		std::cout << std::endl;
	}
	{// NOTE - Test whether vector is empty
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ TESTE IF VECTOR IS EMPTY ]" << std::endl;
		ft::vector<int> myvector1;
		int sum1(0);
		for (int i = 1; i <= 10; i++)
			myvector1.push_back(i);
		print_vector_content(myvector1);
		std::cout <<  (!myvector1.empty() ? "Não está vazio" : "Está Vazio") << std::endl;
		while (!myvector1.empty()) {
			sum1 += myvector1.back();
			myvector1.pop_back();
		}
		std::cout << "Soma dos valores no vetor: " << sum1 << std::endl;
		std::cout << std::endl;
		std::cout <<  (!myvector1.empty() ? "Não está vazio" : "Está Vazio") << std::endl;
		print_vector_content(myvector1);
	}
	{// NOTE - Access element []
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ ACCESS ELEMENT [] ]" << std::endl;
		ft::vector<int> myvector1(10);
		ft::vector<int>::size_type sz1 = myvector1.size();
		for (unsigned i = 0; i < sz1; i++)
			myvector1[i] = i;
		print_vector_simplecontent(myvector1);
	}
	{// NOTE - Access element at
		std::cout << "------------------------------------"  << std::endl;
		std::cout << "[ ACCESS ELEMENT AT ]" << std::endl;
		ft::vector<int> myvector1(10);
		for (unsigned i = 0; i < myvector1.size(); i++)
			myvector1.at(i) = i;
		print_vector_simplecontent(myvector1);
	}
	{// NOTE - Access first element front()
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ TEST FRONT ] " << std::endl;
		ft::vector<int> myvector1;
		myvector1.push_back(78);
		print_vector_simplecontent(myvector1);
		std::cout << std::endl;
		myvector1.push_back(16);
		print_vector_simplecontent(myvector1);
		std::cout << std::endl;
		myvector1.front() -= myvector1.back();
		std::cout << "myvector.front() is now " << myvector1.front() << std::endl;
		print_vector_simplecontent(myvector1);
	}
	{ // NOTE - Access last element back()
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ TEST  BACK ]" << std::endl;
		ft::vector<int> myvector1;
		myvector1.push_back(10);
		while (myvector1.back() != 0) {
			myvector1.push_back(myvector1.back() - 1);
		}
		std::cout << "back = " << myvector1.back() << std::endl;
		print_vector_simplecontent(myvector1);
	}
	{ // NOTE - Assign vector content
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ ASSIGN VECTOR CONTENT ]" << std::endl;
		ft::vector<int> first1;
		ft::vector<int> second1;
		ft::vector<int> third1;
		first1.assign(7, 100);
		ft::vector<int>::iterator it1;
		it1 = first1.begin() + 1;
		second1.assign(it1, first1.end() - 1);
		int myints1[] = {1776, 7, 4};
		third1.assign(myints1, myints1 + 3);
		std::cout << "Size of first: " << int(first1.size()) << std::endl;
		std::cout << "Size of second: " << int(second1.size()) << std::endl;
		std::cout << "Size of third: " << int(third1.size()) << std::endl;
		std::cout << std::endl;
		print_vector(first1);
		std::cout << std::endl;
		print_vector(second1);
		std::cout << std::endl;
		print_vector(third1);
	}
	{ // NOTE - Delete last element
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ DELETE LAST ELEMENT WITH POP_BACK ]" << std::endl;
		ft::vector<int> myvector1;
		int sum1(0);
		myvector1.push_back(100);
		myvector1.push_back(200);
		myvector1.push_back(300);
		print_vector_simplecontent(myvector1);
		while (!myvector1.empty()) {
			sum1 += myvector1.back();
			myvector1.pop_back();
		}
		std::cout << "Sum of elements: " << sum1 << std::endl;
		std::cout << "After pop_back() " << std::endl;
		print_vector_content(myvector1);
	}
	{ // NOTE - Clear content
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ CLEAR CONTENT ]" << std::endl;
		ft::vector<int> myvector1;
		myvector1.push_back(100);
		myvector1.push_back(200);
		myvector1.push_back(300);
		print_vector_content(myvector1);
		myvector1.clear();
		std::cout << std::endl;
		std::cout << "After clear()" << std::endl;
		std::cout << "size: " << myvector1.size() << std::endl;
		std::cout << "capacity: " << myvector1.capacity() << std::endl;
		std::cout << std::endl;
		std::cout << "push_back add" << std::endl;
		myvector1.push_back(1101);
		myvector1.push_back(2202);
		print_vector_content(myvector1);
	}
	{ // NOTE - Swap content
		std::cout << "------------------------------------" << std::endl;
		std::cout << "[ SWAP CONTENT ]" << std::endl;
		ft::vector<int> myvector1(3, 100); // three ints with a value of 100
		ft::vector<int> myvector2(5, 200); // five ints with a value of 200
		print_vector_simplecontent(myvector1);
		print_vector_simplecontent(myvector2);
		std::cout << "Size myvector1 before swap: " << myvector1.size() << std::endl;
		std::cout << "Capacity myvector1 before swap: " << myvector1.capacity() << std::endl;
		std::cout << std::endl;
		std::cout << "Size myvector2 before swap: " << myvector2.size() << std::endl;
		std::cout << "Capacity myvector2 before swap: " << myvector2.capacity() << std::endl;
		myvector1.swap(myvector2);
		std::cout << std::endl;
		std::cout << "Size myvector1 after swap: " << myvector1.size() << std::endl;
		std::cout << "Capacity myvector1 after swap: " << myvector1.capacity() << std::endl;
		std::cout << std::endl;
		std::cout << "Size myvector2 after swap: " << myvector2.size() << std::endl;
		std::cout << "Capacity myvector2 after swap: " << myvector2.capacity() << std::endl;
		std::cout << "\nmyvector1" << std::endl;
		print_vector_content(myvector1);
		std::cout << "\nmyvector2" << std::endl;
		print_vector_content(myvector2);
	}
	{ // NOTE - Get allocator
		std::cout << "------------------------------------"
			  << std::endl;
		std::cout << "[ GET ALLOCATOR ]" << std::endl;
		ft::vector<int> myvector;
		int *p;
		unsigned int i;
		p = myvector.get_allocator().allocate(5);
		for (i = 0; i < 5; i++)
			myvector.get_allocator().construct(&p[i], i);
		std::cout << "The allocated array contains:";
		for (i = 0; i < 5; i++)
			std::cout << ' ' << p[i];
		std::cout << std::endl;
		for (i = 0; i < 5; i++)
			myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p, 5);
	}
	{//Insert elements
		std::cout << "------------------------------------"
			  << std::endl;
		std::cout << "[ INSERT ELEMENTS ]" << std::endl;
		ft::vector<int> myvector1(3, 100); // three ints with a value of 100
		ft::vector<int> myvector2(5, 200); // five ints with a value of 200
		std::cout << "myvector1 contains:";
		for (ft::vector<int>::iterator it = myvector1.begin(); it != myvector1.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
		std::cout << "myvector2 contains:";
		for (ft::vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	} // NOTE - Relational operators for vector
	{
		std::cout << "------------------------------------"
			  << std::endl;
		std::cout << "[ RELATIONAL OPERATORS ]"
			  << std::endl;
		ft::vector<int> myvector1(1, 200);
		ft::vector<int> myvector2(0);
		std::cout << "myvector1 : ";
		print_vector_simplecontent(myvector1);
		std::cout << "myvector2 : ";
		print_vector_simplecontent(myvector2);
		if (myvector1 == myvector2)
			std::cout << "myvector1 and myvector2 are equal\n";
		if (myvector1 != myvector2)
			std::cout << "myvector1 and myvector2 are not equal\n";
		if (myvector1 < myvector2)
			std::cout << "myvector1 is less than myvector2\n";
		if (myvector1 > myvector2)
			std::cout << "myvector1 is greater than myvector2\n";
		if (myvector1 <= myvector2)
			std::cout << "myvector1 is less than or equal to myvector2\n";
		if (myvector1 >= myvector2)
			std::cout << "myvector1 is greater than or equal to myvector2\n";
	}
}





}	