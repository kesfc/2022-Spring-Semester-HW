// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "Item.h"
#include "Order.h"
typedef std::list <Order> OrderList;
typedef std::list <Item> KitchenList;

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &orders, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);
//this function will simulating for a giving amount of time
void run_until_time(OrderList &orders, KitchenList &food_cooking, 
KitchenList &food_completed, int run_minutes){
  OrderFillList iterator_list;
  int time_count = 0; //tracking time passed
  while (run_minutes>time_count){
    std::list<Item>::iterator item_track=food_cooking.begin();
    //use iterator loop over the cooking_list, and minus one minutes first and then check
    //if the time gets to negative and it will remove the item from cooking list and add
    // it to complete cocking list
    while(item_track!=food_cooking.end()){
      (*item_track).minus_one();
      if((*item_track).get_time()<0){
        std::cout<<"Finished cooking "<<(*item_track).getName()<<std::endl;
        food_completed.push_back(*item_track);
        std::list<Item>::iterator p=food_cooking.erase(item_track);
        item_track=p;
      }
      else{
        ++item_track;
      }
    }
    //using the helping function to check if any orders can be filled.
    // if there is any, erase the order and erase the items being used to fill the order 
    //from the complete cocking list.
    std::list<Order>::iterator order_track=orders.begin();
    while(order_track!=orders.end()){
      bool statement=CanFillOrder((*order_track), food_completed, iterator_list);
      if (statement){
        std::cout<<"Filled order #"<<(*order_track).get_id()<<std::endl;
        std::list<Order>::iterator p=orders.erase(order_track);
        order_track=p;
        OrderFillList::iterator iterator_track=iterator_list.begin();
        while(iterator_track!=iterator_list.end()){
          std::cout<<"Removed a "<<(*(*iterator_track)).getName()<<
          " from completed items."<<std::endl;
          food_completed.erase(*iterator_track);
          OrderFillList::iterator p= iterator_list.erase(iterator_track);
          iterator_track=p;
        }
      }
      else{
        //update the promised time and check if any expired.
        (*order_track).minus_one();
        if((*order_track).get_promised_time()<0){
          std::cout<<"Order # "<<(*order_track).get_id()<<" expired."<<std::endl;
          std::list<Order>::iterator p=orders.erase(order_track);
          order_track=p;
        }else{
        order_track++;
        }
      }
    }
    time_count++;
  }
  std::cout<<"===Run for specified time is complete==="<<std::endl;
}
void run_zero(OrderList &orders, KitchenList &food_cooking, KitchenList &food_completed){
  OrderFillList iterator_list;
  //use iterator loop over the cooking_list, and minus one minutes first and then check
  //if the time gets to negative and it will remove the item from cooking list and add
  // it to complete cocking list
  std::list<Item>::iterator item_track=food_cooking.begin();
    while(item_track!=food_cooking.end()){
      if((*item_track).get_time()==0){
        std::cout<<"Finished cooking "<<(*item_track).getName()<<std::endl;
        food_completed.push_back(*item_track);
        std::list<Item>::iterator p=food_cooking.erase(item_track);
        item_track=p;
      }
      else{
        ++item_track;
      }
    }
    std::list<Order>::iterator order_track=orders.begin();
    while(order_track!=orders.end()){
      bool statement=CanFillOrder((*order_track), food_completed, iterator_list);
      if (statement){
        std::cout<<"Filled order #"<<(*order_track).get_id()<<std::endl;
        std::list<Order>::iterator p=orders.erase(order_track);
        order_track=p;
        //using the helping function to check if any orders can be filled.
        // if there is any, erase the order and erase the items being used to fill the order 
        //from the complete cocking list.
        OrderFillList::iterator iterator_track=iterator_list.begin();
        while(iterator_track!=iterator_list.end()){
          std::cout<<"Removed a "<<(*(*iterator_track)).getName()<<
          " from completed items."<<std::endl;
          food_completed.erase(*iterator_track);
          OrderFillList::iterator p= iterator_list.erase(iterator_track);
          iterator_track=p;
        }
      }
      else{
        //update the promised time and check if any expired.
        if((*order_track).get_promised_time()==0){
          std::cout<<"Order # "<<(*order_track).get_id()<<" expired."<<std::endl;
          std::list<Order>::iterator p=orders.erase(order_track);
          order_track=p;
        }else{
          order_track++;
        }
      }
    }
  std::cout<<"===Run for specified time is complete==="<<std::endl;
}

