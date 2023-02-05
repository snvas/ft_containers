#ifndef RBTREE_HPP
#define RBTREE_HPP

#define BLACK 0
#define RED 1
#define DOUBLE_BLACK 2

#define CRED "\033[91m"
#define CEND "\033[0m"

//#include "../containers/rb_iterator.hpp"

/*

Red-black tree class, designed for use in implementing STL
associative containers (set, multiset, map, and multimap). The
insertion and deletion algorithms are based on those in Cormen,
Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990),
except that

(1) the header cell is maintained with links not only to the root
but also to the leftmost node of the tree, to enable constant time
begin(), and to the rightmost node of the tree, to enable linear time
performance when used with the generic set algorithms (set_union,
etc.);

(2) when a node being deleted has two children its successor node is
relinked into its place, rather than copied, so that the only
iterators invalidated are those referring to the deleted node.

*/

namespace ft
{// a single node used by map to create a tree from
	template <typename T>
	struct Node
	{
		struct Node	*left;
		struct Node	*right;
		struct Node	*parent;
		int			color;
		T			*data;
		
		Node(T *value)
		{
			left = NULL;
			right = NULL;
			parent = NULL;
			color = RED;
			data = value;
		}
};
// the red-black-tree itself

// RED BLACK TREE RULES

// 	1. Every node is red or black
// 	2. Root is always black
// 	3. New insertions are always red
// 	4. Every path from root - leaf(NULL) has the same number of BLACK nodes
// 	5. No path can have two consecutice RED nodes
// 	6. NULLs are black
// 	7. Every node has two children

// Example tree to understand the child - parent - uncle relationship
//
// 				_root
// 			/			\.
// 		left			right
// 		/	\			/	\.
//	l1		r1		l2		r2
//
// root has two children: left and right
// the parent of l1 and r1 is left
// the uncle of l1 and r1 is right


// 		Rules for fixing an invalid red-black-tree

// 1. If we have BLACK uncle - rotate
// 	- if imbalance is in right child and right subtree - left rotation
// 	- if imbalance is in right child and left subtree - right/left rotation
// 	- if imbalance is in left child and right subtree - left/right rotation
// 	- if imbalance is in left child and left subtree - right rotation
// 2. If we have RED uncle - color flip
// 3. After rotation working nodes should look like: parent - black, childrens - red
// 4. After color flip working nodes should look like: parent - red, childrens - black
template <class T, 
		  class Compare, 
		  class Alloc = std::allocator<T>,
		  class Node_Alloc = std::allocator<Node<T> > >
class Rbtree
{
      public:
	typedef Compare						value_compare;
	typedef Alloc						allocator_type;
	typedef typename Node_Alloc::size_type size_type;
	typedef Node<T>						node_type;
	typedef Node_Alloc 					node_allocator_type;
	

      private:
	node_type 			*_root;
	allocator_type 		_alloc;
	value_compare 		_comp;
	node_allocator_type	_node_alloc;
	
	public:
	Rbtree(value_compare comp = value_compare(), allocator_type alloc = allocator_type(),
	       node_allocator_type node_alloc = node_allocator_type())
	    : _root(NULL), _alloc(alloc), _comp(comp), _node_alloc(node_alloc)
	{}

	~Rbtree(void)
	{
		destroy_nodes(this->_root);
	}

	Rbtree(const Rbtree &src)
	    : _root(NULL), _alloc(src._alloc), _comp(src._comp),
	      _node_alloc(src._node_alloc)
	{
		copy_nodes(src.get_root());
	}

	bool is_empty() const { 
		return this->_root == NULL; 
	}

	size_type max_size() const {
		return this->_node_alloc.max_size();
	}

	Rbtree &operator=(const Rbtree &src)
	{
		destroy_nodes(this->_root);
		this->_root = NULL;
		copy_nodes(src.get_root());
		return (*this);
	}

