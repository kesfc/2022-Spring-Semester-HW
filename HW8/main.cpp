/*
A Node class is required (see the provided one in Rope.h), must have
  weight, value, left, and right members.
  You can add other members.
The Rope class must have a constructor that takes a Node*
  and uses that Node* as a root.
The Rope class must also have a function, expose_root() to return a pointer to the root 
Node.
(This is poor class design, but will be necessary for us to autograde your data structure
.)
*/

#include <cassert>
#include <string>
#include "Rope.h"

void StudentTests();
bool SAME(const Rope &r, const std::string &s);
bool ValidRope(Node *root);
int countWeights(Node *root);
void BasicTests();
Node *IndexTestRope();
Node *ConcatTestRopeLeft();
Node *ConcatTestRopeRight();
Node *student_node();
Node *student_node2();

int main()
{
	BasicTests();
	std::cout << "***Basic tests passed." << std::endl;
	StudentTests();
	std::cout << "***Student tests passed." << std::endl;
	return 0;
}

void StudentTests()
{
	/* ADD YOUR TESTS HERE
	 * MAKE SURE TO TEST FUNCTIONS THOROUGHLY
	 * CONSIDER CORNER CASES, ETC.
	 * THESE TESTS SHOULD NOT CAUSE A CRASH.
	 */
	Rope r1(student_node());
	r1.print(std::cout);
	r1.print_strings(std::cout);
	std::string s1="it always seems impossible until its done.";
	assert(SAME(r1, s1));
	std::cout << "***Index test passed." << std::endl;
	std::string s2;
	assert(r1.report(0, s1.length() - 1, s2) && s2 == s1);
	std::cout << "***Basic report test passed." << std::endl;
	s2="--Nelson Mandela";
	std::string s3=s1+s2;
	Rope r2(student_node2());
	r1.concat(r2);
	assert(SAME(r1, s3));
	r1.print(std::cout);
	Rope r4(student_node());
	std::string s4="it always seems impossible until its done.--Nelson Mandela";
	std::string s5=s4.substr(0,21);
	std::string s6=s4.substr(21,21);
	Rope r5;
	r4.split(21,r5);
	assert(SAME(r4, s5));
	assert(SAME(r5, s6));
	std::cout << "***Split test passed" << std::endl;
	Rope r6(r4);
	std::string rs2;
	assert(r6.expose_root() != r4.expose_root());
	assert(r6.size() == r4.size());
	assert(r6.report(0, r6.size() - 1, s1) && r4.report(0, r4.size() - 1, rs2) 
	&& s1 == rs2);
	std::cout << "***Copy test passed" << std::endl;
	Rope r7;
	r7 = r5;
	assert(r7.expose_root() != r5.expose_root());
	assert(r7.size() == r5.size());
	assert(r7.report(0, r7.size() - 1, s1) && r5.report(0, r5.size() - 1, rs2) 
	&& s1 == rs2);
	std::cout << "***Assignment test passed" << std::endl;
	std::cout << "Corner case test"<<std::endl;
	char a;
	assert(!r5.index(50,a));
	assert(!r1.report(45, 70, s1));
	Rope r10;
	r7.concat(r10);
	assert(r7.expose_root() != r5.expose_root());
	assert(r7.size() == r5.size());
	assert(r7.report(0, r7.size() - 1, s1) && r5.report(0, r5.size() - 1, rs2) 
	&& s1 == rs2);
	r10.concat(r5);
	assert(r7.expose_root() != r10.expose_root());
	assert(r7.size() == r10.size());
	assert(r7.report(0, r7.size() - 1, s1) && r10.report(0, r10.size() - 1, rs2) 
	&& s1 == rs2);
	std::cout<<"Corner case passed"<<std::endl;

}
Node *student_node2(){
	Node* head=new Node;
	head->weight=2;
	head->left=new Node;
	head->left->parent=head;
	head->left->value="--";
	head->left->weight=2;
	head->right=new Node;
	head->right->parent=head;
	head->right->weight=7;
	head->right->left=new Node;
	head->right->left->parent=head->right;
	head->right->left->weight=7;
	head->right->left->value="Nelson ";
	head->right->right=new Node;
	head->right->right->parent=head->right;
	head->right->right->weight=7;
	head->right->right->value="Mandela";
	return head;
}

