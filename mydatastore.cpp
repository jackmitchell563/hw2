#include "mydatastore.h"
#include "util.h"
#include<fstream>
#include<iostream>
using namespace std;

MyDataStore::~MyDataStore(){
  vector<Product*>::iterator it;
  for(it = products_.begin(); it != products_.end(); it++)
    delete *it;
  map<string, User*>::iterator it2;
  for(it2 = users_.begin(); it2 != users_.end(); it2++)
    delete (*it2).second;
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  set<string> pkwords = p->keywords();
  set<string>::iterator it;
  for(it = pkwords.begin(); it != pkwords.end(); it++){
    if(keywordmap_.find(*it) == keywordmap_.end()){ // if the key isn't in keywordmap_ yet
      set<Product*> initset({p});
      keywordmap_[*it] = initset;
    } else{
      keywordmap_[*it].insert(p); // if the key's already in the map, add the current product to its product set
    }
  }
  // map<string, set<Product*> >::iterator testit;
  // set<Product*>::iterator testit2;
  // for(testit = keywordmap_.begin(); testit != keywordmap_.end(); testit++){
  //   cout << (*testit).first << "-----------------------" << endl;
  //   for(testit2 = (*testit).second.begin(); testit2 != (*testit).second.end(); testit2++)
  //     cout << (*testit2)->getName() <<  " ";
  //   cout << endl;
  // }
}

void MyDataStore::addUser(User* u){
  users_[convToLower(u->getName())] = u;
}

void MyDataStore::addToCart(string user, Product* product){
  cartmap_[user].push_back(product);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  vector<Product*> returnvec;
  vector<string>::iterator it = terms.begin();
  set<Product*> runningset({keywordmap_[*it]}); // initialize with the first term's mapped products
  if(type == 0){ // AND search
    for(it++; it != terms.end(); it++){ // start from the second term since the first one's already been included
      runningset = setIntersection(runningset, keywordmap_[*it]); // iterate through and find the intersection of all terms' product sets
    }
  } else { // OR search
    for(it++; it != terms.end(); it++){
      runningset = setUnion(runningset, keywordmap_[*it]); // iterate through and find the union of all terms' product sets
    }
  }
  set<Product*>::iterator it2;
  for(it2 = runningset.begin(); it2 != runningset.end(); it2++)
    returnvec.push_back(*it2);
  return returnvec;
}
void MyDataStore::dump(std::ostream& os){
  os << "<products>\n";
  for(unsigned int i = 0; i < products_.size(); i++){
    products_[i]->dump(os);
  }
  os << "</products>\n";
  os << "<users>\n";
  map<string, User*>::iterator it;
  for(it = users_.begin(); it != users_.end(); it++){
    (*it).second->dump(os);
  }
  os << "</users>\n";
}