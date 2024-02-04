#include "movie.h"
#include "util.h"
#include<set>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

Movie::Movie(const std::string name, double price, int qty, string genre, string rating) :
  Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

set<string> Movie::keywords() const{
  set<string> s, s2;
  s = parseStringToWords(getName());
  s.insert(convToLower(genre_));
  s2.insert(convToLower(rating_));
  return setUnion(s, s2);
}

string Movie::displayString() const{
  string s = "";
  s += getName() + "\n";
  s += "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n";
  stringstream ss;
  ss << fixed << setprecision(2) << getPrice();
  s += ss.str() + " " + to_string(getQty()) + " left.\n";
  return s;
}