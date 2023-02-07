HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  < Weihao Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Cian Howell >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 hours >


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order:
min:O(ologo+p) max:O(ologo+q)
It will first push_back all food in a list and then push_back it to the orders list, and
then sort it.
push_back will take O(1), but it will do p(or q) time, and sort will take(nlogn)
add_item:
O(clogc)
it will push_back a item in cocking list O(1), and then it will be sorted (clogc)

print_orders_by_time:
min:O(p*o) max:O(q*o)
for this part we don't need to sort agian, so it only need to loop over the orders list, 
and foods in each order.

print_orders_by_id:
min:O(p*o+ologo)  max:(q*o+ologo)
it will sort first(ologo), and then it will loop over the orders list, and foods in each 
order.

print_kitchen_is_cooking:
O(c)
this will only loop over the cooking_list and print each items

print_kitchen_has_completed:
O(d)
this will only loop over the comlete_cooking_list and print each items

run_until_next:
min O(1); nomal case: times*O(c+o*d);
in my run_until_next; it will loop over the item_cook list; then the order list, while 
loop over the order list it will using the help function be giving which will every time
loop over the complete cocking lit. It will stop if there is any task complete.

run_for_time:
when time= 0:O(c+o*d); else: times*O(c+o*d);
run for time will loop over the item_cook list; then the order list, while 
loop over the order list it will using the help function be giving which will every time
loop over the complete cocking lit. It will stop when it loop over giving minutes of time.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!






