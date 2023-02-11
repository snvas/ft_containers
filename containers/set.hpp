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

		const tree_type* tree() const { return &_tree; }
	
		/**
		 * Default Constructor
		 * Constructs an empty container, with no elements.
		 * creates a set with a size of 0
		*/
		set() : _size(0) {}

		explicit set(const Compare &comp, const Allocator& alloc = Allocator()) : _tree(comp, alloc), _size(0) {}
		
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

		/***************************Operator =*****************************/
		set& operator=(const set& other){
			if (this != &other){
				_tree = other._tree;
				_size = other._size;
			}
			return (*this);
		}

		/**
		 * Returns a copy of the allocator object associated with the set.
		*/
		allocator_type get_allocator() const{
			return (_tree.get_allocator());
		}

		/*************************** Iterators *****************************/
		/**
	 	* Return iterator to beginning
	 	* @return an iterator referring to the first node of the set(minimum value).
		*/
		iterator begin()
		{
			//node_type *node = this->_tree.minimum(this->_tree.get_root());
			//if (node){
			//	iterator it(node->left);
			//	return it;
			//}
			//return (NULL);

			iterator it(this->_tree.minimum(this->_tree.get_root()));
			return (it);
		}

		/**
		 * Return const_iterator to beginning
	 	* @return an const_iterator pointing to the first node of the set(minimum value).
		*/
		const_iterator begin() const
		{
			//node_type *node = this->_tree.minimum(this->_tree.get_root());
			//if (node){
			//	const_iterator it(node->left);
			//	return it;
			//}
			//return (NULL);

			const_iterator it(this->_tree.minimum(this->_tree.get_root()));
			return (it);
		}

		/**
		 * Returns an iterator referring to the past-the-end element in the set container.
		 * @return An iterator pointing after the last set's element, on a dummy node. 
		 * Access this iterator will result in undefined behavior.
		*/
		iterator end()
		{
			node_type *node = this->_tree.maximum(this->_tree.get_root());
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
		const_iterator end() const
		{
			node_type *node = this->_tree.maximum(this->_tree.get_root());
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
	reverse_iterator rbegin()
	{
			return (reverse_iterator(--this->end()));
	}
	
	/**
	 * Return const_reverse iterator to reverse beginning
	 * @return a const_reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
	*/
	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(--this->end()));
	}
	
	/**
	 * Return reverse iterator to reverse end
	 * @return  A reverse_iterator pointing before the first map's element, on a dummy node.
	 * Access this iterator will result in undefined behavior.
	 * 
	*/
	reverse_iterator rend()
	{
		return (reverse_iterator(--this->begin()));
	}

	/**
	 * Return a const_reverse iterator to reverse end
	 * @return  A const_reverse_iterator pointing before the first map's element, on a dummy node.
	 * Access this iterator will result in undefined behavior.
	 * 
	*/
	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(--this->begin()));
	}
	

		void clear(void){
				_tree.clear();
		}

		bool empty(void) const {
			if (this->_size == 0)
				return (true);
			return (false);
		}

		size_type size(void) const{
			return (_size);
		}

		size_type max_size(void) const{
			return (_tree.get_allocator().max_size());
		}

		ft::pair<iterator,bool> insert(const value_type &val){
			iterator it = this->find(val);
			if (it != end())
				return ft::make_pair(it, false);
			it = iterator(_tree.insert_value(val));
			_size++;

			return ft::make_pair(it, true);
		}

		iterator insert(iterator hint, const value_type& val){
			(void)hint;
			return insert(val).first;
		}

		template<class U>
		void insert(U first, U last, typename enable_if<!ft::is_integral<U>::value, U>::type * = 0){
			while (first != last)
				insert(*first++);
		}

		ft::pair<iterator, iterator> equal_range(const Key &k){
			return ft::make_pair(iterator(lower_bound(k)), iterator(upper_bound(k)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key &k) const{
			return (ft::make_pair(const_iterator(lower_bound(k)), const_iterator(upper_bound(k))));
		}

		iterator lower_bound(const Key& key) {
			node_type *node =  this->_tree.lower_bound(_tree.get_root(), key);
			if (!node)
				return (this->end());
			return (iterator(node));
		}

		const_iterator lower_bound(const Key& key) const{
				node_type *node =  this->_tree.lower_bound(_tree.get_root(), key);
			if (!node)
				return (this->end());
			return (const_iterator(node));
		}

		iterator upper_bound(const value_type& key) {
			node_type *node =  this->_tree.upper_bound(_tree.get_root(), key);
			if (!node)
				return (this->end());
			return (iterator(node));
		}

		const_iterator upper_bound(const value_type& key) const{
			node_type *node =  this->_tree.upper_bound(_tree.get_root(), key);
			if (!node)
				return (this->end());
			return (const_iterator(node));
		}

		iterator find(const Key& val) {
			node_type *n;
			n = _tree.lookup_value(val);
			if (!n)
				return (end());
			return iterator(n);
		}

		const_iterator find(const Key& val) const{
			node_type *n;
			n = _tree.lookup_value(val);
			if (!n)
				return (end());
			return const_iterator(n);
		}

		void erase(iterator position){
			_tree.delete_node(position.get_node_pointer());
			_size--;
		}

		void erase(iterator first, iterator last){
			iterator it;
			while (first != last){
				it = first;
				++first;
				_tree.delete_node(it.get_node_pointer());
			}
		}

		size_type erase(const key_type& k){
			if (this->_tree.delete_value(k))
		{
			this->_size -= 1;
			return (1);
		}
		return (0);
		}

		size_type count(const Key& key) const{
			size_type s = 0;
			for (const_iterator it = begin(); it != end(); it++)
				if (*it == key)
					s++;
			return s;
		}
		
		void swap(set& other){
			set temp = *this;
			*this = other;
			other = temp;
		}

		key_compare key_comp(void) const{
			return Compare();
		}

		value_compare value_comp(void) const{
			return (value_compare(key_comp()));
		}

		void print(Key const& vec) {
		typename Key::const_iterator it1 = vec.begin();
		typename Key::const_iterator it2 = vec.end();
		for (; it1 != it2; it1++) {
			std::cout << *it1 << " ";
		}
		std::cout << '\n';
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