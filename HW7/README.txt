HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Weihao Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Haoran Bao, Chengyu Zhang, Kenneth DOng >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10h >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?
O(n+m+m(m-1)) when w=2, OO(n+m+m(m-1)+m(m-1)(m-2))
storage take for the file is n, becuase it parse to each word and then store in mp. 
when w=2, I have 2d map, a 1d, and a 2d. storage for 1d is O(m), since int is too small, 
don't need to count. worst case of the storage for 2d map is O(m(m-1)), all unique words
other than itself have appeared followed by each word(it is almost imposible, so the real
case will be much smaller than this.). if w = 3, I will have a 3d map, similar to the
2d map, it will take O(m(m-1)(m-2)).


What is the order notation for performance (running time) of each of
the commands?
load:: O(n+wlong(n))
time to get all file will be n, and for every word in window=2 it will be use to search in
two maps, and for every word in window=2 it will be use to search in three maps.
print:: O(2log(n)+p)
time to search for a key is log(n), we need use it 2 times, one for get total number, 
another to get all word follow(p),
generate:: most_commons:: O(x*(log(n)+p))
we first need to find the key(log(n)), and we need go to the inner map to loop all word
that appeared after(p), for x times.
random:: O(x*(2log(n)+p))
we first use one of the map to get time of the phrase appeared, and then we randomnize a
number, the we search for the phrase in the map(log(n)), and we need to do it for x time.


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


