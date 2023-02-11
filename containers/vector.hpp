/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:21:11 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/11 13:53:20 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"


namespace ft
{
	template <class T, class Alloc = std::allocator<T> > 
	class vector{
		/*Vectors are the same as dynamic arrays with the ability to resize itself 
	automatically when an element is inserted or deleted, with their storage being 
	handled automatically by the container. Vector elements are placed in contiguous 
	storage so that they can be accessed and traversed using iterators. In vectors, 
	data is inserted at the end. Inserting at the end takes differential time, as 
	sometimes the array may need to be extended. Removing the last element takes only 
	constant time because no resizing happens. Inserting and erasing at the beginning 
	or in the middle is linear in time.*/
      public:
	/*=================
			MEMBER TYPES
	=================*/
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef ft::random_access_iterator<value_type> iterator;
	typedef ft::random_access_iterator<value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;

      private:
	allocator_type _alloc;
	value_type *_data;
	size_type _size;
	size_type _capacity;

	/*
	 * alloc = Allocator object. 
	 * The container keeps and uses an internal copy of this allocator.
	 * Member type allocator_type is the internal allocator type used by the container, 
	 * defined in vector as an alias of its second template parameter (Alloc).
	 * If allocator_type is an instantiation of the default allocator (which has no state), this is not relevant.
	 * 
	 * _size = Initial container size (i.e., the number of elements in the container at construction).
	 * Member type size_type is an unsigned integral type.
	 * 
	 * data = Value to fill the container with. Each of the n elements in the container 
	 * will be initialized to a copy of this value.
	 * Member type value_type is the type of the elements in the container, 
	 * defined in vector as an alias of its first template parameter (T).
	 * 
	*/
 	  public:
	/*=================
	      CONSTRUCTORS
	  =================*/
	/**
	 * === empty container constructor (default constructor)
	 * Constructs an empty container, with no elements.
	*/
	explicit vector(const allocator_type &alloc = allocator_type())
	    : _alloc(alloc), _data(NULL), _size(0), _capacity(0) {}
		
	/**
	 * === fill constructor
	 * Constructs a container with n elements. Each element is a copy of val.
	*/
	explicit vector(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type())
	    : _alloc(alloc), _data(NULL), _size(0), _capacity(0)
	{
		this->reserve(n);
		for (size_type i = 0; i < n; i++)
			this->_alloc.construct(this->_data + i, val);
		this->_size = n;
	}
	/**
	 * === range constructor
	 * Constructs a container with as many elements as the range
	 * [first,last), with each element constructed from its corresponding
	 * element in that range, in the same order.
	*/
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
	       const allocator_type &alloc = allocator_type(),
	       typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
	{
		this->_alloc = alloc;
		this->_size = last - first;
		this->_capacity = _size;
		this->_data = _alloc.allocate(_size);
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(&this->_data[i], *first);
			first++;
		}
	}
	/**
	 * ==== copy constructor
	 * Constructs a container with a copy of each of the elements in x, in the same order.
	*/
	vector(const vector &x)
	    : _alloc(x._alloc), _size(x._size), _capacity(x._size)
	{
		if (this->_capacity > 0)
			this->_data = this->_alloc.allocate(this->_capacity);
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.construct(this->_data + i, x._data[i]);
	}
	
	//Destructor
	~vector(void)
	{
		for (size_type i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_data + i);
		if (this->_capacity)
		{
			this->_alloc.deallocate(this->_data, this->_capacity);
		}
	}