Node *student_node()
{
	Node *r = new Node;
	r->weight = 27;
	r->left = new Node;
	r->left->parent = r;
	r->left->weight = 3;
	r->left->left = new Node;
	r->left->left->parent = r->left;
	r->left->left->weight = 3;
	r->left->left->left = new Node;
	r->left->left->left->parent = r->left->left;
	r->left->left->left->weight = 3;
	r->left->left->left->value = "it ";
	r->left->right = new Node;
	r->left->right->parent=r->left;
	r->left->right->weight=7;
	r->left->right->left=new Node;
	r->left->right->left->parent=r->left->right;
	r->left->right->left->weight=7;
	r->left->right->left->value="always ";
	r->left->right->right=new Node;
	r->left->right->right->parent= r->left->right;
	r->left->right->right->weight=6;
	r->left->right->right->left=new Node;
	r->left->right->right->left->parent=r->left->right->right;
	r->left->right->right->left->weight=6;
	r->left->right->right->left->value="seems ";
	r->left->right->right->right=new Node;
	r->left->right->right->right->parent=r->left->right->right;
	r->left->right->right->right->weight=11;
	r->left->right->right->right->value="impossible ";
	r->right=new Node;
	r->right->parent=r;
	r->right->weight=15;
	r->right->left=new Node;
	r->right->left->parent=r->right;
	r->right->left->weight=6;
	r->right->left->left=new Node;
	r->right->left->left->parent=r->right->left;
	r->right->left->left->weight=6;
	r->right->left->left->value="until ";
	r->right->left->right=new Node;
	r->right->left->right->parent=r->right->left;
	r->right->left->right->weight=4;
	r->right->left->right->left=new Node;
	r->right->left->right->left->parent=r->right->left->right;
	r->right->left->right->left->weight=4;
	r->right->left->right->left->value="its ";
	r->right->left->right->right=new Node;
	r->right->left->right->right->parent=r->right->left->right;
	r->right->left->right->right->weight=5;
	r->right->left->right->right->left=new Node;
	r->right->left->right->right->left->parent=r->right->left->right->right;
	r->right->left->right->right->left->weight=5;
	r->right->left->right->right->left->value="done.";
	Node* head=new Node;
	head->left=r;
	r->parent=head;
	head->weight=42;
	return head;
}
// Used to compare a string and a rope that should be the same.
// You can uncomment the .report assert to test report on the whole string
bool SAME(const Rope &r, const std::string &s)
{
	/*std::cout << "Comparing string \"" << s << "\" to Rope:" << std::endl;
	r.print(std::cout);*/
	assert(r.size() == (int)s.length() && "ERROR: ROPE SIZE DOES NOT MATCH STRING SIZE");
	char c;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		assert(r.index(i, c) && c == s[i] && 
		"MISMATCH BETWEEN A CHARACTER IN ROPE AND STRING USING INDEX");
	}
	/*
	std::string s2;
	assert(r.report(0,s.length()-1,s2) && s2 == s &&
	 "MISMATCH BETWEEN ROPE.REPORT(0,length-1) AND STRING");
	*/
	return true;
}

// Function to check that the weights and structure from a root form a valid Rope.
bool ValidRope(Node *root)
{
	int left_sub = 0;

	if (!root)
	{
		return true;
	}

	// Check that weight is correct as a leafe
	if (!root->left && !root->right)
	{
		return root->weight == (int)root->value.length();
	}

	// Check that I'm at least one of the children of my parent.
	if (root->parent && (root->parent->left != root) && (root->parent->right != root))
	{
		return false;
	}

	// Check my weight if I'm not a leaf
	if (root->left)
	{
		/* ON SUBMITTY, THE INSTRUCTOR VERSION OF THE CODE
		 * IMPLEMENTS countWeights(). IF YOU ALSO WANT TO
		 * USE THIS CODE YOU WILL NEED TO IMPLEMENT countWeights().
		 * YOU MAY FIND USING assert() STATEMENTS OR PRINTING SPECIFIC
		 * ERRORS HELPFUL FOR DEBUGGING.
		 */
		left_sub = countWeights(root->left);
	}

	return (root->weight == left_sub) && ValidRope(root->left) && ValidRope(root->right);
}

int countWeights(Node *root)
{
	if(root==NULL){
		return 0;
	}
	else if(!is_leaf(root)){
		return countWeights(root->left)+countWeights(root->right);
	}
	else{
		return root->weight;
	}
}

