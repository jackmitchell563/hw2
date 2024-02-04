#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if(cmd == "ADD"){
                string username, hit_result_index;
                if(ss >> username){
                    username = convToLower(username);
                    if(nullptr != ds.getUser(username)){ // if user is in users_
                        if(ss >> hit_result_index){
                            unsigned int hitdex = stoi(hit_result_index);
                            if(hitdex <= hits.size() and hitdex > 0){ // 1-based indexing
                                ds.addToCart(convToLower(username), hits[hitdex - 1]);
                            } else cout << "Invalid request" << endl;
                        } else cout << "Invalid request" << endl;
                    } else cout << "Invalid request" << endl;
                } else cout << "Invalid request" << endl;
            }
            else if(cmd == "VIEWCART"){
                string username;
                if(ss >> username){
                    username = convToLower(username);
                    if(nullptr != ds.getUser(username)){
                        vector<Product*> usercart = ds.getCartMap()[username]; // get the user's cart
                        int resultNo = 1; // copied the format of displayProducts, but used the word "Item" instead of "Hit"
                        for(vector<Product*>::iterator it = usercart.begin(); it != usercart.end(); ++it) {
                            cout << "Item " << setw(3) << resultNo << endl;
                            cout << (*it)->displayString() << endl;
                            cout << endl;
                            resultNo++;
                        }
                    } else cout << "Invalid username" << endl;
                } else cout << "Invalid username" << endl;
            }
            else if(cmd == "BUYCART"){
                string username;
                if(ss >> username){
                    username = convToLower(username);
                    if(nullptr != ds.getUser(username)){
                        vector<Product*> usercart = ds.getCartMap()[username];
                        vector<int> to_remove; // store list of indices in usercart to remove
                        for(unsigned int i = 0; i < usercart.size(); i++){
                            if(usercart[i]->getQty() and ds.getUser(username)->getBalance() >= usercart[i]->getPrice()){
                                usercart[i]->subtractQty(1);
                                ds.getUser(username)->deductAmount(usercart[i]->getPrice());
                                to_remove.push_back(i); // add to list of removal indices, but don't remove since we're currently iterating through usercart
                            }
                        }
                        for(int i = to_remove.size() - 1; i >= 0; i--){ // iterate backwards so that lower-index removals don't affect higher indices
                            ds.removeFromCart(username, to_remove[i]);
                        }
                    } else cout << "Invalid username" << endl;
                } else cout << "Invalid username" << endl;
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
