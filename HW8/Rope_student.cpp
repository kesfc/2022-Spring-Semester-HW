/*
Write your Rope implementation in this file.
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

// Should advance to the next Node using in-order traversal
// It can point at any Node, not just leaves
rope_iterator &rope_iterator::operator++()
{
	if (ptr_->right != NULL)
	{
		ptr_ = ptr_->right;
		while (ptr_->left != NULL)
		{
			ptr_ = ptr_->left;
		}
	}
	else
	{
		// TreeNode<T> *tmp = ptr_;
		//  Keep going up as long as I'm my parent's right child
		// while (tmp->value < value ) {
		while (ptr_->parent != NULL && ptr_->parent->right == ptr_)
		{
			ptr_ = ptr_->parent;
		}
		// Go up one more time
		ptr_ = ptr_->parent;
	}
	return *this;
}

// Point to the first Node for in-order traversal
rope_iterator Rope::begin() const
{
	if (root == NULL)
		return rope_iterator(NULL);
	Node *p = root;
	while (!is_leaf(p))
	{
		p = p->left;
	}
	return rope_iterator(p);
}

Rope::Rope()
{ // default constructor
	size_ = 0;
	root = NULL;
}

// Should make the root = p and adjust any member variables
// This should not make a copy of the rope with root at p,
// it should just "steal" the Node*
Rope::Rope(Node *p)
{
	Rope out;
	root = p;
	size_ = count_weight(p);
}

Rope::~Rope()
{
	this->destroy_node(root);
	root = NULL;
}

Rope::Rope(const Rope &r)
{
	size_ = r.size_;
	root = this->copy_node(r.root);
}

Rope &Rope::operator=(const Rope &r)
{
	if (&r != this)
	{
		size_ = r.size_;
		this->destroy_node(root);
		root = this->copy_node(r.root);
	}
	return *this;
}

// MUST BE ITERATIVE
// Get a single character at index i
bool Rope::index(int i, char &c) const
{
	if (this->size_ == 0)
	{
		return false; // if size==0 means there is nothing in the rope, just return false.
	}
	else if(this->size_<=i){
		return false;
	}
	Node *temp = this->root;
	while (!is_leaf(temp))
	{
		if (temp->weight > i)
		{
			temp = temp->left;
		}
		else
		{
			i -= temp->weight;
			temp = temp->right;
		}
	}
	int out = temp->weight;
	if (i < out) // it means the given index is greater tan the size.
	{
		c = (temp->value)[i];
		return true;
	}
	else
	{
		return false;
	}
}

// Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope &r)
{
	if (r.size_ == 0)
	{
		return;
	}
	else if(size_==0){
		size_=r.size_;
		root = this->copy_node(r.root);
		return;
	}
	int size = count_weight(this->root);
	// first using helper function to find the weight of the lhs rope;
	Node *temp = copy_node(r.root); // make a new node and copy
	Node *new_root = new Node;
	size_ += r.size_; // size need to + the rhs rope's size
	new_root->weight = size;
	// fixing the parent and left right pointer
	root->parent = new_root;
	new_root->left = this->root;
	temp->parent = new_root;
	new_root->right = temp;
	root = new_root; // set the root to new root.
}

// Get a substring from index i to index j.
// Includes both the characters at index i and at index j.
// String can be one character if i and j match
// Returns true if a string was returned, and false otherwise
// Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string &s) const
{
	s.clear();
	char out;
	if (i > j) // first make sure the second int is greater than the first one;
	{
		return false;
	}
	else if(i>=size_){
		return false;
	}
	else if(j>=size_){
		return false;
	}
	for (int k = i; k <= j; k++)
	{
		if (index(k, out)) // find the string by using index function
		{
			s += out;
		}
		else
		{
			return false;
		}
	}
	return true;
}

// The first i characters should stay in the current rope, while a new
// Rope (rhs) should contain the remaining size_-i characters.
// A valid split should always result in two ropes of non-zero length.
// If the split would not be valid, this rope should not be changed,
// and the rhs rope should be an empty rope.
// The return value should be this rope (the "left") part of the string
// This function should move the nodes to the rhs instead of making new copies.
Rope &Rope::split(int i, Rope &rhs)
{
	if (i >= size_)
	{
		return *this;
	}
	else if(i>=size_&&i<0){
		return *this;
	}
	int k = i; // make a copy of int, the int will be changed in helper function.
	this->need_split(k);
	// helper function will help to check if a node need to split to 2 in the rope, and
	// fix it.
	Node *temp = this->root;
	std::vector<bool> step; // this will use to recorde the did it go right or left.
	while (i != temp->weight)
	// since I already split the node, so the index should right at a node's first element
	// so loop to the place I need to cut.
	{
		if (i < temp->weight)
		{
			bool s = true;
			if (temp->right == NULL)
			{
				s = false;
			}
			temp = temp->left;
			step.push_back(s); // if went right push_back false
		}
		else
		{
			i -= temp->weight;
			temp = temp->right;
			step.push_back(false); // if went left push_back true
		}
	}
	Node *part1 = temp->right;
	rhs.root = part1;
	temp->right = NULL;
	for (int i = step.size() - 1; i >= 0; i--)
	// go in another loop, to back trace the parts need to cut, and concat with the rope
	// in the vector I store steps, if the value gives trues, it will go to the parent
	// node's right node and concat it with rope, else just go to the parent node.
	{
		temp = temp->parent;
		if (step[i])
		{
			Node *part2 = temp->right;
			rhs.concat_noC(part2);
			temp->right = NULL;
		}
		temp->weight = count_weight(temp->left);
	}
	// use helper function count to get the new sizes.
	size_ = count_weight(root);
	rhs.size_ = count_weight(rhs.root);
	return *this;
}

void Rope::concat_noC(Node *node)
// helper function of split function, it will concat anotehr node to the rope.
{
	int size = count_weight(this->root); // find the weight of the new root
	Node *new_root = new Node;
	new_root->weight = size;
	if (node == NULL) // if the giving node is emty;
	{
		new_root->left = this->root;
		this->root->parent = new_root;
		this->root = new_root;
		return;
	}
	size_ += count_weight(node); // adjust new root;
	root->parent = new_root;
	new_root->left = root;
	node->parent = new_root;
	new_root->right = node;
	root = new_root;
	new_root->parent = NULL;
}

Rope &Rope::need_split(int i) // helper funtion of split
{
	if (this->size_ == 0)
	{
		return *this;
	}
	Node *temp = this->root;
	while (!is_leaf(temp)) // loop over to find the node that the index is at
	{
		if (temp->weight > i)
		{
			temp = temp->left;
		}
		else
		{
			i -= temp->weight;
			temp = temp->right;
		}
	}
	if (i == 0)
	// if at this moment i =0, means it is at first element of a node, so don't do a pre
	// split.
	{
		return *this;
	}
	else // split it to two node.
	{
		int origin_weight = temp->weight;
		temp->weight = i;
		std::string cut = temp->value;
		temp->value = "";
		Node *new_left = new Node;
		Node *new_right = new Node;
		new_left->parent = temp;
		new_left->weight = i;
		new_left->value = cut.substr(0, i);
		new_right->parent = temp;
		new_right->weight = origin_weight - i;
		new_right->value = cut.substr(i, origin_weight - i);
		temp->left = new_left;
		temp->right = new_right;
		return *this;
	}
}

int Rope::count_weight(Node *node) const
{ // helper function to help count the weight or size.
	if (node == NULL)
	{
		return 0;
	}
	else if (!is_leaf(node))
	{
		return count_weight(node->left) + count_weight(node->right);
	}
	else
	{
		return node->weight;
	}
}
Node *Rope::copy_node(Node *old) const
{ // function that will return a copy of the old node.
	if (old == NULL)
	{
		return NULL;
	}
	else
	{
		Node *temp = new Node;
		temp->weight = old->weight;
		temp->value = old->value;
		temp->left = copy_node(old->left);
		temp->right = copy_node(old->right);
		if (temp->left != NULL)
		{
			temp->left->parent = temp;
		}
		if (temp->right != NULL)
		{
			temp->right->parent = temp;
		}
		return temp;
	}
}

void Rope::destroy_node(Node *node)
{ // delete a node on the heap.
	if (node == NULL)
	{
		return;
	}
	else
	{
		destroy_node(node->left);
		destroy_node(node->right);
		delete node;
	}
}