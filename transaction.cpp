#include "transaction.h"

BorrowFactory strangeBorrowFactory;
ReturnFactory strangeReturnFactory;

ostream &Transaction::print(ostream &out) const {
  out << "Transaction Type: " << transactionType << endl;
  out << *movie << endl;
  return out;
}

ostream &operator<<(ostream &out, const Transaction &tra) {
  return tra.print(out);
}

void Transaction::rememberType(const char &type, TransactionFactory *factory) {
  getFactories().emplace(type, factory);
}

Transaction *Transaction::create(const char &type) {
  if (getFactories().count(type) > 0) {
    return getFactories().at(type)->create();
  }
  cerr << "Error: No factory exists for " << type << "!" << endl;
  return nullptr;
}

map<char, TransactionFactory *> &Transaction::getFactories() {
  static map<char, TransactionFactory *> factories;
  return factories;
}