/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:13:31 by snovaes           #+#    #+#             */
/*   Updated: 2023/01/13 22:36:14 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
template <class T, class Container = ft::vector<T> > class stack
{
      public:
	/***************************Member Types*****************************/
	typedef T value_type;
	typedef Container container_type;
	typedef typename Container::size_type size_type;

      protected:
	container_type c;

      public:
	// default constructor - Constructs a stack container adaptor object.
	explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

	//copy constructor
	stack(const stack &Obj) : c(Obj.c) {}

	//destructor
	~stack() {}

	//assign operator
	stack &operator=(const stack &Obj) {
		if (this != &Obj)
			c = Obj.c;
		return (*this);
	}
	
	// Test whether container is empty - return true if the stack is empty. i.e. whether its size is zero.
	bool empty() const {
		return (this->c.empty());
	}

	// Return size - return the number of element in the stack
	size_type size() const {
		return (this->c.size());
	}

	// Access next element - Returns a reference to the top element in the stack.
	value_type &top() {
		return (this->c.back());
	}

	// return a read-only reference to the first element in the stack
	const value_type &top() const {
		return (this->c.back());
	}

	// Insert element - Inserts a new element at the top of the stack, above its current top element. 
	//The content of this new element is initialized to a copy of val.
	void push(const value_type &val) {
		this->c.push_back(val);
	}
	
	//Remove top element - Removes the element on top of the stack, effectively reducing its size by one.
	void pop(void)
	{
		this->c.pop_back();
	}
	/*=================
	RELATIONAL OPERATORS
	=================*/
	// stack equality comparison ==
	friend bool operator==(const stack<T, Container> &lhs,
			       const stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}
	// based on operator !=
	friend bool operator!=(const stack<T, Container> &lhs,
			       const stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}
	// stack ordering relation <
	friend bool operator<(const stack<T, Container> &lhs,
			      const stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}
	// based on operator <=
	friend bool operator<=(const stack<T, Container> &lhs,
			       const stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}
	// based on operator >
	friend bool operator>(const stack<T, Container> &lhs,
			      const stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}
	// based on operator >=
	friend bool operator>=(const stack<T, Container> &lhs,
			       const stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
};
} 
#endif