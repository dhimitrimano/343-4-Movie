#include "customer.h"
#include "hashtable.h"
#include "inventory.h"
#include <fstream>
#include <queue>
#include <sstream>

class MovieStore {
public:
  // processes the customer data, returns true if successful
  // otherwise, returns false
  void processCustomerData();

  // processes the customer data, returns true if successful
  // otherwise, returns false
  void processMovieData();

  // processes the customer data, returns true if successful
  // otherwise, returns false
  void processCommands();

  // constructor
  MovieStore(const string &customersInput, const string &moviesInput, const string &commandsInput);

  // default destructor
  ~MovieStore() = default;
private:
  // the inventory of media. index 0 is for 'D', the DVD movies
  map<char, Inventory> movies;

  // the hashtable of customers
  HashTable customers;

  // queues to hold the file commands
  queue<string> customerQueue;
  queue<string> movieQueue;
  queue<string> commandQueue;

  // helper for getting substring until an instance of char
  string subStringUntilChar(string &str, int &start, char ch);

  // helper for processing drama or comedy movie
  void processDramedyDVDMovie(string &str);

  // helper for processing classic movie
  void processClassicDVDMovie(string &str);

  // helper for processing a transaction involving a comedy movie
  void processComedyDVDMovieTransaction(string &str, Customer *&customer);
  
  // helper for processing a transaction involving a drama movie
  void processDramaDVDMovieTransaction(string &str, Customer *&customer);
  
  // helper for processing a transaction involving a classic movie
  void processClassicDVDMovieTransaction(string &str, Customer *&customer);

  // helper for processing transactions
  void processTransaction(string &str);
};