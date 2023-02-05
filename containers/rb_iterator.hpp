/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:13:53 by snovaes           #+#    #+#             */
/*   Updated: 2023/01/26 20:39:54 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_ITERATOR_HPP
#define RB_ITERATOR_HPP

#include "../rbtree/Rbtree.hpp"

namespace ft{
	template<class T>
	class rb_iterator{
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef rb_iterator<T> iterator;
			typedef T value_type;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef T& reference;
			typedef const T& const_reference;
			typedef ft::Node<T>* node_pointer;
			typedef ft::Node<T>& node_reference;
			typedef std::ptrdiff_t difference_type;

			typedef std::less<T> value_compare;
			typedef ft::Rbtree<T, value_compare> tree;

			rb_iterator() : _node_ptr(NULL){}

			rb_iterator(node_pointer src) : _node_ptr(src) {}

			rb_iterator(rb_iterator const &src){
				*this = src;
			}

			~rb_iterator(void){}

			rb_iterator &operator=(rb_iterator const &other){
				if (this != &other)
					this->_node_ptr = other._node_ptr;
				return (*this);
			}
			//equality/inequality operators
			bool operator==(rb_iterator const &other) const{
				return (this->_node_ptr == other._node_ptr);
			}
			bool operator!=(rb_iterator const &other) const{
				return (this->_node_ptr != other._node_ptr);
			}
			//dereference
			reference operator*() const{
				return (*this->_node_ptr->data);
			}

			pointer operator->() const{
				return (&(operator*()));
			}
			//increment and decrement
			rb_iterator &operator++(){
				this->_node_ptr = tree::successor(this->_node_ptr);
				return (*this);
			}
			rb_iterator &operator--(){
				this->_node_ptr = tree::predecessor(this->_node_ptr);
				return (*this);
			}
			rb_iterator operator++(int){
				iterator copy(*this); 
				this->_node_ptr = tree::successor(this->_node_ptr);
				return (copy);
			}
			rb_iterator operator--(int){
				iterator copy(*this); 
				this->_node_ptr = tree::predecessor(this->_node_ptr);
				return (copy);
			}
			node_pointer get_node_pointer(void){
				return (this->_node_ptr);
			}
	private:
		node_pointer _node_ptr;
	};
}
#endif