	//Operator =
	vector &operator=(const vector &other){
		if (this != &other){
			clear();
			_alloc.deallocate(_data, _capacity);
			_size = other._size;
			_capacity = other._capacity;
			_alloc = other._alloc;
			if (_capacity)
				_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, other._data[i]);			
		}
		return *this;
	}
	/*************************** Iterators *****************************/
	/**
	  * @return an iterator pointing to the first element in the vector.
	 */
	iterator begin()
	{
		return iterator(this->_data);
	}

	/**
	  * @return an const_iterator pointing to the first element in the vector.
	 */
	const_iterator begin() const
	{
		return const_iterator(this->_data);
	}

	/**
	 * @return an iterator referring to the past-the-end element in the vector container.
	*/
	iterator end()
	{
		return iterator(this->_data + this->_size);
	}

	/**
	 * @return an const_iterator referring to the past-the-end element in the vector container.
	*/
	const_iterator end() const
	{
		return const_iterator(this->_data + this->_size);
	}

	/**
	 * @return a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	 * rbegin points to the element right before the one that would be pointed to by member end.
	*/
	reverse_iterator rbegin()
	{
		return reverse_iterator(this->end() - 1);
	}

	/**
	 * @return a const reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	 * rbegin points to the element right before the one that would be pointed to by member end.
	*/
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(this->_data + this->_size - 1);
	}

	/**
	 * @return a reverse iterator pointing to the theoretical element preceding the first 
	 * 			element in the vector (which is considered its reverse end).
	 * The range between vector::rbegin and vector::rend contains all 
	 * the elements of the vector (in reverse order).
	*/
	reverse_iterator rend()
	{
		return reverse_iterator(this->_data - 1);

	}

	/**
	 * @return a const reverse iterator pointing to the theoretical element preceding the first 
	 * 			element in the vector (which is considered its reverse end).
	 * The range between vector::rbegin and vector::rend contains all 
	 * the elements of the vector (in reverse order).
	*/
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(this->_data - 1);
	}

	/***************************Capacity*****************************/
	/**
	 * @return the number of elements in the vector
	*/
	size_type size(void) const
	{
		return (this->_size);
	}

	/**
	 * @return the maximum number of elements that the vector can hold.
	*/
	size_type max_size(void) const
	{
		return (this->_alloc.max_size());
	}

	/**
	 * Changes the size of this vector to n. If n > size(), one or more copies of t
	 * are added to the end of the vector to reach the desired size. If the new size
	 * is smaller than the current size, elements are erased from the end 
	 * to reach the new size.
	 * Resizes the container so that it contains n elements.
	 * @param n  number of elements to resize
	*/
	void resize(size_type n, value_type val = value_type())
	{
		if (n > this->_size)
		// If n is greater than the current container size, the content is expanded by 
		//inserting at the end as many elements as needed to reach a size of n.
		{
			if (n > this->_capacity)
			//If n is also greater than the current container capacity, an automatic 
			//reallocation of the allocated storage space takes place.
			{
				if (n > this->_capacity * 2)
					this->reserve(n);
				else
					this->reserve(this->_capacity * 2);
			}
			for (size_type i = this->_size; i < n; i++)
				this->_alloc.construct(this->_data + i, val);
		}
		else
		{// If n is smaller than the current container size, the content is reduced to 
		//its first n elements, removing those beyond (and destroying them).
			for (size_type i = n; i < this->_size; i++)
				this->_alloc.destroy(this->_data + i);
		}
		this->_size = n;
	}
	
	/**
	 * @return the size of the storage space currently allocated 
	 * for the vector, expressed in terms of elements
	 * Returns the maximum number of items that can be stored 
	 * in the vector before it musta be resized.
	*/
	size_type capacity(void)
	{
		return (this->_capacity);
	}

	/**
	 * @return whether the vector is empty (i.e. whether its size is 0).
	*/
	bool empty() const
	{
		if (this->_size == 0)
			return (true);
		return (false);
	}
	
	/**
	 * Ensures that the vector capacity is at least n. Call reserve to 
	 * avoid the need to reallocate the vector repeatedly when you know
	 * the vector will grow by small increments to a large size, or when
	 * you want to ensure iterators do not become invalid after inserting
	 * one or more items. Note that size() does not change. 
	*/
	void reserve(size_type n)
	{
		if (n > this->_capacity)
		{
			value_type *tmp = this->_alloc.allocate(n);
			for (size_type i = 0; i < this->_size; i++)
			{
				this->_alloc.construct(tmp + i, this->_data[i]);
				this->_alloc.destroy(this->_data + i);
			}
			if (this->_capacity > 0)
				this->_alloc.deallocate(_data, _capacity);
			this->_data = tmp;
			this->_capacity = n;
		}
	}

	/***************************Element Access*****************************/
	/**
	 * @return a reference to the element at position n in the vector container.
	*/
	reference operator[](size_type n)
	{
		return (this->_data[n]);
	}

	/**
	 * @return a const_reference to the element at position n in the vector container.
	*/
	const_reference operator[](size_type n) const
	{
		return (this->_data[n]);
	}

	/**
	 * @return a reference to the element at position n in the vector.
	*/
	reference at(size_type n)
	{
		if (n >= _size)
			throw(std::out_of_range("ft::vector::Out-of-Range"));
		return (this->_data[n]);
	}

	/**
	 * @return a const_reference to the element at position n in the vector.
	*/
	const_reference at(size_type n) const
	{
		if (n >= _size)
			throw(std::out_of_range("ft::vector::Out-of-Range"));
		return (this->_data[n]);
	}

	/**
	 * @return a reference to the firts element in the vector
	*/
	reference front(void)
	{
		return (this->_data[0]);
	}

	/**
	 * @return a const_reference to the firts element in the vector
	*/
	const_reference front(void) const
	{
		return (this->_data[0]);
	}

	/**
	 * @return a reference to the last element in the vector
	*/
	reference back(void)
	{
		return (this->_data[this->_size - 1]);
	}

	/**
	 * @return a const_reference to the last element in the vector
	*/
	const_reference back(void) const
	{
		return (this->_data[this->_size - 1]);
	}

	/*=================
		MODIFIERS
	=================*/
	/**
	 * Assigns new contents to the vector, replacing its current 
	 * contents, and modifying its size accordingly.
	 * In the fill version, the new contents are n elements, 
	 * each initialized to a copy of val.
	 * @param val new contents
	 * @param size new size
	*/
	void assign(size_type n, const value_type &val)
	{
		_size = 0;
		reserve(n);
		for (size_type i = 0; i < n; i++)
			push_back(val);
	}

	/**
	 * Assigns range with iterators
	 * In the range version, the new contents are elements 
	 * constructed from each of the elements 
	 * in the range between first and last, in the same order.
	*/
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last,
	       typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0)
	{
		clear();
		reserve(last - first);
		while (first != last)
			push_back(*first++);
	}

	/**
	 * Adds a new element at the end of the vector, after its current last element. 
	 * The content of val is copied (or moved) to the new element.
	 * @param val The new element to be added
	*/  
	void push_back(const value_type &val)
	{
		if (_size + 1 > _capacity)
		{
			if (_capacity > 0)
				reserve(_capacity * 2);
			else
				reserve(1);
		}
		_alloc.construct(_data + _size, val);
		_size++;
	}

	/**
	 * Removes the last element in the vector, effectively reducing the 
	 * container size by one. This destroys the removed element.
	*/
	void pop_back(void)
	{
		if (_size){
			_alloc.destroy(_data + _size - 1);
			_size--;
		}
	}

	/** Insert single element
	 * The vector is extended by inserting new elements before the element at the specified position, 
	 * effectively increasing the container size by the number of elements inserted.
	 * @param position the position to insert the element before
	 * @param val element to be inserted
	 * @return the number of elements inserted
	*/ 
	iterator insert(iterator position, const value_type &val)
	{
		vector tmp;
		size_type index = position - begin();
		size_type tmp_end = end() - position;
		tmp.assign(position, end());
		_size = index;
		push_back(val);
		for (size_type i = 0; i < tmp_end; ++i)
			push_back(tmp[i]);
		return iterator(_data + index);
	}

	/**
	 * fill constructor
	 * Extends vector by inserting new elements in the container. 
	 * Reallocation happens if there is need of more space
	 * This function increases container size by n.
	 * @param position - index in the vector where new element to be inserted
	 * @param n  - number of elements to be inserted
	 * @param val - Value to be assigned to newly inserted element.
	*/
	void insert(iterator position, size_type n, const value_type &val)
	{
		vector tmp(position, end());
		size_type index = position - begin();

		_size = index;
		for (size_type i = 0; i < n; i++)
			push_back(val);
		for (size_type i = 0; i < tmp.size(); i++)
			push_back(tmp[i]);
	}
	
	/**
	 * range constructor
	 * extends vector by inserting new elements in the container. 
	 * Reallocation happens if there is need of more space
	 * This function increases container size.
	 * @param position - index in the vector where new element to be inserted
	 * @param first - input iterator to the initial position in the range
	 * @param second - input iterator to the final position in the range
	*/
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		vector tmp(position, end());
		size_type index = position - begin();

		_size = index;
		while (first != last)
			push_back(*first++);
		for (size_type i = 0; i < tmp.size(); i++)
			push_back(tmp[i]);
	}

	/**
	 * Removes from the vector a single element (position).
	 * This effectively reduces the container size by the number of elements removed, which are destroyed.
	 * @param position the position of the element to be removed
	*/
	iterator erase(iterator position)
	{
		iterator it;
		it = position;
		it++;
		while (it != end()){
			_alloc.destroy(&(*(it - 1)));
			*(it - 1) = *it;
			it++;
		}
		_size--;
		return position;
	}

	/**
	 * Removes from the vector a range of elements ([first,last)).
	 * Iterators specifying a range within the vector to be removed: [first,last). i.e., 
	 * the range includes all the elements between first and last, including the element 
	 * pointed by first but not the one pointed by last.
	 * @param first the first vector to be removed
	 * @param last the last vector to be removed
	 */
	iterator erase(iterator first, iterator last)
	{
		size_type n = last - first;
		
		while (n-- > 0) 
			this->erase(first);
		return (first);
	}

	/**
	 * Exchanges the content of the container by the content of x, 
	 * which is another vector object of the same type. Sizes may differ.
	 * @param x the vector object to be modified
	*/ 
	void swap(vector &x)
	{
		value_type *temp_data = x._data;
		x._data = _data;
		_data = temp_data;
		size_type temp_size = x._size;
		x._size = _size;
		_size = temp_size;
		size_type temp_capacity = x._capacity;
		x._capacity = _capacity;
		_capacity = temp_capacity;
	}

	/**
	 * Removes all elements from the vector (which are destroyed), 
	 * leaving the container with a size of 0.
	*/
	void clear(void)
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_data + i);
		_size = 0;
	}
	
	/**
	 * Returns a copy of the allocator object associated with the vector.
	*/
	allocator_type get_allocator() const
	{
		return (this->_alloc);
	}

};
	/***************************Relational Operators*****************************/
	//Performs the appropriate comparison operation between the vector containers lhs and rhs.

	/**
	 * Based on operator ==
	 * vector are considered equivalent if their sizes are equal, 
	 * and if corresponding elements compare equal.
	*/
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}

	/**
	 * Based on operator != --equivalent operation --- !(a==b)
	*/
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	/**
	 * Based on operator <
	 * The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, 
	 * which compares the elements sequentially using operator< in a reciprocal manner 
	 * (i.e., checking both a<b and b<a) and stopping at the first occurrence.
	*/
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
							rhs.end()));
	}

	/**
	 * Based on operator <= --equivalent operation --- !(b<a)
	 */
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	/**
	 * Based on operator > --equivalent operation --- b<a
	 */
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	/**
	 * Based on operator >= --equivalent operation ---!(a<b)
	*/
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	/**
	 * The contents of container x are exchanged with those of y. Both container objects must be 
	 * of the same type (same template parameters), although sizes may differ.
	*/
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}
#endif