#ifndef SET_HPP
#define SET_HPP

#include "../rbtree/Rbtree.hpp"
#include "algorithm.hpp"
#include "rb_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "pair.hpp" 
#include "vector.hpp"

namespace ft
{
	/**
	 * Characteristics of set
	 * It orders the elemens that are added to it.
	 * A set contains only one copy of any element (key) added to it.
	*/
	template <typename Key, 
				typename Compare = std::less<Key>, //ordering in ascending order
				typename Allocator = std::allocator<Key> >
	class set 
	{
	public:
		/***************************Member Types*****************************/
		typedef Key key_type; //the first template parameter (Key)
		typedef Key value_type; 
		typedef Compare key_compare; // the second template parameter (Compare) -  default to: less<key_type>
		typedef Compare value_compare;
		typedef Allocator allocator_type; // the third template parameter (Allocator)
		typedef typename Allocator::size_type size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename allocator_type::pointer 		pointer;
		typedef typename allocator_type::const_pointer 	const_pointer;
		typedef ft::rb_iterator<value_type>								iterator;
		typedef ft::rb_iterator<value_type>								const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		typedef ft::Node<value_type>					node_type;
		typedef node_type*								node_pointer;
		private:
			typedef typename Allocator::template rebind<node_type>::other		node_allocator_type;
		public:
		typedef ft::Rbtree<value_type, value_compare, allocator_type, node_allocator_type>	tree_type;

	protected:
		tree_type 							_tree;
		size_type 							_size;
		key_compare							_comp;

	public:	
		/**
		 * Construct set
		 * Constructs a set container object, initializing its contents depending on the constructor version used:
		 * (1) empty container constructor (default constructor)
		 * Constructs an empty container, with no elements.
		 * @param comp Binary predicate that, taking two values of the same type of those contained in the set, 
		 * returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise.
		 * @param alloc Allocator object. The container keeps and uses an internal copy of this allocator.
		 *
		*/
		explicit set(const Compare &comp = key_compare(), 
				const Allocator& alloc = Allocator()) : _tree(comp, alloc), _size(0) {}
		
		/**
		 * range constructor - Constructs a container with as many elements as the range [first,last),
		 * with each element constructed from its corresponding element in that range.
		 * @param first	An iterator representing first element in range
		 * @param last	An iterator representing end of the range (will be excluded and not copied).
		 * @param comp The template param used for sorting the set.
		 * @param alloc The template param used for the allocation.
		*/
		template<class U>
		set(U first, U last, 
			const Compare& comp = Compare(), 
			const Allocator& alloc = Allocator()) : _tree(comp, alloc), _size(0){
				while (first != last){
					insert(*first);
					++first;
				}
			}

		/**
		 * copy constructor - Constructs a container with a copy of each of the elements in other.
		 * @param other The set that will be copied.
		*/
		set(const set& other) : _tree(other._tree), _size(other._size) {}

		/**
		 * Set destructor - destroy the contained object.
		*/
		~set(void){
			clear();
		 }

		/**
		 * Operator=
		 * Copy container content 
		 * Assigns new contents to the container, replacing its current content.
		 * Copies all the elements from x into the container, changing its size accordingly.
		 * @param x A set object of the same type (i.e., with the same template parameters, T, Compare and Alloc).
		 */
		set& operator=(const set& x){
			if (this != &x){
				_tree = x._tree;
				_size = x._size;
			}
			return (*this);
		}

		/**
		 * Returns a copy of the allocator object associated with the set.
		 * @return The allocator. Member type allocator_type is the type of the allocator 
		 * used by the container, defined in set as an alias of its third template parameter (Alloc).
		*/
		allocator_type get_allocator() const{
			return (_tree.get_allocator());
		}

		/*************************** Iterators *****************************/
		/**
	 	* Return iterator to beginning
	 	* @return an iterator referring to the first node of the set(minValueNode value).
		*/
		iterator begin(){
			iterator it(this->_tree.minValueNode(this->_tree.get_root()));
			return (it);
		}

		/**
		 * Return const_iterator to beginning
	 	* @return an const_iterator pointing to the first node of the set(minValueNode value).
		*/
		const_iterator begin() const{
			const_iterator it(this->_tree.minValueNode(this->_tree.get_root()));
			return (it);
		}

		/**
		 * Returns an iterator referring to the past-the-end element in the set container.
		 * @return An iterator pointing after the last set's element, on a dummy node. 
		 * Access this iterator will result in undefined behavior.
		*/
		iterator end(){
			node_type *node = this->_tree.maxValueNode(this->_tree.get_root());
			if (node)
			{
				iterator it(node->right);
				return (it);
			}
			return (NULL);
		}
		
