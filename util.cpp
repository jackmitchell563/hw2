#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> s;
  int currlen = 0, wordstart = 0;
  for(unsigned int idx = 0; idx < rawWords.length(); idx++){
    // check if the current char isn't punctuation or a space
    if(!ispunct(rawWords[idx]) and !isspace(rawWords[idx])){
      currlen++;
    } else{ // add word to list if it's 2 characters or longer
      if(currlen >= 2){
        s.insert(convToLower(rawWords.substr(wordstart, currlen))); // convert to lowercase to make searching easier
      }
      wordstart = idx + 1; // set the starting index of the next word
      currlen = 0; // reset current word length
    }
  }
  if(currlen >= 2){ // need to check one more time since the loop terminates at the end of rawWords
    s.insert(convToLower(rawWords.substr(wordstart, currlen)));
  }
  return s;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
