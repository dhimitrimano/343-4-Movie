#include "moviestore.h"

class Manager {
public:
  // constructor
  explicit Manager(vector<string> vec);

  // destructor
  ~Manager();
  
private:
  // vector of stores
  vector<MovieStore *> stores;

  // creates a store from information
  void createStore(const string &a, const string &b, const string &c);
};