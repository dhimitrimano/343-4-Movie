#include "customer.h"
#include <iostream>

using namespace std;

struct HashNode {
public:
  Customer *val;
  HashNode *next;
  explicit HashNode(Customer *newCustomer) : val(newCustomer), next(nullptr) {}
};

class HashTable {
public:
  // insert into hash table
  bool insert(Customer *newCustomer);

  // retrieve from hash table. ret becomes nullptr if it isn't there
  void retrieve(string idNumber, Customer *&ret);

  // constructor
  HashTable();

  // destructor
  ~HashTable();
private:
  // number of buckets it has
  const int buckets = 29;

  // the hashtable itself
  HashNode **hashTable;

  // hashing function that takes the value of all chars in customer id
  // times their index positions plus one 
  int getHash(string &num) const;
};