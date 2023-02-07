HOMEWORK 8: ROPES


NAME:  < Weihao Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Haoran Bao, Zhangcheng YU, Micheal Bei, Kenneth Dong >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
balanced: O(2^p)
unbalanced: O(2*p))
in a balanced tree, time take to find a leaf node is 2^p, because it is using both note
every time, and length to every leaf is teh same.
In a unbalanced tree, since it may not always taking two child each times, the big O
notation would also be varied depends on how it actually work. In my example, this 
unbalanced's leaf will only take 1 character each time, since the length of the string is
n, so it will have n leaf node, and start from root, the one to the left will be a leaf
node, and on the right will have a node which it's left is a leaf node as well and 
right will have anotehr node which left is a leaf node... In the giving string, it will 
have a node that have value H in the left of the root, e in root -> right -> left, l in
root -> right -> right ->left, another l in root -> right -> right -> right ->left...
so the time will be two times longest, because at every node, it left is a leaf, and right 
will continue the path to find the last char.

Construct from Node*:
balanced:: O(2^p)
unbalanced:: O(2*p))
in balance tree the time will be the same as copy constructor, because both of it need to 
recurse to the all leaf node, in copy constructor it need to copy the string, at there it
need to get the weight and add all togetehr to find the size of the rope.
assume the unbalanced tree has the same structure as mentioned previous, it will have the 
same runing time as copy constructor, the reason will be the same as the balanced tree.

Index:
O(p)
it would have pretty same running time for index, if the tree is balance it will always
have O(p) as running time, but for unbalanced tree it will be the O(length of the path to 
the index node), so O(p) will be the worst case.

Report:
let the length of the want to find = n(in function pass 2 int, n is difference of 2 int)
ps::I am not too sure what giving n meaning, hope it is the same as what I understand 
here.
O(p*n)
since report is just loop over from the first int be giving to the second int by using 
index, so the running time will just be difference between to int * index time.


iterator operator++:
balanced:: O(2p)
unbalanced:: O(3)
in a balanced tree the worst case is it need to went back from a leaf to the root and than
went down to another root agian.
assume the unbalanced is the same as the one I described ealier, it only need -> parent ->
right -> left to reach the next leaf.


Split:
Balenced:: O(2p+p*(2^p+1)+2^p)=O(2^2p+2^p+3p)
Unbalanced:: O(2p+2p+2*p+1)=O(6p+1)
assume the unbalanced tree is the same as the previoused mentioned, for both balance and 
unbalanced tree, it need first find the node that the int is index at, to see do I need 
to split that node to two. Then find the node that need to starting cutting(O(p)), on the
we of finding it I will have vector to store did it went left or right, and the vector's 
size should also be p. And loop over the vector, the worst case for balanced tree is when 
it is keep going left, so it need concat p time. The concat in split should just be O(2^p
+1) for balanced tree, because it doesn't need to copy. For my unbalanced tree, it will
always only need to concat onece O(2*p+1). At the end for both balance and unbalanced 
tree, it need to find all leaf node's weight to find the size of the rope(O(2^p) 
for balanced, O(2*p) for unbalanced).


Concat:
Balenced:: O(2^p*2+1)
Unbalanced:: O(4*p+1)
assume the unbalanced tree is the same as the previoused mentioned, the first thing we do 
in the concat is to copy the second rope's root(2^p for balance and 2*p for unbalanced),
then need to creat a new root and connect the new root with those to old root. last 
it need to count the weight of the left hand side weight(2^p for balance and 2*p for 
unbalanced).


graph example of the unbalancedtree.
root
/    \
h    node
    /  \
    e   node
        /   \
        l    node
            /   \
            l   node
                /   \
               o_    node
                    /    \
                    m    node
                        /    \
                       y_    node
                            /    \
                            n    node
                                /    \
                                a    node
                                    /   \
                                    m   node
                                        /   \ 
                                        e_   node
                                            /    \
                                            i    node
                                                /    \
                                               s_    node
                                                    /
                                                   Simon
                                                    
......

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
In my student test I first creat another two ropes and use this two to do all the test 
that did in the provided test. Then I wrote some corner case test, such as:: finding index 
is bigger than the size, report's second int greater than the size, and concat with an 
empty rope, those test actually helped find out I had missed some corner case in the 
function.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