/*This function is used to helping simulating the run until next. in the function there 
will have an interger used to recorde minutes have passed. If there is item being cooked,
order being filled or order expired, the function will stop and print the time have 
passed.
*/
void run_until_next(OrderList &orders, KitchenList &food_cooking, 
KitchenList &food_completed){
  OrderFillList iterator_list;
  //if both orders and food cooking list is empty it will just stop.
  //use iterator loop over the cooking_list, and minus one minutes first and then check
  //if the time gets to negative and it will remove the item from cooking list and add
  // it to complete cocking list
  if (orders.size()==0 && food_cooking.size()==0){
    std::cout<<"No events waiting to process."<<std::endl;
    return;
  }
  int out=0;
  while(true){
  std::list<Item>::iterator item_track=food_cooking.begin();
    while(item_track!=food_cooking.end()){
      (*item_track).minus_one();
      if((*item_track).get_time()<0){
        std::cout<<"Finished cooking "<<(*item_track).getName()<<std::endl;
        food_completed.push_back(*item_track);
        std::list<Item>::iterator p=food_cooking.erase(item_track);
        item_track=p;
        std::cout<<out<<" minute(s) have passed."<<std::endl;
        return;
      }
      else{
        ++item_track;
      }
    }
    //using the helping function to check if any orders can be filled.
    // if there is any, erase the order and erase the items being used to fill the order 
    //from the complete cocking list.
    std::list<Order>::iterator order_track=orders.begin();
    while(order_track!=orders.end()){
      bool statement=CanFillOrder((*order_track), food_completed, iterator_list);
      if (statement){
        std::cout<<"Filled order #"<<(*order_track).get_id()<<std::endl;
        std::list<Order>::iterator p=orders.erase(order_track);
        order_track=p;
        OrderFillList::iterator iterator_track=iterator_list.begin();
        while(iterator_track!=iterator_list.end()){
          std::cout<<"Removed a "<<(*(*iterator_track)).getName()<<
          " from completed items."<<std::endl;
          food_completed.erase(*iterator_track);
          OrderFillList::iterator p= iterator_list.erase(iterator_track);
          iterator_track=p;
        }
        std::cout<<out<<" minute(s) have passed."<<std::endl;
        return;
      }
      else{
        //update the promised time and check if any expired.
        (*order_track).minus_one();
        if((*order_track).get_promised_time()<0){
          std::cout<<"Order # "<<(*order_track).get_id()<<" expired."<<std::endl;
          std::list<Order>::iterator p=orders.erase(order_track);
          order_track=p;
          std::cout<<out<<" minute(s) have passed."<<std::endl;
          return;
        }else{
          order_track++;
        }
      }
    }
  ++out;
  }
}
int main() {
  OrderList orders;
  KitchenList food_cooking;
  KitchenList food_completed;

  std::string token;
  while (std::cin >> token) {
    if (token == "add_order") {
      //it will first turn inputs to an order object item and add it to orders list. 
      //then sort the order list by the promised time
      int id, promised_time, n_items = 0;
      std::string next_item;
      std::list <std::string> order_items;

      std::cin >> id >> promised_time >> n_items;
      assert(n_items > 0);

      for (int i = 0; i < n_items; i++) {
        std::cin >> next_item;
        order_items.push_back(next_item);
      }
      std::cout<<"Received new order #"<< id << " due in "<<promised_time<<" minute(s):"
      <<std::endl;
      std::list<std::string>::iterator p=order_items.begin();
      while (p!=order_items.end()){
        std::cout<<"  "<<*p<<std::endl;
        p++;
      }
      Order order(id, promised_time, order_items);
      orders.push_back(order);
      orders.sort(sort_promised_time);

      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "add_item") {
      //it will first turn input to an item object and than add it to the food cooking 
      //list then sort the order list by time
      int cook_time = -1;
      std::string name;
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);
      std::cout<<"Cooking new "<<name<<" with "<<cook_time<<" minute(s) left."<<std::endl;
      Item new_item(cook_time, name);
      food_cooking.push_back(new_item);
      food_cooking.sort(sort_time);

      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_orders_by_time") {
      /*print each order object in order list with it id, promised time and all food in 
      the order; don't need to sort since it ask print by time, and it is order sorted by 
      time*/
      int size=orders.size();
      std::cout<<"Printing "<<size<<" order(s) by promised time remaining:"<<std::endl;
      std::list<Order>::iterator p=orders.begin();
      while(p!=orders.end()){ 
        std::cout<<"  #"<<(*p).get_id()<<" ("<<(*p).get_promised_time()<<
        " minute(s) left):"<<std::endl;
        std::list <std::string> foods = (*p).getItems();
        std::list <std::string>:: iterator q = foods.begin();
        while(q!=foods.end()){
          std::cout<<"    "<<*q<<std::endl;
          q++;
        }
        p++;
      }
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_orders_by_id") {
      // sort the order by id first and then print it's id, pomised_time, and all food in
      // that order.
      OrderList order_copy=orders;
      order_copy.sort(sort_id);
      int size=order_copy.size();
      std::cout<<"Printing "<<size<<" order(s) by ID:"<<std::endl;
      std::list<Order>::iterator p=order_copy.begin();
      while(p!=order_copy.end()){ 
        std::cout<<"  #"<<(*p).get_id()<<" ("<<(*p).get_promised_time()<<
        " minute(s) left):"<<std::endl;
        std::list <std::string> foods = (*p).getItems();
        std::list <std::string>:: iterator q = foods.begin();
        while(q!=foods.end()){
          std::cout<<"    "<<*q<<std::endl;
          q++;
        }
        p++;
      }
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_kitchen_is_cooking") {
      //print all item that is been cocking and time need to cook;
      int size= food_cooking.size();
      std::cout<<"Printing "<<size<<" items being cooked:"<<std::endl;
      std::list<Item>::iterator p=food_cooking.begin();
      while (p!=food_cooking.end()){
        std::cout<<"  "<<(*p).getName()<<" ("<<(*p).get_time()<<" minute(s) left)"<<
        std::endl;
        p++;
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "print_kitchen_has_completed") {
      //print all complete cooked food that are not being used to fiil the order yet.
      int size= food_completed.size();
      std::cout<<"Printing "<<size<<" completely cooked items:"<<std::endl;
      std::list<Item>::iterator p=food_completed.begin();
      while (p!=food_completed.end()){
        std::cout<<"  "<<(*p).getName()<<std::endl;
        p++;
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "run_for_time") {
      //giving a specific time and simulating that times.
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);
      std::cout<<"===Starting run of "<<run_time<<" minute(s)==="<<std::endl;
      if(run_time>0){
        run_until_time(orders, food_cooking, food_completed, run_time);
      }
      else{
        run_zero(orders, food_cooking, food_completed);
      }
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    } else if (token == "run_until_next") {
      //simulating until next event heppend.
      std::cout << "Running until next event." << std::endl;
      run_until_next(orders, food_cooking, food_completed);
      /* YOU MUST FINISH THIS IMPLEMENTATION */
    }
  }

  return 0;
}


bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

