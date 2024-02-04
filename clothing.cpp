#include "clothing.h"
#include "util.h"
#include<set>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, string size, string brand) :
  Product("clothing", name, price, qty), size_(size), brand_(brand) {}

set<string> Clothing::keywords() const{
  set<string> s, s2;
  s = parseStringToWords(getName());
  s.insert(convToLower(size_));
  s2 = parseStringToWords(brand_);
  return setUnion(s, s2);
}

string Clothing::displayString() const{
  string s = "";
  s += getName() + "\n";
  s += "Size: " + size_ + " " + "Brand: " + brand_ + "\n";
  stringstream ss;
  ss << fixed << setprecision(2) << getPrice();
  s += ss.str() + " " + to_string(getQty()) + " left.\n";
  return s;
}