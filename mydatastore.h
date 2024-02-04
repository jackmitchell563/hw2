#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore{
  public:
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    void addToCart(std::string user, Product* product);
    void removeFromCart(std::string user, int pos){cartmap_[user].erase(cartmap_[user].begin() + pos);}
    std::map<std::string, std::vector<Product*> > getCartMap() const {return cartmap_;}
    User* getUser(std::string username) {if(users_.find(username) != users_.end()) return users_[username]; return nullptr;}
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& os);
  private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordmap_;
    std::map<std::string, std::vector<Product*> > cartmap_;
};

#endif