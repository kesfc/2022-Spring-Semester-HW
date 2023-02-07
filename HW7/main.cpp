// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cassert>

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef std::map<std::string, std::map<std::string, int>> MY_MAP;

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word)
{
  char c;
  word.clear();
  while (istr)
  {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c))
    {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "")
      {
        // break words at whitespace
        return true;
      }
    }
    else if (c == '"')
    {
      // double quotes are a delimiter and a special "word"
      if (word == "")
      {
        istr.get(c);
        word.push_back(c);
      }
      return true;
    }
    else if (isalpha(c))
    {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    }
    else
    {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}

// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr)
{
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr, word))
  {
    if (word == "\"")
    {
      if (open_quote == false)
      {
        open_quote = true;
      }
      else
      {
        break;
      }
    }
    else
    {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}

// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText2(std::map<std::string, int> &data, MY_MAP &data2,
                     const std::string &filename, const std::string &parse_method)
{
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr)
  {
    std::cerr << "ERROR cannot open file: " << filename << std::endl;
    exit(1);
  }
  // verify the window parameter is appropriate
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation")
  {
    ignore_punctuation = true;
  }
  else if (parse_method == "parsing_of_punctuation")
  {
    ignore_punctuation = false;
  }
  else
  {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  //
  std::string word;
  std::string prev_word = "";

  if (ignore_punctuation)
  {
    while (ReadNextWord(istr, word))
    {
      // skip the quotation marks (not used for this part)
      if (word == "\"")
        continue;

      if (prev_word != "")
      {
        data2[prev_word][word]++;
      }
      data[word]++;
      prev_word = word;
    }
  }
  else
  {
    while (istr >> word)
    {
      std::cout << word << std::endl;
    }
  }
}

