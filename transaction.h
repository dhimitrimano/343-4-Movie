#pragma once
#include "dvdmovie.h"
#include <iostream>

class Transaction;

class TransactionFactory {
public:
  // virtual to build the Transaction
  virtual Transaction *create() const = 0;
};

class Transaction {
  // for cout
  friend ostream &operator<<(ostream &out, const Transaction &tra);

  // also for cout, but it works with overloading
  virtual ostream &print(std::ostream &out) const;

public:
  // virtual destructor for virtual class
  virtual ~Transaction() = default;
  
  // type of transaction
  char transactionType;

  // media being transacted
  DVDMovie *movie;

  // remembers the different types of factories
  static void rememberType(const char &type, TransactionFactory *factory);

  // creates a Transaction
  static Transaction *create(const char &type);

private:
  // factory list
  static map<char, TransactionFactory *> &getFactories();

  friend class MovieStore;

  friend class Inventory;

  friend class Customer;
};

class Borrow : public Transaction {
private:
  // the constructor
  explicit Borrow();

  // for corresponding factory to access it
  friend class BorrowFactory;

  friend class MovieStore;

  friend class Inventory;

  friend class Customer;
};

class Return : public Transaction {
private:
  // the constructor
  explicit Return();

  // for corresponding factory to access it
  friend class ReturnFactory;
};

class BorrowFactory : public TransactionFactory {
public:
  // the constructor
  BorrowFactory();

  // overrided create function that returns a borrow transaction
  Transaction *create() const override;
};

class ReturnFactory : public TransactionFactory {
public:
  // the constructor
  ReturnFactory();

  // overrided create function that returns a return transaction
  Transaction *create() const override;
};