		/**
	 	* Returns an const_iterator referring to the past-the-end element in the set container.
		 * @return An const_iterator pointing after the last set's element, on a dummy node. 
		 * Access this iterator will result in undefined behavior.
		*/
		const_iterator end() const{
			node_type *node = this->_tree.maxValueNode(this->_tree.get_root());
			if (node){
				const_iterator it(node->right);
				return (it);
			}
			return (NULL);
		}

		/**
		 * Return reverse iterator to reverse beginning
		 * @return reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		*/
		reverse_iterator rbegin(){
				return (reverse_iterator(--this->end()));
		}
	
		/**
		 * Return const_reverse iterator to reverse beginning
		 * @return a const_reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		*/
		const_reverse_iterator rbegin() const{
			return (const_reverse_iterator(--this->end()));
		}
	
		/**
		 * Return reverse iterator to reverse end
		 * @return  A reverse_iterator pointing before the first map's element, on a dummy node.
		 * Access this iterator will result in undefined behavior.
		 * 
		*/
		reverse_iterator rend(){
			return (reverse_iterator(--this->begin()));
		}

		/**
		 * Return a const_reverse iterator to reverse end
	 	* @return  A const_reverse_iterator pointing before the first map's element, on a dummy node.
	 	* Access this iterator will result in undefined behavior.
	 	* 
		*/
		const_reverse_iterator rend() const{
			return (const_reverse_iterator(--this->begin()));
		}

		/**
		 * Clear content
		 * Removes all elements from the set container (which are destroyed),
		 * leaving the container with a size of 0.
		*/
		void clear(void){
			_tree.clear();
			this->_size = 0;
		}

		/**
		 * Test whether container is empty - 
		 * @return True if the set' size is equal to 0.
		 * whether the set container is empty (i.e. whether its size is 0).
		*/
		bool empty(void) const {
			if (this->_size == 0)
				return (true);
			return (false);
		}

		/**
		 * Return container size 
		 * @return The size of the set
		*/
		size_type size(void) const{
			return (_size);
		}

		/**
		 * Return container size 
		 * @return The max possible size to be allocated.
		*/
		size_type max_size(void) const{
			return (_tree.get_allocator().max_size());
		}

		/** Single element
		 * Extends the container by inserting new elements, effectively increasing 
		 * the container size by the number of elements inserted.
		 * Because elements in a set are unique, the insertion operation checks whether 
		 * each inserted element is equivalent to an element already in the container, 
		 * and if so, the element is not inserted, returning an iterator to this existing element
		 * set containers keep all their elements sorted following the criterion specified by its 
		 * comparison object. The elements are always inserted in its respective position following this ordering.
		 * @param val Value to be copied (or moved) to the inserted elements. Member type value_type is the type 
		 * of the elements in the container, defined in set as an alias of its first template parameter (T).
		 * 
		*/
		ft::pair<iterator,bool> insert(const value_type &val){
			iterator it = this->find(val);
			if (it != end())
				return ft::make_pair(it, false);
			it = iterator(_tree.insert_value(val));
			_size++;

			return ft::make_pair(it, true);
		}

		/** 
		 * Insert with hint
		 * @param position Hint for the position where the element can be inserted.
		*/
		iterator insert(iterator position, const value_type& val){
			node_type *node_pos = position.get_node_pointer();
			node_type *look = this->_tree.lookup_value(node_pos, val);
			if (look)
				return (iterator(look));
			node_type *node = this->_tree.insert_value(node_pos, val);
			this->_size += 1;
			return (iterator(node));
		}

		/**
		 * Insert range
		 * @param first, last Iterators specifying a range of elements. Copies of the elements 
		 * in the range [first,last) are inserted in the container. Notice that the range includes 
		 * all the elements between first and last, including the element pointed by first but not the one pointed by last.
		 * The function template argument InputIterator shall be an input iterator type that points 
		 * to elements of a type from which value_type objects can be constructed.
		*/
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last, 
			typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0){
			while (first != last)
				insert(*first++);
		}

		/**
		 * Get range of equal elements
		 * @returns the bounds of a range that includes all the elements in the container that are equivalent to val.
		 * Because all elements in a set container are unique, the range returned will contain a single element at most.
		*/
		ft::pair<iterator, iterator> equal_range(const value_type &val) const{
			return (ft::make_pair(iterator(lower_bound(val)), iterator(upper_bound(val))));
		}

		/**
		 * Return iterator to lower bound
		 * @param val Value to compare. Member type value_type is the type of the elements in the container, 
		 * 				defined in set as an alias of its first template parameter (T).
		 * @returns An iterator to the the first element in the container which is not 
		 * considered to go before val, or set::end if all elements are considered to go before val.
		*/
		iterator lower_bound(const value_type& val) const{
			node_type *node =  this->_tree.lower_bound(_tree.get_root(), val);
			if (!node)
				return (this->end());
			return (iterator(node));
		}

