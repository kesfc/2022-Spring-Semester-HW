#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

typedef std::priority_queue<int, std::vector<int>, std::greater<int>> int_queue;
typedef std::priority_queue<std::string, std::vector<std::string>, 
std::greater<std::string>> string_queue;
    // defined in performance.cpp
    void
    usage();

template <class T>
void pq_sort(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq, 
std::ostream &ostr, int &output_count){
  //ostream a top and them pop one until it is empty.
  while (!pq.empty()){
    ostr << pq.top() << "\n";
    pq.pop();
    output_count++;
  }
}
template <class T>
void pq_mode(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq, 
std::ostream &ostr, int &output_count){
  T mode; T current;
  int count = 0; int max = 0;
  //since it is in a order, so only count how many is in a row, and compare with max.
  while (!pq.empty()){
    if (current == pq.top()){
      count++;
    }
    else{
      if (count > max){
        max = count;
        mode = current;
      }
      count = 1;
      current = pq.top();
    }
    pq.pop();
  }
  output_count = 2;
  ostr << mode << "\n";
}

void pq_closest_pair(int_queue &pq, std::ostream &ostr, int &output_count){
  int last = pq.top();//initialize it as the first in the pq.
  int current;
  int out1; int out2;
  int diff; int best = -1;//initialize best to a number won't occure
  pq.pop();
  while (! pq.empty()){
    current = pq.top();
    diff = current - last;
    if (best == -1 || diff < best){//check if need to update best.
      best = diff;
      out1 = last;
      out2 = current;
    }
    last = current;
    pq.pop();
  }
  output_count = 2;
  ostr << out1 << "\n";
  ostr << out2 << "\n";
}

template<class T>
void pq_first_sorted(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq, 
std::ostream &ostr, int &output_count, int optional_arg){
  assert(optional_arg >= 1);
  assert((int)pq.size() >= optional_arg);
  output_count = optional_arg; 
  //top one and pop one untile it get to number of thing being asking.
  for (int i = 0; i < output_count; i++){
    ostr << pq.top() << "\n";
    pq.pop();
  }
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg){
  if (type == "string"){
    // load the data into a vector of strings
    string_queue min_pq;
    std::string s;
    input_count = 0;
    while (istr >> s){
      min_pq.push(s);
      input_count++;
    }
    if (operation == "sort"){
      pq_sort(min_pq, ostr, output_count);
    }
    else if (operation == "mode"){
      pq_mode(min_pq, ostr, output_count);
    }
    else if (operation == "first_sorted"){
      pq_first_sorted(min_pq, ostr, output_count, optional_arg);
    }
    else{
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }

  else{
    assert(type == "integer");
    // load the data into a vector of integers
    int_queue min_pq;
    int v;
    input_count = 0;
    while (istr >> v){
      min_pq.push(v);
      input_count++;
    }
    if (operation == "sort"){
      pq_sort(min_pq, ostr, output_count);
    }
    else if (operation == "mode"){
      pq_mode(min_pq, ostr, output_count);
    }
    else if (operation == "closest_pair"){
      pq_closest_pair(min_pq, ostr, output_count);
    }
    else if (operation == "first_sorted"){
      pq_first_sorted(min_pq, ostr, output_count, optional_arg);
    }
    else
    {
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR

  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)
}
