HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Weihao LI >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Haoran Bao, Chengyu Zhang, Kenneth Dong >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12h >



TESTING & DEBUGGING STRATEGY:
when I testing I first tried copy constructor and assignment because it didn't be used
in the simple test case, and then I did many pop, push, insert and erase to double check
those functions are correct. Last I tried the class with char object to see if it can be 
apply on things other than intergers.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 
n=size of the array in node
push_front:
if the head array is full: O(1), else O(n). 
In our code we need to consider to case in 
in push front: when the first node's array is full, than need to creat new node at begin;
and when the it is not full, then just push everything in the array 1 index back. In stl 
list and dslist we only need to care about case one, which just add a new node at front.
push_back: O(1)
push_back is pretty similar for all three, but in our code we still need consider two 
case: when the last is full, then creat a new node; if not add one on the num_element-1;
for dslist and stl list it will just add a new node at back.
pop_front:
if the head array size is 0: O(1), else O(n)
in our code we need consider two case in pop_front, first is when the first node's array 
1, then just delete the first Node, and adjust head. Second is when the size is not one, 
then pushing everything other the last 1 one index forward and +1 num_element. For dslit 
and stl list, pop_front will just make it delete its first Node and adjust the head. 
pop_back: O(1)
pop_back is is pretty much the same as pop_front, in our code we need to consider two
situation but only one in stl list and dslist;
insert: O(n-offset)
for insert, our code need to cosider two situation, first is when the iterator's node's 
array is full, then it will split array, and adjust the pointers(head and tail if it 
is and head and tail; also the prev and next). Second is the size is not full, then it 
pushing everything at or after the iterator's offset 1 indext back. Stl list and dlist 
will just add a new thing at it index, dslist need to adjust pointers as well, stl list 
don't need.
erase: O(n-offset)
erase is similar to the insert, instead of add something between elements, at will just 
take out a element or delete a node.
Copy 
the speed of copy is the O(size of the class);
for stl list it will set a new list and just copy all value, for dslist it need copy the
value with it next and prev pointer and need to change head and tail. for our code, we 
also use next and prev pointet to copy our code and need change head and tail, different 
with dslist, it need loop over to copy value in the array;
destroy
speed O(number of node)
for destroy, all 3 are pretty similar. for stl list it will delet with index. for 
dslist and our code, it will delete every noce with next pointer(or prev).

wort case for memory usage:
assume every node's array only have one element, usage will be O(9*size)(6 for array, 1 
for num_element, and 2 for two pointer)

inefficient case:
when use insert it may cause a node split to two, and may be some pop cuase some node only
have one element, after few inset it may cause many different node that are not full, 
but can be fit together and take less memory space. At this case, average number of 
element will be 4-6;






EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