	static node_type *minimum(node_type *node)
	{
		if (node == NULL || node->left == NULL)
			return (NULL);
		while (!is_null_leaf(node->left))
			node = node->left;
		return (node);
	}

	static node_type *maximum(node_type *node)
	{
		if (node == NULL || node->right == NULL)
			return (NULL);
		while (!is_null_leaf(node->right))
			node = node->right;
		return (node);
	}

	static node_type *successor(node_type *node)
	{
		if (!node)
			return (NULL);
		if (node->right && !is_null_leaf(node->right))
			return (minimum(node->right));
		if (node->parent && node->parent->left == node)
			return (node->parent);
		node_type *next_above = find_successor(node);
		if (next_above)
			return (next_above);
		return (node->right);
	}

	static node_type *predecessor(node_type *node)
	{
		if (!node)
			return (NULL);
		if (node->left && !is_null_leaf(node->left))
			return (maximum(node->left));
		if (node->parent && node->parent->right == node)
			return (node->parent);
		node_type *prev_above = find_predecessor(node);
		if (prev_above)
			return (prev_above);
		return (node->left);
	}

	static bool is_null_leaf(const node_type *node)
	{
		if (!node)
			return (false);
		if (node->data == NULL && node->left == NULL &&
		    node->right == NULL)
			return (true);
		return (false);
	}

	node_type *create_null_node(node_type *p)
	{
		node_type null_node(NULL);
		node_type *node_ptr = _node_alloc.allocate(1);
		null_node.parent = p;
		null_node.left = NULL;
		null_node.right = NULL;
		null_node.color = BLACK;
		_node_alloc.construct(node_ptr, null_node);
		return node_ptr;
	}

	node_type *insert_value(T value)
	{
		T *node_data = _alloc.allocate(1);
		_alloc.construct(node_data, value);

		node_type *node_ptr = _node_alloc.allocate(1);
		node_type node(node_data);
		node.left = create_null_node(node_ptr);
		node.right = create_null_node(node_ptr);
		_node_alloc.construct(node_ptr, node);
		this->_root = insert_BST(this->_root, node_ptr);
		fix_insert_RBT(node_ptr);
		return (node_ptr);
	}

	node_type *insert_value(node_type *pos, T value)
	{
		if (!is_null_leaf(this->successor(pos)) &&
		    this->_comp(*this->successor(pos)->data, value)){
			return insert_value(value);
		}
		T *node_data = _alloc.allocate(1);
		_alloc.construct(node_data, value);

		node_type *node_ptr = _node_alloc.allocate(1);
		node_type node(node_data);
		node.left = create_null_node(node_ptr);
		node.right = create_null_node(node_ptr);
		_node_alloc.construct(node_ptr, node);
		pos = insert_BST(pos, node_ptr);
		fix_insert_RBT(pos);
		return (node_ptr);
	}

	node_type *lookup_value(T value) const
	{
		node_type *node = this->_root;
		while (node && !is_null_leaf(node))
		{
			if (this->_comp(value, *node->data))
				node = node->left;
			else if (this->_comp(*node->data, value))
				node = node->right;
			else
				return (node);
		}
		return (NULL);
	}

	node_type *lookup_value(node_type *root, const T value) const
	{
		if (!root || is_null_leaf(root))
			return (NULL);
		if (this->_comp(value, *root->data))
			return (lookup_value(root->left, value));
		else if (this->_comp(*root->data, value))
			return (lookup_value(root->right, value));
		return (root);
	}

	node_type *lower_bound(node_type *root, const T &value) const{
		node_type *x;
		if (!root || is_null_leaf(root))
			return (NULL);
		if (this->_comp(value, *root->data)){
			x = lower_bound(root->left, value);
			if (!x)
				return root; 
			return x;
		}
		if (this->_comp(*root->data, value)){
			return lower_bound(root->right, value);;
		}
		return (root);
	}

