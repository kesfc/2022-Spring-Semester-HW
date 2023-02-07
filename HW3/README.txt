HOMEWORK 3: CONNECT FOUR


NAME:  < Weihao Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Kenneth Dong, Haoran Bao, Zhengyu Zhang / 
https://docs.microsoft.com/en-us/cpp/cpp/destructors-cpp?view=msvc-170 >

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20h >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
if the giving column number is bigger than it stored: O(3n+n*m), else O(n)

insert (including checking for connected four)
if the giving column number is bigger than it stored: O(4n+2(n*m)), else O(n+n*m)

numTokensInColum
O(1)

numTokensInRow
O(n)

numColumns
O(1)

numRows
O(1)

print
O(m*n)

clear
O(3n)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used gdb and valgrind to debug my program, gdb I main used to track the number that 
being use as index in the array and have a segmentation fault while it run. Valgrind I 
mainly use to track if I delete variebles on the heap correctly, I also use it to check
if there are something can't be access.
In student stest case I tried normal insert and return same as simple test case, 
I also tried clear, copy.
for "corner case" I tried place a token at column 1000 to see if my code can successfully
extand the borad very long.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

