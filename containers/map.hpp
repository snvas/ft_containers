/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:14:21 by snovaes           #+#    #+#             */
/*   Updated: 2023/02/12 20:31:50 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../rbtree/Rbtree.hpp"
#include "algorithm.hpp"
#include "pair.hpp"
#include "rb_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <cstddef>

namespace ft
{
/*
/   * ------------------------------------------------------------- *
	* ------------------------- FT::MAP --------------------------- *
	*
	* - Coplien form:           
	* (constructor):	Construct map
	* (destructor):		Map destructor
	* operator=:		Assign map
	*
	* - Iterators:
	* begin:			Return iterator to beginning
	* end:				Return iterator to end
	* rbegin:			Return reverse iterator to reverse beginning
	* rend:				Return reverse iterator to reverse end
	*
	* - Capacity:
	* empty:			Test whether container is empty
	* size:				Return container size
	* max_size:			Return maximum size
	*
	* - Element access:
	* operator[]:		Access element
	*
	* - Modifiers:
	* insert:			Insert elements
	* erase:			Erase elements
	* swap:				Swap content
	* clear:			Clear content
	*
	* - Observers:
	* key_comp:			Return key comparison object
	* value_comp:		Return value comparison object
	*
	* - Operations:
	* find:				Get iterator to element
	* count:			Count elements with a specific key
	* lower_bound:		Return iterator to lower bound
	* upper_bound:		Return iterator to upper bound
	* equal_range		Get range of equal elements
	* ------------------------------------------------------------- *
	* Maps are associative containers that store elements formed by a combination
	* of a key value and a mapped value, following a specific order.
    */

   /**
	* @param key Type of keys mapped to elements.
	* @param Val Type of elements mapped to keys.
	* @param Compare Comparison object used to sort the binary tree.
	* @param Alloc Object used to manahe the storage
   */
	template <class Key, class Val, class Compare = std::less<Key>,
		  class Alloc = std::allocator<ft::pair<const Key, Val> > >
	class map
	{
		public:
		/***************************Member Types*****************************/
		typedef Key key_type; //The first template parameter (Key)
		typedef Val mapped_type; //The second template parameter (Val)
		typedef ft::pair<const Key, Val> value_type; //pair<const key_type,mapped_type>
		typedef Compare key_compare; //The third template parameter (Compare) - defaults to: less<key_type>
		typedef Alloc allocator_type; //The fourth template parameter (Alloc)
		/**
		 * Comparison object using map´s key_compare
		 * Return value comparison object - Returns a comparison object that can be used to compare 
		 * two elements to get whether the key of the first one goes before the second.
		 * @return value_comp method
		*/
		class value_compare
		{
			friend class map<Key, Val, Compare>;
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				bool operator()(const value_type &x, const value_type &y) const {
					return comp(x.first, y.first);
				}
		};
		typedef ft::rb_iterator<value_type>								iterator;
		typedef ft::rb_iterator<value_type>								const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef ptrdiff_t												difference_type;
		typedef size_t													size_type;
		
		typedef ft::Node<value_type>									node_type;
			private:
		typedef typename Alloc::template rebind<node_type>::other		node_allocator_type;
		/*Binds the allocator object to a different value type. The rebind class has a 
		single typedef, other, which is an instance of allocator*/

		public:
		typedef ft::Rbtree<value_type, value_compare, allocator_type, node_allocator_type>	tree_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
			private:
		key_compare			_comp;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;
		size_type			_size;
		tree_type			_tree; // red-black tree representing map
		
		public:
		/**
		 * Default constructor
		 * Constructs an empty container, with no elements.
		 * creates a map with a size of 0.
		 * @param comp The template param used for sorting the map.
		 * @param alloc The template param used for the allocation.
		*/
		explicit map(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _node_alloc(node_allocator_type()),
			_size(0), _tree(value_compare(_comp), _alloc, _node_alloc) {}

		/**
		 * range constructor - Constructs a container with as many elements as the range [first,last), 
		 * with each element constructed from its corresponding element in that range.
		 * @param first	An iterator representing first element in range
		 * @param last	An iterator representing end of the range (will be excluded and not copied).
		 * @param comp The template param used for sorting the map.
		 * @param alloc The template param used for the allocation.
		*/
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _node_alloc(node_allocator_type()),
			_size(0), _tree(value_compare(_comp), _alloc, _node_alloc)
		{
			insert(first, last);
		}

		/**
		 * copy constructor - Constructs a container with a copy of each of the elements in x.
		 * @param x The map that will be copied.
		*/
		map(const map &x)
			: _comp(x._comp), _alloc(x._alloc), _node_alloc(x._node_alloc),
			_size(x._size), _tree(x._tree) {}

		/**
		 * Map destructor - Destroys the container object.
		*/
		~map(void) {}
		
		/*************************** Iterators *****************************/
		/**
		 * Return iterator to beginning
		 * @return an iterator referring to the first node of the map(minValueNode value).
		*/
		iterator begin(){
			iterator it(this->_tree.minValueNode(this->_tree.get_root()));
			return (it);
		}

		/**
		 * Return const_iterator to beginning
		 * @return an const_iterator pointing to the first node of the map(minValueNode value).
		*/
		const_iterator begin() const{
			const_iterator it(this->_tree.minValueNode(this->_tree.get_root()));
			return (it);
		}
	
		/**
		 * Returns an iterator referring to the past-the-end element in the map container.
		 * @return An iterator pointing after the last map's element, on a dummy node. 
		 * Access this iterator will result in undefined behavior.
		*/
		iterator end(){
			node_type *node = this->_tree.maxValueNode(this->_tree.get_root());
			if (!node){
				return (NULL);
			}
			return iterator(node->right);;
		}

		/**
		 * Returns an const_iterator referring to the past-the-end element in the map container.
		 * @return An const_iterator pointing after the last map's element, on a dummy node. 
		 * Access this iterator will result in undefined behavior.
		*/
		const_iterator end() const{
			node_type *node = this->_tree.maxValueNode(this->_tree.get_root());
			if (!node){
				return (NULL);
			}
			return const_iterator(node->right);;
		}

		/**
		 * Return reverse iterator to reverse beginning
		 * @return reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		*/
		reverse_iterator rbegin(){
			iterator it = this->end();
			it--;
			return (reverse_iterator(it));
		}
		
		/**
		 * Return const_reverse iterator to reverse beginning
		 * @return a const_reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		*/
		const_reverse_iterator rbegin() const{
			const_iterator it = this->end();
			it--;
			return (const_reverse_iterator(it));
		}
		
		/**
		 * Return reverse iterator to reverse end
		 * @return  A reverse_iterator pointing before the first map's element, on a dummy node.
		 * Access this iterator will result in undefined behavior.
		 * 
		*/
		reverse_iterator rend(){
			iterator it = this->begin();
			it--;
			return (reverse_iterator(it));
		}

		/**
		 * Return a const_reverse iterator to reverse end
		 * @return  A const_reverse_iterator pointing before the first map's element, on a dummy node.
		 * Access this iterator will result in undefined behavior.
		 * 
		*/
		const_reverse_iterator rend() const{
			const_iterator it = this->begin();
			it--;
			return (const_reverse_iterator(it));
		}
		
		/*************************** Capacity *****************************/
		/**
		 * Test whether container is empty - 
		 * @return True if the map' size is equal to 0.
		 * whether the map container is empty (i.e. whether its size is 0).
		*/
		bool empty() const{
			if (this->_size == 0)
				return (true);
			return (false);
		}

		/**
		 * Return container size 
		 * @return The size of the map
		*/
		size_type size() const{
			return (this->_size);
		}

		/**
		 * Return container size 
		 * @return The max possible size to be allocated.
		*/
		size_type max_size() const{
			return (this->_node_alloc.max_size());
		}
		
		/*************************** Element access *****************************/
		/**
		 * Searches for a specific key in the tree, and if this one isn't existing,
		 * creating it. Then returning a reference on it that allows modification.
		 * Notice that this always increases the container size by one, even if no 
		 * mapped value is assigned to the element (the element is constructed 
		 * using its default constructor)
		 * @param k
		 * @return A reference to the key's mapped value in the tree (already existing, or newly created.
		*/
		mapped_type &operator[](const key_type &k){
			node_type *node =
				this->_tree.lookup_value(ft::make_pair(k, mapped_type()));
			if (!node)
			{
				node = this->_tree.insert_value(
					ft::make_pair(k, mapped_type()));
				this->_size += 1;
			}
			return (node->data->second);
		}
		
		/**
		 * @return a reference to the mapped value of the element identified with key k.
		 * If k does not match the key of any element in the container, 
		 * the function throws an out_of_range exception.
		 */
		mapped_type &at(const key_type &k){
			node_type *node = this->_tree.lookup_value(ft::make_pair(k, mapped_type()));
			if (!node)
			{
				throw(std::out_of_range("map::at"));
			}
			return (node->data->second);
		}

		const mapped_type &at(const key_type &k) const{
			node_type *node =
				this->_tree.lookup_value(ft::make_pair(k, mapped_type()));
			if (!node)
			{
				throw(std::out_of_range("map::at"));
			}
			return (node->data->second);
		}
		
		/*************************** Modifiers *****************************/
		/**
		 * Insert element - single element
		 * Extends the container by inserting new elements, effectively 
		 * increasing the container size by the number of elements inserted.
		 * Because element keys in a map are unique, the insertion operation 
		 * checks whether each inserted element has a key equivalent to the 
		 * one of an element already in the container, and if so, the element 
		 * is not inserted, returning an iterator to this existing element 
		 * (if the function returns a value).
		 */
		ft::pair<iterator, bool> insert(const value_type &val){
			// Searches in the tree if val´s key is already present and returns
			// an interator to the key inside the tree if it´s the case
			node_type *look = this->_tree.lookup_value(val);
			if (look)
				return (ft::make_pair(iterator(look), false));
			node_type *node = this->_tree.insert_value(val);
			// Inserts the pair in the tree and returns an interator to its position
			this->_size += 1;
			return (ft::make_pair(iterator(node), true));
		}

		/** Insert one element if the key didn´t already exist in map, starting from
		 * a certain position in the tree in order to optimize the insert process.
		 * Increases the size by one if the element was inserted.
		 * @param position	Hint for the position where the element can be inserted.
		 * 					The function optimizes its insertion time if position points to 
		 * 					the element that will precede the inserted element.
		 * @param val		The pair<key, mapped value> to insert.
		 * @return			an iterator pointing to either the newly inserted element 
		 * 					or to the element that already had an equivalent key in the map
		*/
		iterator insert(iterator position, const value_type &val){
			node_type *node_pos = position.get_node_pointer();
			node_type *look = this->_tree.lookup_value(node_pos, val);
			if (look)
				return (iterator(look));
			node_type *node = this->_tree.insert_value(node_pos, val);
			this->_size += 1;
			return (iterator(node));
		}

		/**
		 * Inserts all elements between first and last (if they're not already existing), 
		 * and increases the map' size.
		 *
		 * @param first An iterator pointing to the range's beginning (will be include).
		 * @param last An iterator pointing to the range's end (will not be include).
		 */
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last){
			InputIterator it;
			it = first;
			while (it != last)
			{
				this->insert(*it);
				it++;
			}
		}

		/**
		 * Removes from the map container either a single element 
		 * or a range of elements ([first,last)).
		 * This effectively reduces the container size by the number 
		 * of elements removed, which are destroyed.
		 * @param position Iterator pointing to a single element to be removed from the map.
		*/
		void erase(iterator position){
			value_type value = *position;
			if (this->_tree.delete_value(value))
				this->_size -= 1;
		}

		/** 
		 *  Removes from the map one element that matches a specific key. This reduces the size 
		 * of the container by the number of elements removed (which can be only one).
		 * @param k The key to find in the map and remove it
		 * @return 1 if the key is found and removed, 0 if not
		*/
		size_type erase(const key_type &k){
			if (this->_tree.delete_value(ft::make_pair(k, mapped_type())))
			{
				this->_size -= 1;
				return (1);
			}
			return (0);
		}

		/**
		 * Iterators specifying a range within the map container to be removed: [first,last). i.e., the range 
		 * Removes from the map a range of elements. Size is decreased by the number of 
		 * elements removed.
		 * @param first	An iterator pointing to the range's beginning (will be included).
		 * @param last 	An iterator pointing to the range's end (will not be included).
		 */
		void erase(iterator first, iterator last){
			iterator it;
			while (first != last){
				it = first;
				++first;
				this->erase(it->first);
			}
		}

		/**
		 * Swap content
		 * Exchanges the content of the container by the content of x, 
		 * which is another map of the same type. Sizes may differ.
		 * 
		 * @param x The map to be swapped.
		*/
		void swap(map &x){
			std::swap(this->_comp, x._comp);
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_size, x._size);
			this->_tree.swap(x._tree);
		}

		/**
		 * Clear content
		 * Removes all elements from the map container (which are destroyed),
		 * leaving the container with a size of 0.
		*/
		void clear(){
			this->_tree.clear();
			this->_size = 0;
		}
		
		/*************************** Modifiers *****************************/
		/**
		 * @return a copy of the comparison object used by the container to compare keys.
		*/
		key_compare key_comp() const{
			return this->_comp;
		}

		/**
		 * @return a comparison object that can be used to compare two elements to get 
		 * 			whether the key of the first one goes before the second. This object
		 * 			is using a copy od the map´s comparison object.
		*/
		value_compare value_comp() const{
			return value_compare(this->_comp);
		}
		
		/*************************** Operations *****************************/
		/**
		 * Searches the container for an element with a key equivalent to k
		 * @param k The key to search in the container.
		 * @return An iterator to the element matching the key if it exists, 
		 * 			otherwise it returns an iterator to end
		*/
		iterator find(const key_type &k){
			node_type *node =
				this->_tree.lookup_value(ft::make_pair(k, mapped_type()));
			if (!node)
				return (this->end());
			return (iterator(node));
		}
		/**
		 * Searches the container for an element with a key equivalent to k
		 * @param k The key to search in the container.
		 * @return An const_iterator to the element matching the key if it exists, 
		 * 			otherwise it returns an iterator to end
		*/
		const_iterator find(const key_type &k) const{
			node_type *node =
				this->_tree.lookup_value(ft::make_pair(k, mapped_type()));
			if (!node)
				return (this->end());
			return (const_iterator(node));
		}

		/**
		 * Searches the container for elements with a key 
		 * equivalent to k and returns the number of matches.
		 * @param k The key to count the number of occurrences.
		 * @return The number of matches. Since keys can´t be 
		 * 		twice time in mao, this is either 0 or 1.
		*/
		size_type count(const key_type &k) const{
			const_iterator it = find(k);
			if (it != end()){
				return (1);
			}
			return (0);
		}

		/**
		 * Searches for the element whose key is not considered to go before k.
		 *
		 * @param k	The key to search for.
		 * @return	An iterator to the the first element in the container whose key 
		 * is not considered to go before k, or map::end if all keys are 
		 * considered to go before k.
		*/
		iterator lower_bound(const key_type &k){
			node_type *node =  this->_tree.lower_bound(_tree.get_root(), ft::make_pair(k, mapped_type()));
			if (!node)
				return (this->end());
			return (iterator(node));
		}

		/**
		 * Searches for the element whose key is not considered to go before k.
		 *
		 * @param k	The key to search for.
		 * @return	An const_iterator to the the first element in the container whose key 
		 * is not considered to go before k, or map::end if all keys are 
		 * considered to go before k.
		*/
		const_iterator lower_bound(const key_type &k) const{
			node_type *node =  this->_tree.lower_bound(_tree.get_root(), ft::make_pair(k, mapped_type()));
			if (!node)
				return (this->end());
			return (const_iterator(node));
		}

		/**
		* Searches for the element whose key is considered to go after k.
		*
		* @param k	The key to search for.
		* @return	An iterator to the the first element in the container whose key 
		*			is considered to go after k, or map::end if no keys are 
		*			considered to go after k.
		*/
		iterator upper_bound(const key_type &k){
			node_type *node =  this->_tree.upper_bound(_tree.get_root(), ft::make_pair(k, mapped_type()));
			if (!node)
				return (this->end());
			return (iterator(node));
		}
		
		/**
		* Searches for the element whose key is considered to go after k.
		*
		* @param k	The key to search for.
		* @return	An const_iterator to the the first element in the container whose key 
		*			is considered to go after k, or map::end if no keys are 
		*			considered to go after k.
		*/
		const_iterator upper_bound(const key_type &k) const{
			node_type *node =  this->_tree.upper_bound(_tree.get_root(), ft::make_pair(k, mapped_type()));
			if (!node)
				return (this->end());
			return (const_iterator(node));
		}

		/**
		 * Get range of equal elements
		 * Returns the bounds of a range that includes all the elements in the container 
		 * which have a specific key. Because the elements in a map container have unique keys, 
		 * the range returned will contain a single element at most.
		 *
		 * @param k	The key to search in the tree.
		 * @return		The function returns a pair of iterators, whose member pair::first is the 
		 *				lower bound of the range (the same as lower_bound), and pair::second is the 
		*				upper bound (the same as upper_bound).
		*/
		pair<iterator, iterator> equal_range(const key_type &k){
			iterator lowerBound = lower_bound(k);
			iterator upperBound = upper_bound(k);
			return (ft::make_pair(lowerBound, upperBound));
		}
		
		/**
		 * Get range of equal elements
		 * Returns the bounds of a range that includes all the elements in the container 
		 * which have a specific key. Because the elements in a map container have unique keys, 
		 * the range returned will contain a single element at most.
		 *
		 * @param k	The key to search in the tree.
		 * @return		The function returns a pair of const_iterators, whose member pair::first is the 
		 *				lower bound of the range (the same as lower_bound), and pair::second is the 
		*				upper bound (the same as upper_bound).
		*/
		pair<const_iterator, const_iterator> equal_range(const key_type &k) const{
			const_iterator lowerBound = lower_bound(k);
			const_iterator upperBound = upper_bound(k);
			return (ft::make_pair(lowerBound, upperBound));
		}
		
		/**
		 * Get allocator
		 * @return a copy of the allocator object associated with the map.
		*/
		allocator_type get_allocator(void) const{
			return (this->_alloc);
		}

		/// @brief print tree to test
		void print_tree(){
			this->_tree.printBT();
		}
	};

	/**
	 * Implementation of the equality operator (==) for a custom ft::map class in C++. 
	 * The function takes two ft::map objects as input, lhs and rhs.
	 * The function first checks if the sizes of lhs and rhs are equal. 
	 * If they are not equal, it returns false immediately. 
	 * If the sizes are equal, it then checks if both lhs and rhs are empty, and if so, 
	 * it returns true because two empty maps are equal.
	 * Otherwise, it returns the result of calling the ft::equal function, 
	 * passing lhs.begin() and lhs.end() as the first two arguments, and rhs.begin() as the third argument.
	 * The ft::equal function is likely a custom implementation of the std::equal algorithm, 
	 * and it checks if the elements of two ranges are equal. 
	 * In this case, the ranges being compared are the elements of the two maps. 
	 * If the elements are equal, ft::equal returns true and the operator== function returns true. 
	 * If the elements are not equal, ft::equal returns false and the operator== function returns false.
	*/
	template <class Key, class Val, class Compare, class Alloc>
	bool operator==(const ft::map<Key, Val, Compare, Alloc> &lhs,
			const ft::map<Key, Val, Compare, Alloc> &rhs){
		if (lhs.size() != rhs.size())
			return (false);
		if (lhs.empty() && rhs.empty())
			return (true);
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	/**
	 * Templated operator overload for the "not equals to" operator != for a map called ft::map. 
	 * The function takes two ft::map objects lhs and rhs as input.
	 * The function first checks if the size of lhs is not equal to the size of rhs. 
	 * If they are not equal, then it returns false. If both maps are empty, then it returns true.
	 * Otherwise, it uses the ft::equal function to compare the elements of lhs and rhs. 
	 * If all elements are equal, then it returns false, otherwise it returns true.
	*/
	template <class Key, class Val, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, Val, Compare, Alloc> &lhs,
			const ft::map<Key, Val, Compare, Alloc> &rhs){
		return (!(lhs == rhs));
	}

	/**
	 * an overloaded operator "<" for the "ft::map" class template. 
	 * It compares two maps, lhs and rhs, and returns true if lhs is strictly less than rhs. 
	 * This means that all elements of lhs are present in rhs and rhs has at least one element that is not present in lhs. 
	 * The comparison is done lexicographically, which means it compares the first elements of both maps, 
	 * and if they are equal, it moves on to the next elements, and so on. 
	 * If any pair of elements is not equal, the comparison stops and the result is based on the comparison of the current elements. 
	 * The operator returns false if rhs is empty or if the two maps have the same elements.
	*/
	template <class Key, class Val, class Compare, class Alloc>
	bool operator<(const ft::map<Key, Val, Compare, Alloc> &lhs,
			const ft::map<Key, Val, Compare, Alloc> &rhs){
		if (rhs.empty())
			return (false);
		if (lhs.empty())
			return (true);
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
							rhs.end()));
	}

	/**
	 * template for the operator <= (less than or equal to) for a custom class ft::map 
	 * with template parameters Key, Val, Compare, and Alloc. 
	 * The ft::map class is a type of data structure that stores key-value pairs in a sorted manner, 
	 * where the sorting order is determined by the comparison function Compare. 
	 * The template parameters Key and Val represent the types of the keys and values stored in the map, 
	 * respectively, while the Alloc parameter specifies the type of the memory allocator used by the map.
	 * The operator <= compares two ft::map objects lhs and rhs and returns true if lhs is less than or equal to rhs. 
	 * The comparison is done in a lexicographical manner, meaning that it compares the 
	 * elements of the two maps in sequence until either a pair of elements are not equal 
	 * or one of the maps has been completely iterated through. If lhs is less than rhs, 
	 * then !(rhs < lhs) returns false, so the operator returns true to indicate that lhs is less than or equal to rhs.
	*/
	template <class Key, class Val, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, Val, Compare, Alloc> &lhs,
			const ft::map<Key, Val, Compare, Alloc> &rhs){
		return (!(rhs < lhs));
	}

	/**
	 * template function definition for the operator "greater than" (">") for a map object 
	 * of the C++ Standard Library-like container class ft::map. 
	 * The function takes two ft::map objects, lhs and rhs, as input parameters, 
	 * both with the template arguments Key, Val, Compare, and Alloc, representing the 
	 * key type, value type, comparison object type, and memory allocation object type, respectively.
	 * The function returns a boolean value indicating whether lhs is greater than rhs. 
	 * The greater than comparison between two maps is established by checking if rhs is less than lhs, 
	 * which is calculated by the previously defined operator "<" for maps. If rhs is less than lhs, 
	 * then lhs is greater than rhs, and the function returns true. Otherwise, it returns false.
	*/
	template <class Key, class Val, class Compare, class Alloc>
	bool operator>(const ft::map<Key, Val, Compare, Alloc> &lhs,
			const ft::map<Key, Val, Compare, Alloc> &rhs){
		return (rhs < lhs);
	}
	
	/**
	 * This template defines the operator >= for objects of type ft::map<Key, Val, Compare, Alloc>. 
	 * The purpose of this operator is to compare two ft::map objects to determine 
	 * if the first object (lhs) is greater than or equal to the second object (rhs). 
	 * The operator returns the result of !(lhs < rhs), where < is the less than operator defined earlier. 
	 * In other words, if lhs is not less than rhs, then lhs >= rhs.
	*/
	template <class Key, class Val, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, Val, Compare, Alloc> &lhs,
			const ft::map<Key, Val, Compare, Alloc> &rhs){
		return (!(lhs < rhs));
	}
}

#endif