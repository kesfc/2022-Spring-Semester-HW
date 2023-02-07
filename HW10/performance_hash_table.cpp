#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

// defined in performance.cpp
void usage();

template <class T>
void hash_table_remove_duplicates(std::unordered_map<T, int> Map, std::ostream &ostr, 
int &output_count){
  output_count = Map.size();
  typename std::unordered_map<T, int>::const_iterator j;
  for (int i = 0; i < output_count; i++){
    for (j = Map.begin(); j != Map.end(); j++){
      if (i == j->second)
      {
        ostr << j->first << "\n";
        break;
      }
    }
  }
}

template <class T>
void hash_table_mode(std::unordered_map<T, int> Map, std::ostream &ostr, 
int &output_count){
  typename std::unordered_map<T, int>::const_iterator i;
  T out;
  int max = 0;
  for (i = Map.begin(); i != Map.end(); i++){
    if (i->second > max){
      max = i->second;
      out = i->first;
    }
  }
  output_count = 1;
  ostr << out << "\n";
}

void hash_table_longest_substring(std::unordered_set<std::string> Set, std::ostream &ostr,
int &output_count){
  std::string Final;
  std::unordered_set<std::string>::const_iterator i;
  for (i = Set.begin(); i != Set.end(); i++){
    for (unsigned int k = 0; k < (*i).size(); k++){
      for (unsigned j = k+1; j < (*i).size(); j++){
        std::string temp = (*i).substr(k, j - k);
        if (temp.size() <= Final.size()){
          continue;
        }
        std::unordered_set<std::string>::const_iterator l = i;
        l++;
        for (; l != Set.end(); l++){
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

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg){
  if (type == "string"){
    // load the data into a vector of strings
    std::unordered_set<std::string> Set;
    std::unordered_map<std::string, int> Map1;
    std::unordered_map<std::string, int> Map2;
    std::string s;
    input_count = 0;
    int index=0;
    std::unordered_map<std::string, int>::iterator add;
    while (istr >> s){
      Set.insert(s);
      Map2[s]++;
      add=Map1.find(s);
      if(add==Map1.end()){
        Map1[s]=index;
        index++;
      }
      input_count++;
    }
    if (operation == "remove_duplicates"){
      hash_table_remove_duplicates(Map1, ostr, output_count);
    }
    else if (operation == "mode"){
      hash_table_mode(Map2, ostr, output_count);
    }
    else if (operation == "longest_substring"){
      hash_table_longest_substring(Set, ostr, output_count);
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
    std::unordered_map<int, int> Map1;
    std::unordered_map<int, int> Map2;
    int v;
    int index=0;
    std::unordered_map<int, int>::iterator add;
    while (istr >> v){
      Map2[v]++;
      add=Map1.find(v);
      if(add==Map1.end()){
        Map1[v]=index;
        index++;
      }
      input_count++;
    }
    if (operation == "remove_duplicates"){
      hash_table_remove_duplicates(Map1, ostr, output_count);
    }
    else if (operation == "mode"){
      hash_table_mode(Map2, ostr, output_count);
    }
    // "longest_substring" not available for integers
    else{
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }
}
