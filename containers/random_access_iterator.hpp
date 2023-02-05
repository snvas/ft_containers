/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:14:03 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/05 14:56:13 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

namespace ft{
	template<typename T>
	/*Random-access iterators are iterators that can be used to access elements at an arbitrary offset position 
	relative to the element they point to, offering the same functionality as pointers. 
	Random-access iterators are the most complete iterators in terms of functionality. 
	All pointer types are also valid random-access iterators.
	https://cplusplus.com/reference/iterator/*/
	class random_access_iterator{
		public:
		/*************************** Member types *****************************/
			typedef std::random_access_iterator_tag iterator_category;
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
	private:
			pointer _current;
	public:
			/***************************Constructors*****************************/
		//default constructor
		random_access_iterator(void) : _current(NULL){}; 
		
		random_access_iterator(pointer const src) : _current(src) {}; 
		
		//constructor with iterator
		random_access_iterator(random_access_iterator const &src){
			*this = src;
		}
		
		//destructor
		~random_access_iterator(void){}
		
		//operator =
		random_access_iterator &operator=(random_access_iterator const &rhs) {
			if (this != &rhs)
				_current = rhs._current;
			return (*this);}
		
		// equality operator
		bool operator==(random_access_iterator const &rhs) const {
			return (_current == rhs._current);
		}

		//inequality operator
		bool operator!=(random_access_iterator const &rhs) const {
			return (_current != rhs._current);
		}
			/***************************Operator Overloading**************************/
		//dereference
		reference operator*() const {
			return (*_current);}
		
		pointer operator->() const {
			return(_current);}
	
		// offset dereference operator
		reference operator[](const difference_type n) const {
			return (_current[n]);}
		
		// Increment and decrement operators
		random_access_iterator& operator++() {
			this->_current++;
			return (*this);}
		
		random_access_iterator operator++(int) {
			//return(random_access_iterator(_current++));
			random_access_iterator tmp(*this);
			this->_current++;
			return tmp;
			}

		random_access_iterator& operator--() {
			this->_current--;
			return (*this);}
		
		random_access_iterator operator--(int) {
			//return (random_access_iterator(_current--));
			random_access_iterator tmp(*this);
			this->_current--;
			return tmp;
			}
		
		// arithmetic operations (a + b / a - b)
		random_access_iterator operator+(difference_type n) const{
				return (random_access_iterator(this->_current + n));}
		
		random_access_iterator operator-(difference_type n) const{
			return (random_access_iterator(this->_current - n));}

		//relational operator
		bool operator<(const random_access_iterator &rhs) const {
			return (this->_current < rhs._current);
		}

		bool operator>(const random_access_iterator &rhs) const {
			return (this->_current > rhs._current);
		}

		bool operator<=(const random_access_iterator &rhs) const {
			return (this->_current <= rhs._current);
		}

		bool operator>=(const random_access_iterator &rhs) const {
			return (this->_current >= rhs._current);
		}
		// compound assignment operations (a += b / a -= b)
		random_access_iterator& operator+=(difference_type n) {
			this->_current += n;
			return (*this);}

		random_access_iterator& operator-=(difference_type n) {
			this->_current -= n;
			return (*this);}
	
		pointer base() const{
			return (this->_current);
		}
	};
	/*-----[ Non Member Functions - Random Access Iterator ]-----*/
	template<class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator-(
			const random_access_iterator<Iterator>& lhs, 
			const random_access_iterator<Iterator>& rhs) {
				return (lhs.base() - rhs.base()); }

	template<class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator+(
			typename random_access_iterator<Iterator>::difference_type n, 
			const random_access_iterator<Iterator> &it) {
			return (random_access_iterator<Iterator>(it.base() + n)); }
			
			/***************************Relational Operators**************************/
	//	Comparison operators
	template<class Iterator>
	bool operator==(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class Iterator>
	bool operator!=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() != rhs.base()); }
	
	template<class Iterator>
	bool operator<(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template<class Iterator>
	bool operator>(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template<class Iterator>
	bool operator<=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() <= rhs.base()); }
	
	template<class Iterator>
	bool operator>=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
	{ return (lhs.base() >= rhs.base()); }
	
}

#endif