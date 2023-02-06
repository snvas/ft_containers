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
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Allocator allocator_type;
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
		//typedef typename tree_type::iterator		iterator;
		//typedef typename tree_type::const_iterator	const_iterator;
		//typedef typename tree_type::reverse_iterator	reverse_iterator;
		//typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

	protected:
		tree_type 							_tree;
		size_type 							_size;

	public:
		const tree_type* tree() const { return &_tree; }
	
		set() : _size(0) {}

		explicit set(const Compare &comp, const Allocator& alloc = Allocator()) : _tree(comp, alloc), _size(0) {}
		
		template<class U>
		set(U first, U last, 
			const Compare& comp = Compare(), 
			const Allocator& alloc = Allocator()) : _tree(comp, alloc), _size(0){
				while (first != last){
					insert(*first);
					++first;
				}
			}


		set(const set& other) : _tree(other._tree), _size(other._size) {}

		~set(void){
			clear();
		 }

		set& operator=(const set& other){
			if (this != &other){
				_tree = other._tree;
				_size = other._size;
			}
			return (*this);
		}

		allocator_type get_allocator() const{
			return (_tree.get_allocator());
		}

		iterator begin()
		{
			iterator it(this->_tree.minimum(this->_tree.get_root()));
			return (it);
		}

		const_iterator begin() const
		{
			const_iterator it(this->_tree.minimum(this->_tree.get_root()));
			return (it);
		}

		//Return iterator to end - Returns an iterator referring to the past-the-end element in the map container.
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
		
		const_iterator end() const
		{
			node_type *node = this->_tree.maximum(this->_tree.get_root());
			const_iterator it(node->right);
			return (it);
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
			node_type *n;
			node_type *res;
			res = end().base();
			if (!_size)
				return iterator(res);
			n = _tree->root();
			while (1){
				if ((*n).data == key){
					res = n;
					break;
				} else if (!_comp((*n).data, key)){
					res = n;
					if (!n->left)
						break;
					n = n->left;
				} else if (_comp((*n).data, key)){
					if (!n->right)
						break;
					n = n->right;
				}
			}
			return iterator(res);
		}

		const_iterator lower_bound(const Key& key) const{
			node_type *n;
			const node_type *res;
			res = end().base();
			if (!_size)
				return const_iterator(res);
			n = _tree->root();
			while (1){
				if ((*n).data == key){
					res = n;
					break;
				} else if (!_comp((*n).data, key)){
					res = n;
					if (!n->left)
						break;
					n = n->left;
				} else if (_comp((*n).data, key)){
					if (!n->right)
						break;
					n = n->right;
				}
			}
			return const_iterator(res);
		}

		iterator upper_bound(const value_type& key) {
			node_type *n;
			node_type *res;
			res = end().base();
			if (!_size)
				return iterator(res);
			n = _tree->root();
			while (1){
				if ((*n).data == key){
						if (!n->right)
							break;
						n = n->right;
				} else if (!_comp((*n).data, key)){
					res = n;
					if (!n->left)
						break;
					n = n->left;
				} else if (_comp((*n).data, key)){
					if (!n->right)
						break;
					n = n->right;
				}
			}
			return iterator(res);
		}

		const_iterator upper_bound(const value_type& key) const{
			node_type *n;
			const node_type *res;
			res = end().base();
			if (!_size)
				return const_iterator(res);
			n = _tree->root();
			while (1){
				if ((*n).data == key){
						if (!n->right)
							break;
						n = n->right;
				} else if (!_comp((*n).data, key)){
					res = n;
					if (!n->left)
						break;
					n = n->left;
				} else if (_comp((*n).data, key)){
					if (!n->right)
						break;
					n = n->right;
				}
			}
			return const_iterator(res);
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
			_tree.delete_node(*position);
			_size--;
		}

		void erase(iterator first, iterator last){
			for (iterator it = first; it != last; it++){
				erase(it);
			}
		}

		size_type erase(const key_type& k){
			iterator ite = this->find(k);
			if (ite != end()){
				this->_tree.remove(ite.base());
				_size--;
				return (1);
			}
			return 0;
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
			return (value_compare());
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