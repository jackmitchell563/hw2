#include "book.h"
#include "util.h"
#include<set>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

Book::Book(const std::string name, double price, int qty, string isbn, string author) :
  Product("book", name, price, qty), isbn_(isbn), author_(author) {}

set<string> Book::keywords() const{
  set<string> s, s2;
  s = parseStringToWords(getName());
  s.insert(isbn_);
  s2 = parseStringToWords(author_);
  return setUnion(s, s2);
}

string Book::displayString() const{
  string s = "";
  s += getName() + "\n";
  s += "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n";
  stringstream ss;
  ss << fixed << setprecision(2) << getPrice();
  s += ss.str() + " " + to_string(getQty()) + " left.\n";
  return s;
}