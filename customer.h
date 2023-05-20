#pragma once
#include "dvdmovie.h"
#include "transaction.h"

class Customer {
public:
  // gets a movie from the borrowing vector
  DVDMovie *&getMovie(char type, const string &strA, const string &strB);

  // removes a movie from the borrowing vector
  void removeMovie(char type, const string &strA, const string &strB);
private:
  // the customer's id
  string customerID;

  // the customer's name
  string firstName;
  string lastName;

  // the currently borrowed movies
  vector<DVDMovie *> borrowing;

  // the transaction history
  vector<Transaction *> history;

  // customer constructor
  explicit Customer(string customerIDC, string lastNameC, string firstNameC);
  
  // customer destructor
  ~Customer();

  friend class HashTable;
  friend class Inventory;
  friend class MovieStore;
};