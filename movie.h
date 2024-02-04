#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include<fstream>
#include<string>
#include<set>

class Movie : public Product{
  public:
    Movie(const std::string name, double price, int qty, std::string genre, std::string rating);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const{
      Product::dump(os);
      os << genre_ << std::endl;
      os << rating_ << std::endl;
    }
  private:
    std::string genre_;
    std::string rating_;
};

#endif