HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Weihao Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Haoran Bao, Chengyu Zhang, Rollin Chen >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

-----------------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f    |  longest  substr  |
|          | sort     | dups     | mode     | pair     | sorted     |                   | 
-----------------------------------------------------------------------------------------
|          |          |          |          |          |            |                   |
| vector   |O(nlog(n))|  O(n^2)  |O(nlog(n))|O(nlog(n))|O(nlog(n))  |     O(l^2*n^2)    |
-----------------------------------------------------------------------------------------
|          |          |          |          |          |            |                   |
| list     |O(nlog(n))|  O(n^2)  |O(nlog(n))|O(nlog(n))|O(nlog(n))  |     O(l^2*n^2)    |
-----------------------------------------------------------------------------------------
|          |          |          |          |          |            |                   |
| bst      |O(nlog(n))|O(nlog(n))|O(nlog(n))|O(nlog(n))|O(nlog(n))  |O(n*l^2*log(n*l^2))|
-----------------------------------------------------------------------------------------
|          |          |          |          |          |            |                   |
| pq       |O(nlog(n))|     X    |O(nlog(n))|O(nlog(n))|O(n+flog(n))|         X         |
-----------------------------------------------------------------------------------------
|          |          |          |          |          |            |                   |
| hash     |    X     |   O(n)   |   O(n)   |     X    |      X     |       other       |
-----------------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

I am using data from submitty to calculate the coefficients, which for every different
data type tested 4 time in each different function with different numbers. 
For sort it used 10000 length 5 strings, 50000 length 5 strings, 100000 length 5 strings, 
and 500000 length 5 strings as input to measure time. 
For remove duplicates, it used 5000 length 3,10000 length 3 strings, 20000 length 3 
strings, and 50000 length 3 strings as input to measure time
For mode it used 10000 length 4 strings, 50000 length 4 strings, 100000 length 4 strings, 
and 500000 length 4 strings as input to measure time.
For closest pair it used 10000 8 digit integers, 50000 8 digit integers, 100000 8 digit 
integers, and 500000 8 digit integers as input to measure time.
For first f sorted it used 100000 length 4 strings, 200000 length 4 strings, 500000 length
4 strings,  and 1000000 length 4 strings as input to measure time.
For longets string it used 500 length 20 strings, 1000 length 20 strings, 2000 length 20 
strings, and 3000 length 20 strings as input to measure time

coefficient estimates:
---------------------------------------------------------------------------------------
|       |            | remove     |            | closest    | first f    |  longest   |
|       | sort       | dups       | mode       | pair       | sorted     |  substr    | 
---------------------------------------------------------------------------------------
|       |            |            |            |            |            |            |
|vector |K=6.7*10^-8 |K=7.3*10^-9 |K=6.7*10^-8 |K=5.25*10^-8|K=1.1*10^-8 |K=3.35*10^-9|
---------------------------------------------------------------------------------------
|       |            |            |            |            |            |            |
|list   |K=9*10^8    |K=1.3*1-^-8 |K=9.7*10^-8 |K=8.5*10^-8 |K=1.9*10^-8 |K=5.1*10^-9 |
---------------------------------------------------------------------------------------
|       |            |            |            |            |            |            |
|bst    |K=2.1*10^-7 |K=1.8*10^-5 |K=2*10^-7   |K=1.3*10^-7 |K=4.8*10^-8 |K=3.65*10^-7|
---------------------------------------------------------------------------------------
|       |            |            |            |            |            |            |
|pq     |K=1*10^-7   |      X     |K=9.4*10^-8 |K=8.45*10^-8|K=1.4*10^-7 |      X     |
---------------------------------------------------------------------------------------
|       |            |            |            |            |            |            |
|hash   |      X     |K=4.35*10^-7|K=2.4*10^-6 |     X      |      X     |K=2.5*10^-7 |
---------------------------------------------------------------------------------------



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  

I think the measurements mostly matched my prediction base on my Big ‘O‘ Notation, so I 
didn't change my Big ‘O‘ Notation. Something surprised me from the measurement is that the
 hash table(set and map) had the shortest time in finding the longest string since I 
thought there running time will be pretty much the same as the rest of container, 
also even vector and linked list have the exactly same Big ‘O‘ Notation running time and 
very similar structure for all functions, but vector is running faster in all functions 
compare with linked list.
The coefficients mostly matched what I expect, and it also proved showed that linked list 
have higher coefficients compare with vector in all functions, it kind of explain why is 
linked running slower compare with vector, even they have the same Big ‘O‘ Notation. Those
 coefficients didn’t surprise me too much, most of the coefficients are in the region of 
my prediction based on its Big ‘O‘ Notation and running time. The only data that surprises
 me a bit is BST’s remove dup function, I thought it should be pretty similar to 
coefficient of linked list and vector.
Those results can help me to make a choice of using data types in the future. It shows me 
that although hashtable is not able to do a lot of functions, it can perform very well in 
many functions it can be used. Moreover, if I want my code to run as fast as possible, 
and I need to choose data type from vector and linked list, I will always go for vector, 
because it has lower coefficients.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!
