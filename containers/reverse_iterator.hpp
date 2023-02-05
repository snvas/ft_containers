/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:13:44 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 20:33:14 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft{
			/***************************Reverse Iterator**************************/
	/*This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	https://cplusplus.com/reference/iterator/reverse_iterator/*/
	template<class Iterator>
	class reverse_iterator{

	 public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;

		// default constructor - Constructs a reverse iterator that points to no object.
		reverse_iterator(void) {}; 

		// constructor from an iterator - Constructs a reverse iterator from some original iterator it. 
		//The behavior of the constructed object replicates the original, except that it iterates through its pointed elements in the reverse order.
		explicit reverse_iterator(iterator_type it) : _current(it) {}; 
		
		//copy constructor - Constructs a reverse iterator from some other reverse iterator.
		reverse_iterator(const reverse_iterator<Iterator>& temp){
			_current = temp.base();
		} 
		
		//destructor
		~reverse_iterator(void) {};

		//base - Returns a copy of the base iterator.
		iterator_type base(void) const { 
			return (_current);
		}

			/***************************Operator Overloading**************************/
		//Dereference iterator - Returns a reference to the element pointed to by the iterator.
		reference operator*(void) const { 
			return (*(_current)); }
		
		//Addition operator - Returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to.
		reverse_iterator operator+(difference_type n) const{
			return (reverse_iterator(_current - n));}

		//Subtraction operator - Returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to.
		reverse_iterator operator-(difference_type n) const{
			return reverse_iterator(_current + n);}

		//Increment iterator position - Advances the reverse_iterator by one position.
		reverse_iterator& operator++() {
			_current--;
			return (*this); }
		
		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			_current--;
			return tmp;}

		//Decrease iterator position - Decreases the reverse_iterator by one position.
		reverse_iterator& operator--() {
			_current++;
			return (*this); }

		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			_current++;
			return tmp;}

		//Advance iterator - Advances the reverse_iterator by n element positions.
		reverse_iterator& operator+=(difference_type n) {
			_current -= n;
			return (*this);}

		//Retrocede iterator - Descreases the reverse_iterator by n element positions.
		reverse_iterator& operator-=(difference_type n) {
			_current += n;
			return (*this);}

		//Dereference iterator - Returns a pointer to the element pointed to by the iterator (in order to access one of its members).
		pointer operator->() const { 
			return (&(operator*())); }

		//Dereference iterator with offset - Accesses the element located n positions away from the element currently pointed to by the iterator.
		reference operator[](difference_type n) const {
			return (_current[-n]);}

		
		private:
			Iterator _current;
	};

			/***************************Relational Operators**************************/
			//Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	template<class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return(lhs.base() != rhs.base()) ; }
	
	template<class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template<class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template<class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return(lhs.base() >= rhs.base()); }
	
	template<class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }

}
#endif