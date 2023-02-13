#ifndef RBTREE_HPP
#define RBTREE_HPP

#define BLACK 0
#define RED 1

#define CRED "\033[91m"
#define CEND "\033[0m"

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
{// a single node used to create a tree
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
/* the red-black-tree itself
* RED BLACK TREE RULES
* 	1. Every node is red or black
* 	2. Root is always black
* 	3. New insertions are always red
* 	4. Every path from root - leaf(NULL) has the same number of BLACK nodes
* 	5. No path can have two consecutice RED nodes
* 	6. NULLs are black
* 	7. Every node has two children
*	
*	Rules for Inserting Nodes in Red Black Tree
*	1-If the tree is empty, then create a new node as the root node and colour it black.
*	2-If the tree is not empty, then create a new node as the leaf node with the colour red.
*	3-If the parent of a new node is of black colour, then take the exit.
*	4-If the parent of a new node is red, then check the colour of the parent's sibling of a new node.
*	a-If the colour is black or NULL' then do proper rotation and recolour it.
*	b-If the colour is red, then recolour it and check if the parent's parent of the new node is not 
*	the root node, then recolour it and recheck.
*
* Example tree to understand the child - parent - uncle relationship
 				_root
 			/			\.
 		left			right
 		/	\			/	\.
	l1		r1		l2		r2

* root has two children: left and right
* the parent of l1 and r1 is left
* the uncle of l1 and r1 is right

* 		Rules for fixing an invalid red-black-tree
* 1. If we have BLACK uncle - rotate
* 	- if imbalance is in right child and right subtree - left rotation
* 	- if imbalance is in right child and left subtree - right/left rotation
* 	- if imbalance is in left child and right subtree - left/right rotation
* 	- if imbalance is in left child and left subtree - right rotation
* 2. If we have RED uncle - color flip
* 3. After rotation working nodes should look like: parent - black, childrens - red
* 4. After color flip working nodes should look like: parent - red, childrens - black
*/
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
	// ###########################################################################
	// #                              CONSTRUCTORS                               #
	// ###########################################################################
	/**
	 * The constructor for the Red-Black tree class Rbtree. It has three parameters:
	 * @param comp The comparison function for the key values of the nodes in the tree. By default, it uses the value_compare type
	 * @param alloc The memory allocation policy for the values in the nodes of the tree. By default, it uses the allocator_type
	 * @param node_alloc The memory allocation policy for the nodes of the tree. By default, it uses the node_allocator_type
	 * In the constructor, the root of the tree is initialized to NULL, the comparison function, 
	 * memory allocation policy, and node memory allocation policy are initialized with the corresponding parameters.
	*/
	Rbtree(value_compare comp = value_compare(), allocator_type alloc = allocator_type(),
	       node_allocator_type node_alloc = node_allocator_type())
	    : _root(NULL), _alloc(alloc), _comp(comp), _node_alloc(node_alloc)
	{}

	/**
	 * the destructor of the Rbtree class. 
	 * It takes no arguments and returns no value. 
	 * The purpose of this function is to clean up memory associated with the tree when the tree is destroyed.
	 * The function calls the destroy_nodes method and passes in the root node of the tree to 
	 * delete all the nodes in the tree, freeing up memory that was allocated for the nodes.
	*/
	~Rbtree(void)
	{
		destroy_nodes(this->_root);
	}

	//copy constructor
	/**creates a new instance of a red-black tree by copying the data from another red-black tree src.
	 * The constructor takes as input a constant reference to another red-black tree src. 
	 * It initializes the root of the new tree to NULL, and sets the allocator, comparator, 
	 * and node allocator of the new tree to be the same as the src tree.
	 * Finally, the constructor calls the copy_nodes function to copy all the nodes from the src tree to the new tree.*/
	Rbtree(const Rbtree &src)
	    : _root(NULL), _alloc(src._alloc), _comp(src._comp),
	      _node_alloc(src._node_alloc)
	{
		copy_nodes(src.get_root());
	}

	//operator=
	/**
	 * an overloaded assignment operator for the Red-Black Tree class Rbtree. 
	 * It is used to assign one Red-Black Tree to another.
	 * The function first destroys the nodes of the current tree by calling the destroy_nodes function 
	 * with the root node of the current tree as an argument. Then it sets the root node of the current tree to NULL.
	 * After that, it copies all the nodes of the source tree (passed as an argument to the function) 
	 * to the current tree by calling the copy_nodes function with the root node of the source tree as an argument.
	 * Finally, the function returns the reference to the current tree.
	*/
	Rbtree &operator=(const Rbtree &src)
	{
		destroy_nodes(this->_root);
		this->_root = NULL;
		copy_nodes(src.get_root());
		return (*this);
	}


	// #############################################################################
	// #                                ASSESSORS                                  #
	// #############################################################################

	/** function to find the minimum value at the tree
	 * takes in a pointer to a node in a red-black tree, 
	 * and returns the node with the minimum value in the subtree rooted at that node.
	 * The function first checks if the input node is NULL or if the left child of the input node is NULL. 
	 * If either of these conditions is true, the function returns NULL.
	 * Otherwise, the function repeatedly sets node to its left child, until it reaches a node with a NULL left child. 
	 * The function then returns that node, which is the node with the minimum value in the subtree.
	*/
	static node_type *minValueNode(node_type *node)
	{
		if (node == NULL || node->left == NULL)
			return (NULL);
		while (!is_null_leaf(node->left))
			node = node->left;
		return (node);
	}

	/**function to find the maxValueNode value at the tree
	 * takes a pointer to a node in a red-black tree as an argument 
	 * and returns the node with the maximum value in that tree. 
	 * The function starts from the input node, checks if the node is NULL or its right child is NULL. 
	 * If either of these conditions is true, it returns NULL. 
	 * If not, it keeps moving to the right child of the node until it finds a null leaf, 
	 * which represents the end of the tree and returns that node, which is the node with the maximum value.
	*/
	static node_type *maxValueNode(node_type *node)
	{
		if (node == NULL || node->right == NULL)
			return (NULL);
		while (!is_null_leaf(node->right))
			node = node->right;
		return (node);
	}

	/** function returns the in-order successor 
	 * of a given node in a binary search tree
	*/
	static node_type *successor(node_type *node)
	{
		if (!node)
			return (NULL);
		// checking for the right child of the node first.
		if (node->right && !is_null_leaf(node->right))
		//If the right child exists and is not a null leaf, 
		//then the successor will be the node with the minimum value in the right subtree
			return (minValueNode(node->right));
		/** If the right child doesn't exist or is a null leaf, 
		/ then looks for the parent of the node and if the parent's left child 
		/ is equal to the node, then the parent is returned as the successor*/
		if (node->parent && node->parent->left == node)
			return (node->parent);
		/** If the parent's left child is not equal to the node, 
		/ then looks for the successor above the node by calling the function find_successor(node)*/
		node_type *next_above = find_successor(node);
		if (next_above)
		// If the successor is found above, it's returned
			return (next_above);
		//If no successor is found, then the right child of the node is returned
		return (node->right);
	}

	/**
	 * finds the predecessor node of a given node in a tree. 
	 * The predecessor of a node in a tree is the node with the largest 
	 * value that is smaller than the given node's value.
	*/
	static node_type *predecessor(node_type *node)
	{
		//check if the node passed as an argument is NULL, and if so, it returns NULL.
		if (!node)
			return (NULL);
		/* Next, if the given node has a non-NULL left child and it's not a null leaf, 
		/then the predecessor node is the maximum value node in the left subtree.
		*/
		if (node->left && !is_null_leaf(node->left))
		//find the maximum value node in the left subtree
			return (maxValueNode(node->left));
		/* If the given node's parent exists and its parent's right child is 
		/equal to the given node, then the parent node is the predecessor.*/
		if (node->parent && node->parent->right == node)
			return (node->parent);
		/*If the given node's parent exists, then the function find_predecessor(node) 
		/is called to find the predecessor node.*/
		node_type *prev_above = find_predecessor(node);
		//If find_predecessor(node) returns a non-NULL node, then it is returned as the predecessor.
		if (prev_above)
			return (prev_above);
		/* if all the above conditions are not met, the left child of the given node 
		/is returned as the predecessor.*/
		return (node->left);
	}

	/**
	 * checks if the RBTree is empty by checking if its root node is NULL. 
	 * If the root is NULL, then it returns true, indicating that the tree is empty. 
	 * If the root is not NULL, then it returns false, indicating that the tree is not empty.
	*/
	bool is_empty() const { 
		return this->_root == NULL; 
	}

	/*This function returns the maximum size of the container that the red-black tree can hold, 
	which is determined by the maximum size of the node_type allocator. 
	It is usually determined by the amount of memory available in the system. 
	This information can be useful in determining the performance and memory constraints of the container. 
	The return type is size_type, which is an alias for an unsigned integer type.*/
	size_type max_size() const {
		return this->_node_alloc.max_size();
	}

	/** function returns a pointer to the root node of the red-black tree. 
	 * This is a constant function, meaning that it cannot modify the contents of the tree. 
	 * The purpose of this function is to allow access to the root node, 
	 * which is the starting point of the tree, 
	 * so that other functions can traverse and manipulate the tree as needed.*/
	node_type *get_root(void) const
	{
		return (this->_root);
	}

	/**
	 * returns the data stored in the root node of the red-black tree. 
	 * If the root node exists, the data it stores is dereferenced and returned. 
	 * If the root node does not exist, this function will likely result in an error or undefined behavior.
	*/
	T get_root_data(void)
	{
		return (*this->_root->data);
	}

	/**returns a constant reference to the allocator that's being used to allocate memory 
	 * for the elements stored in the data structure. 
	 * The allocator is an object that is responsible for managing the memory used by the data structure 
	 * and for creating and deleting objects of a specific type. The return value of this function 
	 * can be used to compare the allocator being used in the data structure with other allocators.*/
	const allocator_type& get_allocator() const{
			return (_alloc);
	}

	// ###########################################################################
	// #                            MEMBER FUNCTIONS                             #
	// ###########################################################################

	/*
	* Determine whether a given node is a "null leaf" in the tree.
	* A null leaf is a special type of node in a binary tree that serves as a marker 
	* to indicate the end of a branch. It has the properties that its data field is NULL, 
	* and both its left and right fields are also NULL. The function starts by checking 
	* if the input node is NULL.
	*/
	static bool is_null_leaf(const node_type *node)
	{
		//If node is NULL, the function returns false immediately
		if (!node)
			return (false);
		/** If node is not NULL, the function checks if the data field of node is NULL 
		 * and both the left and right fields are NULL. If these conditions are met, 
		 * returns true, indicating that the input node is a null leaf. */
		if (node->data == NULL && node->left == NULL &&
		    node->right == NULL)
			return (true);
		// If these conditions are not met, the function returns false, 
		// indicating that the input node is not a null leaf
		return (false);
	}

	/** Creates a new null leaf node in the tree
	 * Takes as input a pointer to a node in the tree (p), which is 
	 * meant to be the parent of the new null leaf node. 
	*/
	node_type *create_null_node(node_type *p)
	{
		//creates a new node using an object of type node_type with NULL data
		node_type null_node(NULL);
		node_type *node_ptr = _node_alloc.allocate(1);
		//The new node's parent field is set to p
		null_node.parent = p;
		//both its left and right fields are set to NULL
		null_node.left = NULL;
		null_node.right = NULL;
		//The new node's color is set to BLACK
		null_node.color = BLACK;
		/** Then allocates memory for the new node using an object of type _node_alloc, 
		 * calls the construct method of _node_alloc to construct the 
		 * new node in the allocated memory*/
		_node_alloc.construct(node_ptr, null_node);
		//returns a pointer to the newly created node
		return node_ptr;
	}

	/** inserts a new node into the red-black tree
	 * The function takes as input a value of type T (value), 
	 * which is the value to be inserted into the tree. 
	*/
	node_type *insert_value(T value)
	{
		// first allocates memory for the new data using an object of type _alloc
		T *node_data = _alloc.allocate(1);
		// construct the new data in the allocated memory
		_alloc.construct(node_data, value);
		// allocates memory for the new node using an object of type _node_alloc
		node_type *node_ptr = _node_alloc.allocate(1);
		// creates a new object of type node_type with the new data
		node_type node(node_data);
		// sets its left and right fields to be two new null leaf nodes
		node.left = create_null_node(node_ptr);
		node.right = create_null_node(node_ptr);
		// construct the new node in the allocated memory
		_node_alloc.construct(node_ptr, node);
		//calls the insert_BST function to insert the new node into the red-black tree
		this->_root = insert_BST(this->_root, node_ptr);
		// calls the fix_insert_RBT function to fix any violations of the red-black tree 
		//properties caused by the insertion of the new node
		fix_insert_RBT(node_ptr);
		// returns a pointer to the newly inserted node
		return (node_ptr);
	}

	/** insertion of a value into a red-black tree. It takes a pointer to 
	 * a node, pos, and a value value as input.
	 */
	node_type *insert_value(node_type *pos, T value)
	{
		/** Check if the successor of pos is not a null leaf and if the 
		 * value of the successor is less than the value. If this is true, 
		 * it calls the insert_value function with just the value as input 
		 * to insert the value in the standard manner.*/
		if (!is_null_leaf(this->successor(pos)) &&
		    this->_comp(*this->successor(pos)->data, value)){
			return insert_value(value);
		}
		//Otherwise, it allocates memory for the data of the node
		T *node_data = _alloc.allocate(1);
		// constructs the data in place
		_alloc.construct(node_data, value);
		// allocates memory for the node
		node_type *node_ptr = _node_alloc.allocate(1);
		// creates a new node with the data
		node_type node(node_data);
		// creates two null children for the node, both pointing to the parent
		node.left = create_null_node(node_ptr);
		node.right = create_null_node(node_ptr);
		_node_alloc.construct(node_ptr, node);
		// inserts the node in the BST 
		pos = insert_BST(pos, node_ptr);
		// fixes the red-black tree properties
		fix_insert_RBT(pos);
		// returns a pointer to the newly inserted node
		return (node_ptr);
	}

	//search for a node in a red-black tree data structure that has the specified value
	node_type *lookup_value(T value) const
	{
		node_type *node = this->_root;
		/* starts at the root of the tree and moves down the tree using a binary search, 
		/ comparing the input value to the value stored at each node*/
		while (node && !is_null_leaf(node))
		{
			//If the input value is smaller than the value at a node, the function moves to the left child
			if (this->_comp(value, *node->data))// menor
				node = node->left;
			//if it's larger, it moves to the right child
			else if (this->_comp(*node->data, value))//maior
				node = node->right;
			/*If encounters a node that has a value equal to the input value, 
			/it returns a pointer to that node*/
			else
				return (node);
		}
		/*If the function reaches a NULL node, meaning it has exhausted all possible paths 
		in the tree and could not find the value, it returns NULL as well.*/
		return (NULL);
	}

	/** a recursive function to look for a value in a binary search tree
	 * Takes as input the root of the tree and the value to look for.
	 * Uses the comparison function _comp defined in the class to compare 
	 * the value with the data stored in the root and its left and right children.
	*/
	node_type *lookup_value(node_type *root, const T value) const
	{
		/** Checks if the root is not null and if it is not a null leaf node.
		 * If it is either null or a null leaf node, the function returns null, 
		 * indicating that the value is not present in the tree.
		 */
		if (!root || is_null_leaf(root))
			return (NULL);
		/*If the value is smaller than the data stored in the root, 
		/ it recursively calls lookup_value on the left subtree*/
		if (this->_comp(value, *root->data))//menor
			return (lookup_value(root->left, value));
		/*If the value is greater than the data stored in the root, 
		it recursively calls lookup_value on the right subtree.*/
		else if (this->_comp(*root->data, value))//maior
			return (lookup_value(root->right, value));
		//If the value is equal to the data stored in the root, returns the root.
		return (root);
	}

	/**
	 * Function to find the lower bound in a binary tree. 
	 * The lower bound is the first element in the tree whose value is equal to 
	 * or greater than the specified value.
	 * The function takes as input a pointer to the root of the tree (root) 
	 * and the value to be searched for (value). 
	 * The type of data stored in the tree is specified by the generic type T.
	 * The comparator used in the comparison is obtained from the 
	 * member variable _comp of the class that contains this function.
	 * */
	node_type *lower_bound(node_type *root, const T &value) const{
		node_type *x;
		//checking if the root of the tree is null or if it is a null leaf 
		//(using the is_null_leaf function), and in this case returns NULL
		if (!root || is_null_leaf(root))
			return (NULL);
		//Then compares the value value with the data stored in the root of the tree.
		if (this->_comp(value, *root->data)){// menor
			//If value is less, the function calls itself recursively with the left 
			//subtree of the root and returns the result. 
			x = lower_bound(root->left, value);
			if (!x)
				return root; 
			return x;
		}
		//If value is greater, the function calls itself recursively with the right 
		//subtree of the root and returns the result. 
		if (this->_comp(*root->data, value)){// maior
			return lower_bound(root->right, value);;
		}
		//If value is equal to the data stored in the 
		//root of the tree, the function returns the root.
		return (root);
	}

	/**
	 * Find the "upper bound" in a binary tree. 
	 * The "upper bound" is the first element in the tree whose value 
	 * is greater than the specified value.
	 * The function takes as input a pointer to the root of the tree (root) 
	 * and the value to be searched for (value). The type of data stored in 
	 * the tree is specified by the generic type T.
	 * The comparator used in the comparison is obtained from the 
	 * member variable _comp of the class that contains this function.
	*/
	node_type *upper_bound(node_type *root, const T &value) const{
		node_type *x = NULL;
		/*a while loop to traverse the tree, starting from the root. 
		* The loop continues as long as the current node (root) 
		* is not NULL and is not a null leaf*/
		while (root && !is_null_leaf(root)){
			//compares the value value with the data stored in the current node (root->data)
			if (this->_comp(value, *root->data)){
				/* If value is less, the function sets a temporary variable x 
				to the current node and moves to the left subtree of the current node.
				*/
				x = root;
				root = root->left;
			}
			else 
				/* If value is greater or equal, the function moves to the 
				right subtree of the current node.*/
				root = root->right;
		}
		/* When the loop terminates, the function returns the value of x. 
		If the loop never enters the branch that sets x, this means that 
		no upper bound was found and the function returns NULL. 
		If the loop enters this branch, the value of x will be the upper bound in the tree.
		*/
		return (x);
	}

	/**
	 * This function delete_value takes in a value of type T and 
	 * removes the corresponding node from the red-black tree. 
	 * The function first uses lookup_value to search for the node with 
	 * the given value. If the node is found, delete_node is called to r
	 * emove it from the tree. If the node is not found, the function returns 0.
	 *  The function returns 1 if the node was successfully deleted.
	*/
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

	/**This function swaps the contents of the source Rbtree 
	 * object src with the contents of the current Rbtree object. 
	 * The three data members _root, _alloc, and _comp are swapped 
	 * using the std::swap function. The std::swap function swaps 
	 * the contents of two objects in an efficient and exception-safe way. 
	 * This is useful for when you want to exchange the contents of two 
	 * containers without having to copy the contents of one container 
	 * to a temporary location and then copy it back.*/
	void swap(Rbtree &src)
	{
		std::swap(this->_root, src._root);
		std::swap(this->_alloc, src._alloc);
		std::swap(this->_comp, src._comp);
	}

	/**the "clear" function of a data structure. 
	 * It is used to remove all elements stored in the data structure. 
	 * It calls the "destroy_nodes" function to delete all nodes in the structure, 
	 * starting from the root node. Then, it sets the root node to "NULL".*/
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

	/**
	 * Implements a left rotation in a Red-Black tree. A left rotation in a 
	 * binary tree involves rotating the nodes in such a way that the right 
	 * child of the given node "n" becomes the new root of the subtree and 
	 * the original root becomes the left child of the new root.
	 * This rotation is used to balance the tree and ensure that the properties 
	 * of a Red-Black tree are preserved.
	*/
	void rotate_left(node_type *n)
	{
		/*"right" is a pointer to the right child of the node "n"
		/The operation starts by updating the right child of "n" to be the left child of "right"*/
		node_type *right = n->right;
		n->right = right->left;
		//updates the parent of the previous right child of n, if it exists
		if (n->right)
			n->right->parent = n;
		//Then, the parent of "right" is updated to be the parent of "n"
		right->parent = n->parent;
		//Check if n was the root of the tree. If it was, then right becomes the root of the tree
		if (n->parent == NULL)
			this->_root = right;
		/**If n was not the root, the following code checks if n was the left child or the right 
		 * child of its parent. Based on that, it updates the appropriate child of the parent 
		 * of n to be right	*/
		else if (n->parent->left == n)
			n->parent->left = right;
		else
			n->parent->right = right;
		//the parent of "n" is updated to be "right"
		n->parent = right;
		//the left child of "right" is updated to be "n"
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

	/**
	 * used to perform a right rotation operation on a node in a Red-Black tree. 
	 * The idea behind a rotation is to change the structure of the tree in order 
	 * to maintain the balance and the Red-Black tree properties.
	*/
	void rotate_right(node_type *n)
	{
		//The left child of the node n is stored in the variable left
		node_type *left = n->left;
		//The left child of n is updated to be the right child of left
		n->left = left->right;
		//If n->left is not NULL, its parent is updated to be n
		if (n->left)
			n->left->parent = n;
		//The parent of left is updated to be the parent of n
		left->parent = n->parent;
		//If n is the root node, then the root of the tree is updated to be left
		if (n->parent == NULL)
			this->_root = left;
		// If n is the left child of its parent, then the left child of the parent is updated to be left
		else if (n->parent->left == n)
			n->parent->left = left;
		else
		//If n is the right child of its parent, then the right child of the parent is updated to be left
			n->parent->right = left;
		//The parent of n is updated to be left
		n->parent = left;
		//The right child of left is updated to be n
		left->right = n;
	}

	/**
	 * Implementation of the insertion operation for a binary search tree (BST). 
	 * The function takes two arguments: root and value. The root argument is the root of the BST, 
	 * and value is the node to be inserted into the BST.
	 * The function starts by checking if the root is NULL. If it is, returns value as the new root of the BST. 
	 * If root is not NULL, checks if it is a null leaf node (using the is_null_leaf function). 
	 * If it is, the function destroys the node and returns value as the new root of the BST.
	 * Next, compares the data stored in value with the data stored in root using the comparison function 
	 * specified in the constructor of the Rbtree class. 
	 * If the data stored in value is less than the data stored in root, inserts value as the left child of root 
	 * by calling insert_BST recursively on the left subtree of root. 
	 * If the data stored in value is greater than the data stored in root, inserts value as the right child of root 
	 * by calling insert_BST recursively on the right subtree of root. 
	 * Finally, the function returns root to maintain the structure of the BST.
	*/
	node_type *insert_BST(node_type *root, node_type *value)
	{
		//if there is no root
		if (!root)
			return (value);
		if (is_null_leaf(root))
		{
			destroy_node(root);
			return (value);
		}
		//if value is less than root insert at root left
		if (this->_comp(*value->data, *root->data))
		{
			root->left = insert_BST(root->left, value);
			root->left->parent = root;
		}
		//if value is greater than root insert at root right
		else if (this->_comp(*root->data, *value->data))
		{
			root->right = insert_BST(root->right, value);
			root->right->parent = root;
		}
		return (root);
	}

	/**
	 * Function to fix an RBT (Red-Black Tree) after inserting a node in order 
	 * to maintain its red-black properties. The red-black tree is a type of 
	 * binary search tree that is balanced, meaning that its height is logarithmic 
	 * in the number of nodes. This is achieved by color coding the nodes in the tree: black and red. 
	 * There are specific rules that must be maintained for a red-black tree to remain balanced, 
	 * and this function enforces these rules after an insertion has been made. 
	 * The function takes a newly inserted node as input and adjusts the properties of the Red-Black 
	 * tree to maintain balance and ensure that the tree still satisfies the properties of a Red-Black tree. T
	 * he function does this by checking for any possible violations of the Red-Black tree properties and
	 * fixing them by rotating nodes and changing the color of some nodes. The function continues to do this
	 * until there are no more violations and the Red-Black tree remains balanced.
	 * 
	 * Takes in a pointer to a node in a Red-Black Tree and modifies the tree to ensure that it still 
	 * satisfies the Red-Black Tree properties after the insertion of the new node.
	*/
	void fix_insert_RBT(node_type *node)
	{
		/**
		 * The function starts by checking the color of the parent node of the newly inserted node. 
		 * If the parent node is red, then we check the color of the uncle node (the sibling of the parent node). 
		 * There are three cases:
		 * 	Case 1: If the uncle node is red, then we change the color of the uncle node to black, 
		 * 		the color of the parent node to black, and the color of the grandparent node to red. 
		 * 		Then, we set the newly inserted node to be the grandparent node and repeat the same process.
		 * 	Case 2: If the uncle node is black, and the newly inserted node is a left child of its parent, 
		 * 		then we rotate the parent node to the right.
		 * 	Case 3: If the uncle node is black, and the newly inserted node is a right child of its parent, 
		 * 		then we rotate the grandparent node to the left and change the color of the parent node 
		 * 		to black and the color of the grandparent node to red.
		 * 	Finally, the function sets the color of the root node to black.
		*/
		//declares a pointer to a node type and initializes it to NULL
		node_type *uncle = NULL;
		/* starts a while loop that will continue to execute as long as node 
		/is not the root of the tree and the color of node->parent is red.*/
		while (node != this->_root && get_color(node->parent) == RED)
		{
			/*checks if the parent of node is the right child of its grandparent.*/
			if (node->parent == node->parent->parent->right)
			{
				/**If the parent of node is the right child of its grandparent, 
				 * sets uncle to be the left child of the grandparent.*/
				uncle = node->parent->parent->left;
				//checks if the color of uncle is red
				if (get_color(uncle) == RED)
				{
					//std::cout << "Case 1a\n";
					/**If the color of uncle is red, sets the color of uncle to black*/
					set_color(uncle, BLACK);
					/*If the color of uncle is red, sets the color of the parent of node to black.*/
					set_color(node->parent, BLACK);
					/* and sets the color of the grandparent of node to red*/
					set_color(node->parent->parent, RED);
					/**and sets node to be the grandparent of node*/
					node = node->parent->parent;
				}
				else /*If the color of uncle is not red, the code inside the else statement will be executed.*/
				{
					// checks if node is the left child of node->parent
					if (node == node->parent->left)
					{
						//std::cout << "Case 2a\n";
						//If node is the left child of its parent, sets node to be its parent
						node = node->parent;
						//performs a right rotation on node
						rotate_right(node);
					}
					//std::cout << "Case 3a\n";
					//sets the color of the parent of node to black
					set_color(node->parent, BLACK);
					//sets the color of the grandparent of node to red
					set_color(node->parent->parent, RED);
					//performs a left rotation on the grandparent of node
					rotate_left(node->parent->parent);
				}
			}
			else/*else the parent of node is the not right child of its grandparent.*/
			{
				/** assigns uncle to the right sibling of the node's parent*/
				uncle = node->parent->parent->right;
				/*checks if the color of uncle is red*/
				if (get_color(uncle) == RED)
				{
					//std::cout << "Case 1b\n";
					/** if it is, the code changes the color of uncle to black, 
					 * the color of node's parent to black, and the color of node's 
					 * grandparent to red. Then, node is updated to be the grandparent.*/
					set_color(uncle, BLACK);
					set_color(node->parent, BLACK);
					set_color(node->parent->parent, RED);
					node = node->parent->parent;
				}
				else/*If uncle is not red*/
				{
					/*the next step is checking if the node is on the right of its parent*/
					if (node == node->parent->right)
					{
						//std::cout << "Case 2b\n";
						/*If it is, the code performs a left rotation on the node's parent, 
						effectively moving the node to be its parent's left child*/
						node = node->parent;
						rotate_left(node);
					}
					// std::cout << "Case 3b\n";
					/* changes the color of the node's parent to black,
					 and the color of the node's grandparent to red.*/
					set_color(node->parent, BLACK);
					set_color(node->parent->parent, RED);
					//performs a right rotation on the node's grandparent
					rotate_right(node->parent->parent);
				}
			}
		}
		// std::cout << "Case 0\n" if is root;
		//Sets the color of the root of the tree to black
		set_color(this->_root, BLACK);
		return;
	}

	/**
	 * helper function that is used to determine the color of a node in a Red-Black Tree. 
	 * If the node is NULL, it returns BLACK. 
	 * If the node is not NULL, it returns the color attribute of the node. 
	 * The color attribute of a node is either RED or BLACK. 
	 * This function is used to check the color of the nodes in the tree, 
	 * which is an important property of Red-Black Trees
	*/
	int get_color(node_type *node)
	{
		if (node == NULL)
			return BLACK;
		return (node->color);
	}

	/**Sets the color of a node in the red-black tree. 
	 * The function takes two arguments: a pointer to the node (node) and the color to set (color).
	 * Starts by checking if the node pointer is NULL. If it is, the function returns without doing anything.
	 * If the node pointer is not NULL, the function sets the color member of the node to the value of the color argument. 
	 * This updates the color of the node in the red-black tree.*/
	void set_color(node_type *node, int color)
	{
		if (node == NULL)
			return;
		node->color = color;
	}

	/**transplant is a helper function that replaces one node in a tree with another node. 
	 * The purpose of this function is to simplify the implementation of tree operations like delete and insert.
	 * The function takes two parameters: u and v. 
	 * u is the node that is being replaced, and v is the node that is being inserted in its place.*/
	void transplant(node_type *u, node_type *v)
	{
		/*The function starts by checking if u has a parent. 
		If u is the root of the tree, the root is updated to v.*/
		if (!u->parent)
			this->_root = v;
		/*If u has a parent, the function checks if u is the left or right child of its parent.*/
		else if (u == u->parent->left)
		/* If u is the left child, the parent's left pointer is updated to v*/
			u->parent->left = v;
		else
		/*If u is the right child, the parent's right pointer is updated to v*/
			u->parent->right = v;
		/*Finally, if v is not NULL, the parent of v is updated to u's parent*/
		if (v)
			v->parent = u->parent;
	}

	/**
	 * Used to restore the red-black tree properties after a node is deleted. 
	 * It takes a single argument node, which is a pointer to the node that was deleted.
	*/
	void fix_delete_RBT(node_type *node)
	{
		node_type *sibling;
		/*The function starts a loop and checks if the node is the root of the tree and its color is black. 
		If these conditions are true, the loop continues, otherwise, it terminates.*/
		while (node != this->_root && get_color(node) == BLACK)
		{
			/*The loop first checks if the node is a left child
			Based on that, it sets the sibling node to the other child of the parent node.*/
			if (node == node->parent->left)
			{
				sibling = node->parent->right;
				/*If the sibling node's color is red, the function performs 
				a color flip and a rotation to balance the tree.*/
				if (get_color(sibling) == RED)
				{
					//std::cout << "Case 1a\n";
					set_color(sibling, BLACK);
					set_color(node->parent, RED);
					rotate_left(node->parent);
					sibling = node->parent->right;
				}
				/*If the sibling node's color is black and both of its children are also black, 
				changes the color of the sibling node to red and sets the node to its parent.*/
				if (get_color(sibling->left) == BLACK &&
				    get_color(sibling->right) == BLACK)
				{
					//std::cout << "Case 2a\n";
					set_color(sibling, RED);
					node = node->parent;
				}
				else//or a right child of its parent
				{
					/**
					 * If the sibling is black, and one of its children is red, 
					 * the code performs the following actions:
					 * 		Changes the color of the red child to black
					 * 		Changes the color of the sibling to red
					 * 		Performs a right rotation on the sibling node 
					 * 		Updates the sibling reference to the new sibling
					*/
					if (get_color(sibling->right) == BLACK)
					{
						//std::cout << "Case 3a\n";
						set_color(sibling->left, BLACK);
						set_color(sibling, RED);
						rotate_right(sibling);
						sibling = node->parent->right;
					}
					/**If the sibling is black, and one of its children is red, 
					 * the code performs the following actions:
					 * 		Changes the color of the sibling to the color of the parent node
					 * 		Changes the color of the parent node to black
					 * 		Changes the color of the red child of the sibling to black
					 * 		Performs a left rotation on the parent node.*/
					//std::cout << "Case 4a\n";
					set_color(sibling, get_color(node->parent));
					set_color(node->parent, BLACK);
					set_color(sibling->right, BLACK);
					rotate_left(node->parent);
					break;
				}
			}
			else
			{
				sibling = node->parent->left;
				/**
				 * If the sibling is red, the code performs the following actions:
				 * 		Changes the color of the sibling to black
				 * 		Changes the color of the parent node to red
				 * 		Performs a right rotation on the parent node
				 * 		Updates the sibling reference to the new sibling
				*/
				if (get_color(sibling) == RED)
				{
					//std::cout << "Case 1b\n";
					set_color(sibling, BLACK);
					set_color(node->parent, RED);
					rotate_right(node->parent);
					sibling = node->parent->left;
				}
				/**
				 * If the sibling is black, the code checks the colors of its children. 
				 * If both the left and right children of the sibling are black, 
				 * the code performs the following actions:
				 * 		Changes the color of the sibling to red
				 * 		Updates the node reference to the parent node
				*/
				if (get_color(sibling->right) == BLACK &&
				    get_color(sibling->left) == BLACK)
				{
					//std::cout << "Case 2b\n";
					set_color(sibling, RED);
					node = node->parent;
				}
				else
				{
					/**
					 * If the sibling is black, and one of its children is red, 
					 * the code performs the following actions:
					 * 		Changes the color of the red child to black
					 * 		Changes the color of the sibling to red
					 * 		Performs a left rotation on the sibling node 
					 * 		Updates the sibling reference to the new sibling
					*/
					if (get_color(sibling->left) == BLACK)
					{
						//std::cout << "Case 3b\n";
						set_color(sibling->right,
							  BLACK);
						set_color(sibling, RED);
						rotate_left(sibling);
						sibling = node->parent->left;
					}
					/**If the sibling is black, and one of its children is red, 
					 * the code performs the following actions:
					 * 		Changes the color of the sibling to the color of the parent node
					 * 		Changes the color of the parent node to black
					 * 		Changes the color of the red child of the sibling to black
					 * 		Performs a right rotation on the parent node.*/
					//std::cout << "Case 4b\n";
					set_color(sibling,
						  get_color(node->parent));
					set_color(node->parent, BLACK);
					set_color(sibling->left, BLACK);
					rotate_right(node->parent);
					break;
				}
			}
		}
		/*Finally, the function sets the color of the node to black and terminates the loop. 
		/ This is to ensure that the root of the tree remains black.*/
		//std::cout << "Case 5 - root\n";
		set_color(node, BLACK);
	}
	
	void delete_node(node_type *node)
	{
		if (!node)
			return;
		node_type *root = this->_root;
		node_type *temp = NULL;
		/**
		 * a while loop that is searching for the node in the Red-Black tree that holds the same data 
		 * as the node being passed to the function. 
		 * It starts by initializing the temp variable to NULL, and checks if root is not a null leaf and not NULL.
		 * The loop continues to iterate as long as temp is NULL and root is not a null leaf and not NULL. 
		 * In each iteration of the loop, it compares the data of the node being passed to the function 
		 * with the data of the root node. */
		while (temp == NULL && root != NULL && !is_null_leaf(root))
		{
			/*If they are equal, then it sets temp to the value of root*/
			if (*node->data == *root->data)
				temp = root;
			if (this->_comp(*node->data, *root->data))
			/*If the data of the node being passed to the function is less than the data of the root node, 
		 	* then root is set to the left child of root*/
				root = root->left;
			else
			/*If the data of the node being passed to the function is greater than the data of the root node, 
		 	* then root is set to the right child of root*/
				root = root->right;
		}
		/*checks if the node to be deleted (stored in "temp") is either a null pointer or a null leaf node. 
		/If either of these conditions is true, the function returns without doing anything.*/
		if (!temp || is_null_leaf(temp))
			return;

		node_type *aux;
		node_type *temp2 = temp;
		int temp_original_color = temp2->color;
		/*determines the type of node that "temp" is. 
		/If "temp" has no children or only a right child, 
		/it sets "aux" to "temp->right", 
		/destroys the left child (if there is one), 
		/and performs a transplant operation to replace "temp" with its right child.*/
		if (is_null_leaf(temp->left))// no children or only right
		{
			aux = temp->right;
			destroy_node(temp->left);
			transplant(temp, temp->right);
		}
		/*If "temp" only has a left child, it sets "aux" to "temp->left", 
		/destroys the right child, 
		/and performs a transplant operation to replace "temp" with its left child.*/
		else if (is_null_leaf(temp->right))// only left child
		{
			aux = temp->left;
			destroy_node(temp->right);
			transplant(temp, temp->left);
		}
		/**
		 * If the node to be deleted has both children:
		 * The function finds the minimum value node in the right subtree (temp2).
		 * The function swaps the values of the deleted node and the minimum value node.
		 * The minimum value node becomes the new root of the subtree, replacing the deleted node.
		 * The minimum value node's right child becomes the right child of the subtree.
		 * The minimum value node's left child is destroyed, since it is a null leaf.
		*/
		else// both children
		{
			temp2 = minValueNode(temp->right);
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
		/**
		 * checks if the color of the node that was deleted was black. 
		 * If so, it performs a fix-up operation to restore the red-black tree properties (fix_delete_RBT). 
		 * This operation ensures that the number of black nodes from the root to the leaves remains the same for every path, 
		 * which is one of the properties of a red-black tree.
		*/
		destroy_node(temp);
		if (temp_original_color == BLACK)
			fix_delete_RBT(aux);
	}

	/**
	 * a recursive function that is used to delete all nodes of a Red-Black tree. 
	 * The function takes a pointer to the root node of the tree as an argument.
	 * The function works as follows:
	 * If the current node is a null leaf, the function returns immediately.
	 * Recursively call the destroy_nodes function on the left child of the current node.
	 * Recursively call the destroy_nodes function on the right child of the current node.
	 * Call the destroy_node function on the current node.
	 * This way, the function will traverse the tree in post-order and delete all nodes, 
	 * starting from the leaves and working its way up to the root node.
	*/
	void destroy_nodes(node_type *node)
	{
		if (!node)
			return;
		destroy_nodes(node->left);
		destroy_nodes(node->right);
		destroy_node(node);
	}

	/**
	 * The function takes a pointer to a node_type as input and deallocates the memory associated with that node.
	 * The first thing it does is check if the input node is NULL. If it is, the function simply returns without doing anything.
	 * Then, it checks if the data member of the node is not NULL. If it is not, the function calls the destroy function 
	 * of the associated allocator on the data member, which frees the memory associated with the data stored in the node. 
	 * Then, the deallocate function of the allocator is called on the data member to deallocate the memory of the data member itself.
	 * Finally, the destroy and deallocate functions of the _node_alloc member are called on the input node, 
	 * deallocating the memory associated with the node structure.
	*/
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

	/**
	 * Finds the in-order successor of a node in a binary search tree. 
	 * The function first checks if the node is NULL or if its parent is NULL, in which case it returns NULL.
	 * Then, it checks if the node is its parent's left child. If it is, the parent is the in-order successor.
	 * Otherwise, the function recursively calls itself on the node's parent to find the in-order successor. 
	 * The in-order successor of a node in a binary search tree is the node that comes 
	 * immediately after the node in a in-order traversal of the tree.
	*/
	static node_type *find_successor(node_type *node)
	{
		if (!node || !node->parent)
			return (NULL);
		if (node->parent->left == node)
			return (node->parent);
		return (find_successor(node->parent));
	}

	/**
	 * Used to find the node that precedes a given node in the tree, based on the ordering of the nodes' data. 
	 * If the given node has a left child, then the predecessor of the node is the maximum node in the left subtree of the node. 
	 * If the node does not have a left child, then the predecessor is the first ancestor of the node for which the node 
	 * is in the right subtree of that ancestor. If the given node is NULL or its parent is NULL, the function returns NULL.
	 * This function works by using recursion to traverse the tree up to the root. 
	 * At each step of the recursion, the function checks whether the given node is the right child of its parent. 
	 * If it is, then the parent node is returned as the predecessor. 
	 * If it is not, then the function is called again with the parent node as the input, continuing the upward traversal.
	*/
	static node_type *find_predecessor(node_type *node)
	{
		if (!node || !node->parent)
			return (NULL);
		if (node->parent->right == node)
			return (node->parent);
		return (find_predecessor(node->parent));
	}

	/**
	 * This function is called copy_nodes and is used to copy the nodes of a tree to another tree. 
	 * It takes in a const pointer to a node of the tree to be copied as an argument. 
	 * The function first checks if the node pointer is NULL or if it's a null leaf, and in either case returns without doing anything.
	 * Otherwise, the function recursively copies the nodes in the left subtree of the node, 
	 * then inserts the value stored in the current node into the target tree using the insert_value function. 
	 * Finally, the function recursively copies the nodes in the right subtree of the node.
	*/
	void copy_nodes(const node_type *node)
	{
		if (!node || is_null_leaf(node))
			return;
		copy_nodes(node->left);
		insert_value(*node->data);
		copy_nodes(node->right);
	}
	// =================================================================================
	//						DEBUG AND PRINT FUNCTIONS
	// =================================================================================
		/**The function printBT is used to print the binary tree in a visually appealing way. 
		 * It takes three arguments:
		 * prefix: a string used to add indentation to the output, representing the structure of the tree.
		 * node: a pointer to the node that is being printed.
		 * isRight: a boolean indicating whether the node is a right child or not.
		 * The function first checks if node is a valid pointer. 
		 * If it is, it prints the value of the node and its color (represented as CEND or CRED). 
		 * Then, it prints the left and right children of the node by calling printBT recursively with an updated prefix. 
		 * If node is not a valid pointer, the function returns immediately.*/
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

		/**Printing a tree in a nice format. 
		 * print the binary tree of a Red-Black tree data structure. 
		 * The function first prints "---" to indicate the start of the tree. 
		 * Then, it calls another helper function, also named printBT(), with the root node of the tree, 
		 * and a Boolean value indicating if the node is a right child or not.
		 * The helper function takes a string prefix, the current node, and the Boolean value as inputs.
		 * If the current node is not null, the function first prints the value of the node 
		 * (in red if the node is a red node, and in black otherwise). 
		 * The function then enters the next level of the tree by calling itself recursively 
		 * on the left and right children of the current node. The prefix string is updated to 
		 * properly format the tree visualization with branches and spaces.
		 * Finally, after the tree has been printed, the original function prints "---" to indicate the end of the tree.*/
		void printBT(){
			std::cout << "---" << std::endl;
			printBT("", this->get_root(), false);
			std::cout << "---" << std::endl;
		}

	};
} 
#endif
