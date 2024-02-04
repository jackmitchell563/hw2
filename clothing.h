#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include<fstream>
#include<string>
#include<set>

class Clothing : public Product{
  public:
    Clothing(const std::string name, double price, int qty, std::string size, std::string brand);
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const{
      Product::dump(os);
      os << size_ << std::endl;
      os << brand_ << std::endl;
    }
  private:
    std::string size_;
    std::string brand_;
};

#endif