// since I have different type of map, so I choose two diiferent function to help me
// parse the file into map.
void LoadSampleText3(std::map<std::string, int> &data, MY_MAP &data2,
                     std::map<std::string, MY_MAP> &data3, const std::string &filename,
                     const std::string &parse_method)
{
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr)
  {
    std::cerr << "ERROR cannot open file: " << filename << std::endl;
    exit(1);
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation")
  {
    ignore_punctuation = true;
  }
  else if (parse_method == "parsing_of_punctuation")
  {
    ignore_punctuation = false;
  }
  else
  {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  //
  std::string word;
  std::string prev_word = "";
  std::string prev_prev_word = "";

  if (ignore_punctuation)
  {
    while (ReadNextWord(istr, word))
    {
      if (word == "\"")
        continue;

      if (prev_word != "")
      {
        data2[prev_word][word]++;
      }
      if (prev_prev_word != "")
      {
        data3[prev_prev_word][prev_word][word]++;
      }
      data[word]++;
      prev_prev_word = prev_word;
      prev_word = word;
    }
  }
  else
  {
    while (istr >> word)
    {
      std::cout << word << std::endl;
    }
  }
}

// this is the helper function for print method, it will help to find all the word
// followed by the phrase and number of time it appears.
void find_next_word(const std::string word, const MY_MAP &data2,
                    std::map<std::string, int> &data)
{
  int count = data[word];
  std::cout << word << " (" << count << ")" << std::endl;
  MY_MAP::const_iterator w2_itr = data2.find(word);
  std::map<std::string, int>::const_iterator find_word;
  find_word = w2_itr->second.begin();
  for (; find_word != w2_itr->second.end(); find_word++)
  {
    std::cout << word << " " << find_word->first << " (" << find_word->second << ")"
              << std::endl;
  }
}

// helper function for generate with most common, it will find the most frequent word
// that flowed by the giving phrase.
void most_common2(std::string &word, int length, const MY_MAP &data2)
{
  int max;
  MY_MAP::const_iterator itr_w2 = data2.find(word);
  for (int i = 0; i < length; i++)
  { // number of time need to loop is number of more word need to find.
    max = 0;
    std::map<std::string, int>::const_iterator find_word = itr_w2->second.begin();
    std::string most_appear;
    for (; find_word != itr_w2->second.end(); find_word++)
    { // loop through the key of the map and then find the most appears.
      if (find_word->second > max)
      {
        max = find_word->second;
        most_appear = find_word->first;
      }
    }
    if (i == length - 1)
    {
      std::cout << most_appear << std::endl;
    }
    else
    {
      std::cout << most_appear << " ";
    }
    itr_w2 = data2.find(most_appear);
  }
}

// also is the helper function for generate with most common, this is use when the window
//=3, and prase size is two
void most_common3(std::string word, std::string next_word, int length,
                  const std::map<std::string, MY_MAP> &data3)
{
  int max;
  for (int i = 0; i < length; i++)
  // number of time need to loop is number of more word need to find.
  {
    std::string next_next_word;
    max = 0;
    std::map<std::string, MY_MAP>::const_iterator itr_w3 = data3.find(word);
    MY_MAP temp = itr_w3->second;
    MY_MAP::const_iterator itr_w2 = temp.find(next_word);
    std::map<std::string, int>::const_iterator find_word = itr_w2->second.begin();
    for (; find_word != itr_w2->second.end(); find_word++)
    { // loop through the key of the map and then find the most appears.
      if (find_word->second > max)
      {
        max = find_word->second;
        next_next_word = find_word->first;
      }
    }
    if (i == length - 1)
    {
      std::cout << next_next_word << std::endl;
    }
    else
    {
      std::cout << next_next_word << " ";
    }
    word = next_word;
    next_word = next_next_word;
  }
}

/* helper function for generate with random, when the window size=2, I can juts use this
fuction to generate, when window size=3, and word be giving is 1, I will use this 
function to find my next word first and then use another helper function.
*/
std::string random_next2(std::string word, MY_MAP &data2, std::map<std::string, int> 
&data, int length, bool print)
{
  for (int i = 0; i < length; i++)
  {
    int total = data[word];
    int random = rand() % total;
    int count = 0;
    std::map<std::string, int>::iterator count_track = (data2[word]).begin();
    for (; count_track != (data2[word]).end(); count_track++)
    {
      count += count_track->second;
      if (count > random)
      {
        word = count_track->first;
        if (i != length - 1)
        {
          std::cout << word << " ";
        }
        else if (i == length - 1 && print)
        {
          std::cout << word << std::endl;
        }
        break;
      }
    }
  }
  return word;
}

/*This is also a helper function for generate with random, compare with the first helper
function this is use for window =2
*/
void random_next3(std::string word, std::string next_word, MY_MAP &data2,
                  std::map<std::string, MY_MAP> &data3, int length)
{
  for (int i = 0; i < length; i++)
  {
    int total = data2[word][next_word];
    int random = rand() % total;
    int count = 0;
    std::map<std::string, int>::iterator count_track = (data3[word][next_word]).begin();
    for (; count_track != (data2[word]).end(); count_track++)
    {
      count += count_track->second;
      if (count > random)
      {
        word = next_word;
        next_word = count_track->first;
        if (i != length - 1)
        {
          std::cout << next_word << " ";
        }
        else
        {
          std::cout << next_word << std::endl;
        }
        break;
      }
    }
  }
}

int main()
{
  srand(time(NULL));
  std::map<std::string, int> data;
  MY_MAP data2;
  std::map<std::string, MY_MAP> data3;
  int window;

  // ASSIGNMENT: THE MAIN DATA STRUCTURE

  // Parse each command
  std::string command;
  while (std::cin >> command)
  {

    // load the sample text file
    if (command == "load")
    {
      std::cout << "Loaded"
                << " ";
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;
      std::cout << filename << " with window = " << window << " "
                << "and parse method = " << parse_method << std::endl;
      std::cout << std::endl;
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      // since the type of the map will be differ when the window =2, and =3, so I wrote
      // differently when parse it with 2 diiferent helper function. when window is =2
      // I creat a 1d map, a 2d map. whne window is =3, I creat a 1d map, a 2d map, and
      // a 3d map
      if (window < 2)
      {
        std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
      }
      if (window == 2)
      {
        LoadSampleText2(data, data2, filename, parse_method);
      }
      else if (window == 3)
      {
        LoadSampleText3(data, data2, data3, filename, parse_method);
      }
      continue;
    }

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print")
    {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      if (sentence.size() == 1)
      {
        find_next_word(sentence[0], data2, data);
        std::cout << std::endl;
      }
      else if (sentence.size() == 2)
      {
        int count = data2[sentence[0]][sentence[1]];
        std::cout << sentence[0] << " " << sentence[1] << " (" << count << ")"
                  << std::endl;
        std::map<std::string, MY_MAP>::const_iterator w3_itr = data3.find(sentence[0]);
        MY_MAP temp = w3_itr->second;
        MY_MAP::const_iterator w2_itr = temp.find(sentence[1]);
        std::map<std::string, int>::const_iterator find_word = w2_itr->second.begin();
        for (; find_word != w2_itr->second.end(); find_word++)
        {
          std::cout << sentence[0] << " " << sentence[1] << " " << find_word->first
                    << " (" << find_word->second << ")" << std::endl;
        }
        std::cout << std::endl;
      }
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //
      /*
      for print mode I wrote differently depend on number of word is giving to me,
      when only one word is giving to me, I will first find the total number of it appears
      in my id map, then locate all following word with the 2d map. when 2 word is giving
      to me, I will find the total number of it appears by the 2d map, and locate all
      following word by the 3d pointer.
      */
    }

    // generate the specified number of words
    else if (command == "generate")
    {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string word = sentence[0];
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random")
      {
        random_flag = true;
      }
      else
      {
        assert(selection_method == "most_common");
        random_flag = false;
      }
      std::cout << word << " ";
      if (!random_flag)
      {
        int max = 0;
        if (window == 2)
        {
          most_common2(word, length, data2);
        }
        else if (window == 3)
        {
          if (sentence.size() == 1)
          {
            std::string next_word;
            MY_MAP::const_iterator itr_w2 = data2.find(word); // locate to current word
            std::map<std::string, int>::const_iterator find_word = itr_w2->second.begin();
            for (; find_word != itr_w2->second.end(); find_word++)
            { // loop through the key of the map and then find the most appears.
              if (find_word->second > max)
              {
                max = find_word->second;
                next_word = find_word->first;
              }
            }
            std::cout << next_word << " ";
            most_common3(word, next_word, length - 1, data3);
          }
          else if (sentence.size() == 2)
          {
            std::cout << sentence[1] << " ";
            most_common3(sentence[0], sentence[1], length, data3);
          }
        }
        // for generating with most commons, I also write diiferently depends on the 
        // number of words be giving. for finding ever word it will loop through all the
        // word that appeared flowed by the giving phrase and then find out which word
        // apperaed most frequently.
        std::cout << std::endl;
      }
      else if (random_flag)
      {
        if (window == 2)
        {
          random_next2(word, data2, data, length, true);
        }
        else if (window == 3)
        {
          if (sentence.size() == 1)
          {
            std::string next_word = random_next2(word, data2, data, 1, false);
            random_next3(word, next_word, data2, data3, length - 1);
          }
          else if (sentence.size() == 2)
          {
            std::cout << sentence[1] << " ";
            random_next3(word, sentence[1], data2, data3, length - 1);
          }
        }
        std::cout << std::endl;
      }
    }

    /*for generate with number I will first find number of time the phrase is appeared,
    and then I will randanize a number between 1 and the total number. I will locate the
    random number in my map, and the word I get will be the word I use to randanize for 
    next time, untile I find enough word.
    */
    else if (command == "quit")
    {
      break;
    }
    else
    {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}