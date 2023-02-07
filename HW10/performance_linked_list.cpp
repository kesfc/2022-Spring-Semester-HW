#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

// defined in performance.cpp
void usage();

template <class T>
//sort and loop it with iterator to ostream it
void linked_list_sort(std::list<T> &lis, std::ostream &ostr, int &output_count){
  lis.sort();
  typename std::list<T>::const_iterator i;
  for (i = lis.begin(); i != lis.end(); i++){
    ostr << *i << "\n";
    output_count++;
  }
}

template <class T>
void linked_list_remove_duplicates(const std::list<T> &lis, std::ostream &ostr, 
int &output_count){
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  typename std::list<T>::const_iterator i;
  typename std::list<T>::const_iterator j;
  for (i = lis.begin(); i != lis.end(); i++){
    bool dup = true;
    for (j=lis.begin(); j != i; j++){
      if (*i == *j){
        dup = false;
        break;
      }
    }
    // if it has not already been added to the output list
    if (dup){
      ostr << *i << "\n";
      output_count++;
    }
  }
}

template <class T>
void linked_list_mode(std::list<T> &lis, std::ostream &ostr, int &output_count){
  // use the vector sort algorithm
  lis.sort();
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::list<T>::iterator current = lis.begin();
  ++current;
  typename std::list<T>::iterator previous = lis.begin();
  for (; current != lis.end(); ++current, ++previous){
    if (*current == *previous)
    {
      // if they are the same element increment the count
      current_count++;
    }
    else if (current_count >= mode_count){
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    }
    else{
      current_count = 1;
    }
  }
  if (current_count >= mode_count){
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}

// note: closest_pair is only available for integer data (not string data)
void linked_list_closest_pair(std::list<int> &lis, std::ostream &ostr, int &output_count)
{
  assert(lis.size() >= 2);
  // use the vector sort algorithm
  lis.sort();
  output_count = 2;
  int best = -1;
  int best_1;
  int best_2;
  // the two elements with closest value must be next to each other in sorted order
  std::list<int>::const_iterator i = lis.begin();
  int prev = *i;
  int next;
  i++;
  for (; i != lis.end(); i++){
    next = *i;
    int diff = next - prev;
    if (best == -1 || diff < best){
    //if it is equal to initialize number or greater than diff
      best = diff;
      best_1 = prev;
      best_2 = next;
    }
    prev = next;
  }
  // print the two elements
  output_count = 2;
  ostr << best_1 << "\n";
  ostr << best_2 << "\n";
}

template <class T>
void linked_list_first_sorted(std::list<T> &lis, std::ostream &ostr, int &output_count, 
int optional_arg){
  assert(optional_arg >= 1);
  assert((int)lis.size() >= optional_arg);
  // use the vector sort algorithm
  lis.sort();
  output_count = optional_arg;
  typename std::list<T>::const_iterator j = lis.begin();
  for (int i = 0; i < output_count; i++){
    ostr << *j << "\n";
    j++;
  }
}

void linked_list_longest_substring(std::list<std::string> &lis, std::ostream &ostr, 
int &output_count){
  std::string Final;
  std::list<std::string>::const_iterator i;
  for (i = lis.begin(); i != lis.end(); i++){
    for (unsigned int k = 0; k < (*i).size(); k++){
      for (unsigned j = k+1; j < (*i).size(); j++){
        std::string temp = (*i).substr(k, j - k);//find all possible substring
        if (temp.size() <= Final.size()){
          continue;
        }
        std::list<std::string>::const_iterator l = i;
        l++;
        for (; l != lis.end(); l++){
          //bring the substring and loop over to see any string have a matched one.
          if(*l!=*i){
            int index = (*l).find(temp);
            if (index != -1){
              Final = temp;
            }
          }
        }
      }
    }
  }
  output_count = 1;
  ostr << Final << "\n";
}

void list_test(const std::string &operation, const std::string &type,
               std::istream &istr, std::ostream &ostr,
               int &input_count, int &output_count, int optional_arg){
  if (type == "string"){
    // load the data into a vector of strings
    std::list<std::string> lis;
    std::string s;
    input_count = 0;
    while (istr >> s){
      lis.push_back(s);
      input_count++;
    }
    if (operation == "sort"){
      linked_list_sort(lis, ostr, output_count);
    }
    else if (operation == "remove_duplicates"){
      linked_list_remove_duplicates(lis, ostr, output_count);
    }
    else if (operation == "mode"){
      linked_list_mode(lis, ostr, output_count);
    }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted"){
      linked_list_first_sorted(lis, ostr, output_count, optional_arg);
    }
    else if (operation == "longest_substring"){
      linked_list_longest_substring(lis, ostr, output_count);
    }
    else
    {
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }

  else
  {
    assert(type == "integer");
    // load the data into a vector of integers
    std::list<int> lis;
    int v;
    input_count = 0;
    while (istr >> v)
    {
      lis.push_back(v);
      input_count++;
    }
    if (operation == "sort")
    {
      linked_list_sort(lis, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      linked_list_remove_duplicates(lis, ostr, output_count);
    }
    else if (operation == "mode")
    {
      linked_list_mode(lis, ostr, output_count);
    }
    else if (operation == "closest_pair")
    {
      linked_list_closest_pair(lis, ostr, output_count);
    }
    else if (operation == "first_sorted")
    {
      linked_list_first_sorted(lis, ostr, output_count, optional_arg);
    }
    // "longest_substring" not available for integers
    else
    {
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }
}
