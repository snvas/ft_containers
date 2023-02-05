/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 00:21:11 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 14:36:59 by snovaes          ###   ########.fr       */
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
      public:
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

 	  public:
	//Construct
	//empty container constructor (default constructor)
	explicit vector(const allocator_type &alloc = allocator_type())
	    : _alloc(alloc), _data(NULL), _size(0), _capacity(0) {}
	//fill constructor
	explicit vector(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type())
	    : _alloc(alloc), _data(NULL), _size(0), _capacity(0)
	{
		this->reserve(n);
		for (size_type i = 0; i < n; i++)
			this->_alloc.construct(this->_data + i, val);
		this->_size = n;
	}
	//range constructor
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
	//copy constructor
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
	//Iterators
	//return an iterator pointing to the first element in the vector.
	iterator begin()
	{
		return iterator(this->_data);
	}

	//return an const_iterator pointing to the first element in the vector.
	const_iterator begin() const
	{
		return const_iterator(this->_data);
	}

	//return an iterator referring to the past-the-end element in the vector container.
	iterator end()
	{
		return iterator(this->_data + this->_size);
	}

	//return an const_iterator referring to the past-the-end element in the vector container.
	const_iterator end() const
	{
		return const_iterator(this->_data + this->_size);
	}

	//return a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	reverse_iterator rbegin()
	{
		return reverse_iterator(this->end() - 1);
	}

	//return a const reverse iterator pointing to the last element in the vector
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(this->_data + this->_size - 1);
	}

	//return a reverse iterator pointing to the theoretical element preceding the first element in the vector
	reverse_iterator rend()
	{
		return reverse_iterator(this->_data - 1);

	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(this->_data - 1);
	}

	//return the number of elements in the vector
	size_type size(void) const
	{
		return (this->_size);
	}

	//return the maximum number of elements that the vector can hold.
	size_type max_size(void) const
	{
		return (this->_alloc.max_size());
	}

	//Changes the size of this vector to n
	void resize(size_type n, value_type val = value_type())
	{
		if (n > this->_size)
		{
			if (n > this->_capacity)
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
		{
			for (size_type i = n; i < this->_size; i++)
				this->_alloc.destroy(this->_data + i);
		}
		this->_size = n;
	}
	//return the size of the storage space currently allocated for the vector
	size_type capacity(void)
	{
		return (this->_capacity);
	}

	//return whether the vector is empty (i.e. whether its size is 0).
	bool empty() const
	{
		if (this->_size == 0)
			return (true);
		return (false);
	}
	// Ensures that the vector capacity is at least n.
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

	//return a reference to the element at position n in the vector container
	reference operator[](size_type n)
	{
		return (this->_data[n]);
	}

	//return a const_reference to the element at position n in the vector container
	const_reference operator[](size_type n) const
	{
		return (this->_data[n]);
	}

	//return a reference to the element at position n in the vector.
	reference at(size_type n)
	{
		if (n >= _size)
			throw(std::out_of_range("ft::vector::Out-of-Range"));
		return (this->_data[n]);
	}

	//return a const_reference to the element at position n in the vector.
	const_reference at(size_type n) const
	{
		if (n >= _size)
			throw(std::out_of_range("ft::vector::Out-of-Range"));
		return (this->_data[n]);
	}

	//return a reference to the firts element in the vector
	reference front(void)
	{
		return (this->_data[0]);
	}

	const_reference front(void) const
	{
		return (this->_data[0]);
	}

	//return a reference to the last element in the vector
	reference back(void)
	{
		return (this->_data[this->_size - 1]);
	}

	const_reference back(void) const
	{
		return (this->_data[this->_size - 1]);
	}

	//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	void assign(size_type n, const value_type &val)
	{
		_size = 0;
		reserve(n);
		for (size_type i = 0; i < n; i++)
			push_back(val);
	}

	//Assigns range with iterators
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last,
	       typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0)
	{
		clear();
		reserve(last - first);
		while (first != last)
			push_back(*first++);
	}

	//Adds a new element at the end of the vector, after its current last element. 
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

	// Removes the last element in the vector, effectively reducing the container size by one.
	void pop_back(void)
	{
		if (_size){
			_alloc.destroy(_data + _size - 1);
			_size--;
		}
	}

	//Insert single element
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

	//Insert - fill constructor
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
	
	//Insert - range constructor
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

	//Removes from the vector a single element (position).
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

	// Removes from the vector a range of elements ([first,last)).
	iterator erase(iterator first, iterator last)
	{
		size_type n = last - first;
		
		while (n-- > 0) 
			this->erase(first);
		return (first);
	}

	//Exchanges the content of the container by the content of x
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

	//Removes all elements from the vector (which are destroyed)
	void clear(void)
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_data + i);
		_size = 0;
	}
	
	//Returns a copy of the allocator object associated with the vector.
	allocator_type get_allocator() const
	{
		return (this->_alloc);
	}

};
	//Based on operator ==
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}

	//Based on operator != --equivalent operation --- !(a==b)
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	//Based on operator <
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
							rhs.end()));
	}

	//Based on operator <= --equivalent operation --- !(b<a)
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	//Based on operator > --equivalent operation --- b<a
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	//Based on operator >= --equivalent operation ---!(a<b)
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	// The contents of container x are exchanged with those of y. Both container objects must be  of the same type 
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}
#endif