		/**
		 * Return iterator to upper bound
		 * @param val Value to compare.
		 * @returns An iterator to the the first element in the container which is 
		 * considered to go after val, or set::end if no elements are considered to go after val.
		*/
		iterator upper_bound(const value_type& val) const{
			node_type *node =  this->_tree.upper_bound(_tree.get_root(), val);
			if (!node)
				return (this->end());
			return (iterator(node));
		}

		/**
		 * Get iterator to element
		 * Searches the container for an element equivalent to val and returns an iterator 
		 * to it if found, otherwise it returns an iterator to set::end.
		 * @param val Value to be searched for.
		 * @return An iterator to the element, if val is found, or set::end otherwise.
		*/
		iterator find(const value_type& val) const{
			node_type *n;
			n = _tree.lookup_value(val);
			if (!n)
				return (end());
			return iterator(n);
		}

		/**
		 * Erase elements
		 * Removes from the set container either a single element or a range of elements ([first,last)).
		 * @param position Iterator pointing to a single element to be removed from the set.
		*/
		void erase(iterator position){
			_tree.delete_node(position.get_node_pointer());
			_size--;
		}
		
		/**
		 * Erase val
		 * @param val the value to erase
		*/
		size_type erase(const value_type& val){
			if (this->_tree.delete_value(val)){
				this->_size -= 1;
				return (1);
			}
			return (0);
		}
		
		/**
		 * Erase with iterators
		 * @param first, last Iterators specifying a range within the set container to be removed: [first,last). 
		 * i.e., the range includes all the elements between first and last, including the element pointed by 
		 * first but not the one pointed by last.
		*/
		void erase(iterator first, iterator last){
			iterator it;
			while (first != last){
				it = first;
				++first;
				_tree.delete_node(it.get_node_pointer());
			}
		}

		/**
		 * Count elements with a specific value
		 * Searches the container for elements equivalent to val and returns the number of matches.
		 * Because all elements in a set container are unique, the function can only 
		 * return 1 (if the element is found) or zero
		 * @param val Value to search for
		 * @return if the container contains an element equivalent to val, or zero otherwise.
		 * 
		*/
		size_type count(const value_type& val) const{
			size_type size = 0;
			for (const_iterator it = begin(); it != end(); it++)
				if (*it == val)
					size++;
			return size;
		}

		/**
		 * Swap content
		 * Exchanges the content of the container by the content of x, 
		 * which is another set of the same type. Sizes may differ.
		 * After the call to this member function, the elements in this container are those which 
		 * were in x before the call, and the elements of x are those which were in this. All iterators, 
		 * references and pointers remain valid for the swapped objects.
		 * @param x Another set container of the same type as this 
		 * (i.e., with the same template parameters, T, Compare and Alloc) 
		 * whose content is swapped with that of this container.
		*/
		void swap(set& x){
			set temp = *this;
			*this = x;
			x = temp;
		}

		/**
		 * Return comparison object
		 * Returns a copy of the comparison object used by the container.
		 * @return The comparison object. Member type key_compare is the type of the comparison 
		 * object associated to the container, defined in set as an alias of its second template parameter (Compare).
		*/
		key_compare key_comp(void) const{
			return Compare();
		}

		/**
		 * Return comparison object
		 * Returns a copy of the comparison object used by the container.
		 * @return The comparison object. Member type value_compare is the type of the comparison 
		 * object associated to the container, defined in set as an alias of its second template parameter (Compare).
		*/
		value_compare value_comp(void) const{
			return (value_compare(key_comp()));
		}
	};
		template <typename Key, typename Compare, typename Allocator>
		bool operator==(const ft::set<Key, Compare, Allocator> & lhs, const ft::set<Key, Compare, Allocator>& rhs){
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template <typename Key, typename Compare, typename Allocator>
		bool operator!=(const ft::set<Key, Compare, Allocator>& lhs, const ft::set<Key, Compare, Allocator>& rhs){
			return (!(lhs == rhs));
		}

		template <typename Key, typename Compare, typename Allocator>
		bool operator<(const ft::set<Key, Compare, Allocator>& lhs, const ft::set<Key, Compare, Allocator>& rhs){
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		template <typename Key, typename Compare, typename Allocator>
		bool operator>=(const ft::set<Key, Compare, Allocator>& lhs, const ft::set<Key, Compare, Allocator>& rhs){
			return (!(lhs < rhs));
		}

		template <typename Key, typename Compare, typename Allocator>
		bool operator>(const ft::set<Key, Compare, Allocator>& lhs, const ft::set<Key, Compare, Allocator>& rhs){
			return (rhs < lhs);
		}

		template <typename Key, typename Compare, typename Allocator>
		bool operator<=(const ft::set<Key, Compare, Allocator>& lhs, const ft::set<Key, Compare, Allocator>& rhs){
			return (!(rhs < lhs));
		}
}
#endif