	node_type *upper_bound(node_type *root, const T &value) const{
		node_type *x = NULL;
		while (root && !is_null_leaf(root)){
			if (this->_comp(value, *root->data)){
				x = root;
				root = root->left;
			}
			else 
				root = root->right;
		}
		return (x);
	}

	size_t delete_value(T value)
	{
		node_type *node = lookup_value(this->_root, value);
		if (node)
		{
			delete_node(node);
			return (1);
		}
		return (0);
	}

	node_type *get_root(void) const
	{
		return (this->_root);
	}

	void swap(Rbtree &src)
	{
		std::swap(this->_root, src._root);
		std::swap(this->_alloc, src._alloc);
		std::swap(this->_comp, src._comp);
	}

	T get_root_data(void)
	{
		return (*this->_root->data);
	}

	const allocator_type& get_allocator() const{
			return (_alloc);
		}

	void clear(void)
	{
		this->destroy_nodes(this->_root);
		this->_root = NULL;
	}
	
	//   Q (nodeGoingUp) is going up and will replace P (nodeGoingDown)
	//
	//
	//               Q                                 P              |
	//              / \          LEFT ROTATION        / \             |
	//             P   C    <<<-------------------   A   Q            |
	//            / \                                   / \           |
	//           A   B                                 B   C          |

	// left rotates the given node
	void rotate_left(node_type *n)
	{
		//new parent will be node's right child
		node_type *right = n->right;
		
		n->right = right->left;
		if (n->right)
			n->right->parent = n;
		right->parent = n->parent;
		if (n->parent == NULL)
			this->_root = right;
		else if (n->parent->left == n)
			n->parent->left = right;
		else
			n->parent->right = right;
		n->parent = right;
		right->left = n;
	}

	//   P (nodeGoingUp) is going up and will replace Q (nodeGoingDown)
	//
	//
	//               Q                                 P              |
	//              / \     RIGHT ROTATION            / \             |
	//             P   C  ------------------->>>     A   Q            |
	//            / \                                   / \           |
	//           A   B                                 B   C          |

	void rotate_right(node_type *n)
	{
		node_type *left = n->left;
		n->left = left->right;
		if (n->left)
			n->left->parent = n;
		left->parent = n->parent;
		if (n->parent == NULL)
			this->_root = left;
		else if (n->parent->left == n)
			n->parent->left = left;
		else
			n->parent->right = left;
		n->parent = left;
		left->right = n;
	}

	node_type *insert_BST(node_type *root, node_type *value)
	{
		if (!root)
			return (value);
		if (is_null_leaf(root))
		{
			destroy_node(root);
			return (value);
		}
		if (this->_comp(*value->data, *root->data))
		{
			root->left = insert_BST(root->left, value);
			root->left->parent = root;
		}
		else if (this->_comp(*root->data, *value->data))
		{
			root->right = insert_BST(root->right, value);
			root->right->parent = root;
		}
		return (root);
	}

	void fix_insert_RBT(node_type *node)
	{
		node_type *uncle = NULL;
		while (node != this->_root && get_color(node->parent) == RED)
		{
			if (node->parent == node->parent->parent->right)
			{
				uncle = node->parent->parent->left;
				if (get_color(uncle) == RED)
				{
					set_color(uncle, BLACK);
					set_color(node->parent, BLACK);
					set_color(node->parent->parent, RED);
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rotate_right(node);
					}
					set_color(node->parent, BLACK);
					set_color(node->parent->parent, RED);
					rotate_left(node->parent->parent);
				}
			}
			else
			{
				uncle = node->parent->parent->right;
				if (get_color(uncle) == RED)
				{
					set_color(uncle, BLACK);
					set_color(node->parent, BLACK);
					set_color(node->parent->parent, RED);
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						rotate_left(node);
					}
					set_color(node->parent, BLACK);
					set_color(node->parent->parent, RED);
					rotate_right(node->parent->parent);
				}
			}
		}
		set_color(this->_root, BLACK);
		return;
	}

	int get_color(node_type *node)
	{
		if (node == NULL)
			return BLACK;
		return (node->color);
	}

	void set_color(node_type *node, int color)
	{
		if (node == NULL)
			return;
		node->color = color;
	}

	void transplant(node_type *u, node_type *v)
	{
		if (!u->parent)
			this->_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v)
			v->parent = u->parent;
	}
