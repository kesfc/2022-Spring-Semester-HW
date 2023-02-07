HOMEWORK 6: STAR BATTLE


NAME:  < Weihao Li >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Kenneth Dong, Chengyu Zheng, Haoran Bao / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15h >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of zones (z)? 
The average number of squares in a zone (t) 
The number of stars per zone(s)? 
etc.
O((z-1)*t^2)^s
For my function, if the number of star asking to place in a zone is one, it will first 
find out that every position in the first zone can place a star, then it will move to the 
next zone, the worst case for that is it looped all overed the second zone and only the 
last positon. Then move to the next zone, the worst case is also it loop over the zone and
the only the last position can place a star... so if star in the zone=1, the time will be
O((z-1)*t*t)(number of squares in first zone times all the rest of spors). If the number 
of stars allowed in the zone is larger than 1, for every zone it will run number of 
squres ^ number of star it allowed. So I think my running time will be O((z-1)*t^2)^s.

DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
I first made a puzzle with a empty position, just want to check if there is any problem 
to running a not correct board.
I also made a 10*10(a big grid), but instead giving some big zones, I chose do give many 
small zones.

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
# of solutions & approximate wall clock running time for different
puzzles / stars per zone for a single solution or all solutions. Be
specific about which puzzle/parameters you were timing.
for the first puzzle I made it was actually running perfectly, the second puzzle finished 
run with 0 solution, but I think it is on the right track, because I was using my 
<<opertor to tracking the board change. For all the providing puzzels, my function get 
all the correct number of solution(not able to actually tracking all the solutions is 
correct or not), and other than the last two puzzel(the two said will not be use to get
tested), all the rest of the puzzels can run under 5s.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