void BasicTests()
{
	Rope r1(IndexTestRope());
	std::string s1 = "Hello my name is Simon";
	std::string rs1;
	r1.print(std::cout);
	r1.print_strings(std::cout);
	assert(SAME(r1, s1));
	std::cout << "***Index test passed." << std::endl;
	assert(r1.report(0, s1.length() - 1, rs1) && rs1 == s1);
	std::cout << "***Basic report test passed." << std::endl;

	// Concat test
	Rope r2(ConcatTestRopeLeft());
	Rope r3(ConcatTestRopeRight());
	std::string s2 = "Hello my ";
	std::string s3 = "name i";

	assert(SAME(r2, s2));
	assert(SAME(r3, s3));
	std::cout << "***More index tests passed." << std::endl;

	r2.concat(r3);
	s2 += s3;
	assert(SAME(r2, s2));
	std::cout << "***Concatenation test passed" << std::endl;

	// Split test
	Rope r4(IndexTestRope()); // Wikipedia split @ 11
	std::string s4 = "Hello my name is Simon";
	Rope r5;
	std::string s5 = s4.substr(0, 11);
	std::string s6 = s4.substr(11, 11);
	r4.split(11, r5);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	assert(SAME(r4, s5));
	assert(SAME(r5, s6));
	std::cout << "***Split test passed" << std::endl;

	// Copy & Assignment tests
	Rope r9(IndexTestRope());
	Rope r10(r9);
	std::string rs2;
	assert(r10.expose_root() != r9.expose_root());
	assert(r10.size() == r9.size());
	assert(r10.report(0, r10.size() - 1, rs1) && r9.report(0, r9.size() - 1, rs2) 
	&& rs1 == rs2);
	std::cout << "***Copy test passed" << std::endl;
	Rope r11;
	r11 = r9;
	assert(r11.expose_root() != r9.expose_root());
	assert(r11.size() == r9.size());
	assert(r11.report(0, r11.size() - 1, rs1) && r9.report(0, r9.size() - 1, rs2) 
	&& rs1 == rs2);
	std::cout << "***Assignment test passed" << std::endl;
}

// Also used for split() test
Node *IndexTestRope()
{
	Node *ret = new Node;
	ret->weight = 22;
	ret->left = new Node;
	ret->left->parent = ret;
	ret->left->weight = 9;
	ret->left->left = new Node;
	ret->left->left->parent = ret->left;
	ret->left->left->weight = 6;
	ret->left->right = new Node;
	ret->left->right->parent = ret->left;
	ret->left->right->weight = 6;
	ret->left->left->left = new Node;
	ret->left->left->left->parent = ret->left->left;
	ret->left->left->left->weight = 6;
	ret->left->left->left->value = "Hello ";
	ret->left->left->right = new Node;
	ret->left->left->right->parent = ret->left->left;
	ret->left->left->right->weight = 3;
	ret->left->left->right->value = "my ";
	ret->left->right->left = new Node;
	ret->left->right->left->parent = ret->left->right;
	ret->left->right->left->weight = 2;
	ret->left->right->right = new Node;
	ret->left->right->right->parent = ret->left->right;
	ret->left->right->right->weight = 1;
	ret->left->right->left->left = new Node;
	ret->left->right->left->right = new Node;
	ret->left->right->left->left->parent = ret->left->right->left;
	ret->left->right->left->left->weight = 2;
	ret->left->right->left->left->value = "na";
	ret->left->right->left->right->parent = ret->left->right->left;
	ret->left->right->left->right->weight = 4;
	ret->left->right->left->right->value = "me i";
	ret->left->right->right->left = new Node;
	ret->left->right->right->left->parent = ret->left->right->right;
	ret->left->right->right->left->weight = 1;
	ret->left->right->right->left->value = "s";
	ret->left->right->right->right = new Node;
	ret->left->right->right->right->parent = ret->left->right->right;
	ret->left->right->right->right->weight = 6;
	ret->left->right->right->right->value = " Simon";
	return ret;
}

Node *ConcatTestRopeLeft()
{
	Node *ret = new Node;
	ret->weight = 6;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 6;
	ret->left->value = "Hello ";
	ret->right->parent = ret;
	ret->right->weight = 3;
	ret->right->value = "my ";
	return ret;
}

Node *ConcatTestRopeRight()
{
	Node *ret = new Node;
	ret->weight = 2;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 2;
	ret->left->value = "na";
	ret->right->parent = ret;
	ret->right->weight = 4;
	ret->right->value = "me i";
	return ret;
}