//new *uncle - returns pointer to uncle
	/*node_type *uncle(node_type *n){
		// If no parent or grandparent, then no uncle
		if (n->parent == NULL || n->parent->parent == NULL)
			return NULL;
		if (n->parent->isOnLeft())
			//uncle on right;
			return n->parent->parent->right;
		else
		//uncle on left;
			return n->parent->parent->left;
	}
//new isonleft - check if node is left child of parent
	bool isOnLeft(){ return this == this->parent->left; }

// returns pointer to sibling
	node_type *sibling(node_type *n){
		if (n->parent == NULL)
			return NULL;
		if (isOnLeft())
			return n->parent->right;
		return n->parent->left;
	}

	bool hasRedChild(){
		return (this->left != NULL && this->left->color == 1)
			|| (this->right != NULL && this->right->color == 1);
	}// this function check if has a red child
*/

	//function that recoloring nodes after delete
	void fix_delete_RBT(node_type *node)
	{
		node_type *sibling;
		while (node != this->_root && get_color(node) == BLACK)
		//enquanto não for o root e a cor for preto
		{
			if (node == node->parent->left)
			//se node for igual o pai esquerdo
			{
				sibling = node->parent->right;
				//sibling recebe o pai direito
				if (get_color(sibling) == RED)
				{
					set_color(sibling, BLACK);
					//set a color for sibling like black
					set_color(node->parent, RED);
					//set color for parent like red
					rotate_left(node->parent);
					//rotaciona o pai para a esquerda
					sibling = node->parent->right;
					//recebe o pai direito
				}
				if (get_color(sibling->left) == BLACK &&
				    get_color(sibling->right) == BLACK)
					//se os dois irmãos são preto
				{
					set_color(sibling, RED);
					//seta a cor Red para o irmão
					node = node->parent;
					// node recebe o pai
				}
				else
				{
					if (get_color(sibling->right) == BLACK)
					//se o irmão a direita é black
					{
						set_color(sibling->left, BLACK);
						//seta a cor Black para o irmão a esquerda
						set_color(sibling, RED);
						//seta a cor Red para o irmão
						rotate_right(sibling);
						//rotaciona sibling
						sibling = node->parent->right;
						//sibling recebe o pai a direita
					}
					set_color(sibling, get_color(node->parent));
					//set cor de sibling com a cor do pai
					set_color(node->parent, BLACK);
					//seta a cor do pai para black
					set_color(sibling->right, BLACK);
					//seta a cor do irmão à direita Black
					rotate_left(node->parent);
					//rotaciona o pai
					break;
				}
			}
			else
			{
				sibling = node->parent->left;
				//sibling recebe o pai à esquerda
				if (get_color(sibling) == RED)
				//se a cor de sibling for Red
				{
					set_color(sibling, BLACK);
					//seta a cor do sibling para Black
					set_color(node->parent, RED);
					//seta a cor do pai para red
					rotate_right(node->parent);
					//rotaciona o pai para direita
					sibling = node->parent->left;
					//sibling recebe o pai à esquerda
				}
				if (get_color(sibling->right) == BLACK &&
				    get_color(sibling->left) == BLACK)
					//se os dois irmãos são Black
				{
					set_color(sibling, RED);
					//seta cor Red para sibling
					node = node->parent;
					//node reber o pai
				}
				else
				{
					if (get_color(sibling->left) == BLACK)
					{
						set_color(sibling->right,
							  BLACK);
						set_color(sibling, RED);
						rotate_left(sibling);
						sibling = node->parent->left;
					}
					set_color(sibling,
						  get_color(node->parent));
					set_color(node->parent, BLACK);
					set_color(sibling->left, BLACK);
					rotate_right(node->parent);
					break;
				}
			}
		}
		set_color(node, BLACK);
	}
	

	void delete_node(node_type *node)
	{
		if (!node)
			return;
		node_type *root = this->_root;
		node_type *temp = NULL;

		while (temp == NULL && root != NULL && !is_null_leaf(root))
		{
			if (*node->data == *root->data)
				temp = root;
			if (this->_comp(*node->data, *root->data))
				root = root->left;
			else
				root = root->right;
		}
		if (!temp || is_null_leaf(temp))
			return;

		node_type *aux;
		node_type *temp2 = temp;
		int temp_original_color = temp2->color;
		if (is_null_leaf(temp->left))
		{
			aux = temp->right;
			destroy_node(temp->left);
			transplant(temp, temp->right);
		}
		else if (is_null_leaf(temp->right))
		{
			aux = temp->left;
			destroy_node(temp->right);
			transplant(temp, temp->left);
		}
		else
		{
			temp2 = minimum(temp->right);
			temp_original_color = temp2->color;
			aux = temp2->right;
			if (temp2->parent == temp)
				aux->parent = temp2;
			else
			{
				transplant(temp2, temp2->right);
				temp2->right = temp->right;
				temp2->right->parent = temp2;
			}
			transplant(temp, temp2);
			destroy_node(temp2->left);
			temp2->left = temp->left;
			temp2->left->parent = temp2;
			temp2->color = temp->color;
		}
		destroy_node(temp);
		if (temp_original_color == BLACK)
			fix_delete_RBT(aux);
	}
	void destroy_nodes(node_type *node)
	{
		if (!node)
			return;
		destroy_nodes(node->left);
		destroy_nodes(node->right);
		destroy_node(node);
	}

	void destroy_node(node_type *node)
	{
		if (node == NULL){
			return;
		}
		if (node->data != NULL)
		{
			_alloc.destroy(node->data);
			_alloc.deallocate(node->data, 1);
		}
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
	}

	static node_type *find_successor(node_type *node)
	{
		if (!node || !node->parent)
			return (NULL);
		if (node->parent->left == node)
			return (node->parent);
		return (find_successor(node->parent));
	}

	static node_type *find_predecessor(node_type *node)
	{
		if (!node || !node->parent)
			return (NULL);
		if (node->parent->right == node)
			return (node->parent);
		return (find_predecessor(node->parent));
	}

	void copy_nodes(const node_type *node)
	{
		if (!node || is_null_leaf(node))
			return;
		copy_nodes(node->left);
		insert_value(*node->data);
		copy_nodes(node->right);
	}

	//iterator begin(void) { return iterator(minimum(_root))}
	//const_iterator begin(void) { return const_iterator(minimum(_root))}
	//iterator rbegin(void) { return reverse_iterator(maximum(_root))}
	//const_iterator rbegin(void) { return const_reverse_iterator(maximum(_root))}


		void printBT(const std::string &prefix, const node_type *node, bool isRight){
			if(node){
				std::cout << prefix;
				std::cout << (isRight ? "├──" : "└──");
				// print the value of the node
				std::cout << (node->color ? CRED : CEND);
				if (this->is_null_leaf(node))
					std::cout << "N";
				else
					std::cout << node->data->first;
				std::cout << CEND << std::endl;
			//enter the next level of the tree - left and right branch
				if (!this->is_null_leaf(node)){
					printBT(prefix + (isRight ? "|    " : "    "), node->right, true);
					printBT(prefix + (isRight ? "|    " : "    "), node->left, false);
				}
			}
		}

		void printBT(){
			std::cout << "---" << std::endl;
			printBT("", this->get_root(), false);
			std::cout << "---" << std::endl;
		}

	};
} // namespace ft
#endif
