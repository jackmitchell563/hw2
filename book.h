#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include<fstream>
#include<string>
#include<set>

class Book : public Product{
  public:
    Book(const std::string name, double price, int qty, std::string isbn, std::string author);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const{
      Product::dump(os);
      os << isbn_ << std::endl;
      os << author_ << std::endl;
    }
  private:
    std::string isbn_;
    std::string author_;
};

#endif