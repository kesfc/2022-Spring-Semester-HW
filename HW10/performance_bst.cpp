#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>

// defined in performance.cpp
void usage();

template <class T>
//input the map that use passed in int/string as key, time it occure as value
void bst_sort(std::map<T, int> &map1, std::ostream &ostr, int &output_count){
  typename std::map<T, int>::const_iterator i;
  for (i = map1.begin(); i != map1.end(); i++){
    //use iterator to loop over the map
    for (int k = 0; k < i->second; k++){//print as many time as it occures
      ostr << i->first << "\n";
    }
  }
  output_count++;
}

template <class T>
//input the map that use passed in int/string as value, it's index as key
void bst_remove(std::map<int, T> &map1, std::ostream &ostr, int &output_count){
  typename std::map<int, T>::const_iterator i;
  typename std::map<int, T>::const_iterator j;
  for (i = map1.begin(); i != map1.end(); i++)
  {
    bool print = true;
    for (j = map1.begin(); j != i; j++){//find if there is duplicate
      if (i->second == j->second){
        print = false; break;
      }
    }
    if (print){
      ostr << i->second << "\n";
      output_count++;
    }
  }
}

template <class T>
//input the map that use passed in int/string as key, time it occure as value
void bst_mode(std::map<T, int> &map1, std::ostream &ostr, int &output_count){
  typename std::map<T, int>::const_iterator i;
  T out;
  int max = 0;
  for (i = map1.begin(); i != map1.end(); i++){
    if (i->second > max){//find the max occured
      max = i->second;
      out = i->first;
    }
  }
  output_count = 1;
  ostr << out << "\n";
}

template <class T>
//input the map that use passed in int/string as key, time it occure as value
void bst_closest_pair(std::map<T, int> &map1, std::ostream &ostr, int &output_count){
  typename std::map<T, int>::const_iterator i;
  int last;   // first use to compare
  int curent; // second use to compare
  int diff;
  int best = -1; // biigest diff
  int out1 = -1; int out2 = -1;
  i = map1.begin();
  last = i->first;
  if (i->second > 1)
  { // corner case that first thing in the map occured two times.
    ostr << last << "\n";
    ostr << last << "\n";
  }
  else{
    i++;
    for (; i != map1.end(); i++)
    {
      curent = i->first;
      if (i->second > 1)
      {
        out1 = last;
        out2 = curent;
        break;
      }
      else
      {
        diff = curent - last;
        if (diff < best || best == -1)
        {
          best = diff; out1 = last; out2 = curent;
        }
        last = curent;
      }
    }
  }
  output_count = 2;
  ostr << out1 << "\n";
  ostr << out2 << "\n";
}

template <class T>
//input the map that use passed in int/string as key, time it occure as value
void bst_first_sorted(std::map<T, int> &map1, std::ostream &ostr, int &output_count, 
int optional_arg){
  assert(optional_arg >= 1);
  assert((int)map1.size() >= optional_arg);
  // use the vector sort algorithm
  output_count = optional_arg;
  typename std::map<T, int>::const_iterator i = map1.begin();
  int count = 0;
  while (true){
    if (i == map1.end())
      break;
    else{
      for (int j = 0; j < i->second; j++){
        ostr << i->first << "\n";
        count++;
        if (count == output_count)
          break;
      }
      if (count == output_count)
        break;
      else
        i++;
    }
  }
}

void bst_longest_substring(std::set<std::string> set1, std::ostream &ostr, 
int &output_count){
  std::string Final;//make a string use to store substring.
  std::set<std::string>::const_iterator i;
  for (i = set1.begin(); i != set1.end(); i++){
    for (unsigned int k = 0; k < (*i).size(); k++){
      for (unsigned j = k+1; j < (*i).size(); j++){
        //since we have ckeck everything before k, so started leasted loop with k+1
        std::string temp = (*i).substr(k, j - k);
        if (temp.size() <= Final.size()){//if the size is smaller don't need to find.
          continue;
        }
        std::set<std::string>::const_iterator l = i;
        l++;
        for (; l != set1.end(); l++){
          int index = (*l).find(temp);
          if (index != -1){
            Final = temp;
          }
        }
      }
    }
  }
  ostr << Final << "\n";
  output_count = 1;
}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg)
{
  // HINT: For the string element type, declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR
  // std::map<std::string,int> mp;
  if (type == "string"){
    // load the data into a vector of strings
    //since submitty has print order requirement, to match submitty's expect output,
    //I creat two map and a set
    std::set<std::string> set1;
    std::map<std::string, int> map1;
    //int/string passed in as key, number of times occured is value.
    std::map<int, std::string> map2;
    //int/string passed in as value, ordered it passed in as key
    std::string s;
    input_count = 0;
    while (istr >> s){
      set1.insert(s);
      map1[s]++;
      map2[input_count] = s;
      input_count++;
    }
    if (operation == "sort"){
      bst_sort(map1, ostr, output_count);
    }
    else if (operation == "remove_duplicates"){
      bst_remove(map2, ostr, output_count);
    }
    else if (operation == "mode"){
      bst_mode(map1, ostr, output_count);
    }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted"){
      bst_first_sorted(map1, ostr, output_count, optional_arg);
    }
    else if (operation == "longest_substring"){
      bst_longest_substring(set1, ostr, output_count);
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
    std::map<int, int> map1;
    std::map<int, int> map2;
    int v;
    input_count = 0;
    while (istr >> v){
      map1[v]++;
      map2[input_count] = v;
      input_count++;
    }
    if (operation == "sort"){
      bst_sort(map1, ostr, output_count);
    }
    else if (operation == "remove_duplicates"){
      bst_remove(map2, ostr, output_count);
    }
    else if (operation == "mode"){
      bst_mode(map1, ostr, output_count);
    }
    else if (operation == "closest_pair"){
      bst_closest_pair(map1, ostr, output_count);
    }
    else if (operation == "first_sorted"){
      bst_first_sorted(map1, ostr, output_count, optional_arg);
    }
    // "longest_substring" not available for integers
    else{
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }
}
