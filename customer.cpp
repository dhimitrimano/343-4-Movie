#include "customer.h"

Customer::Customer(string customerIDC, string lastNameC, string firstNameC) {
  customerID = move(customerIDC);
  lastName = move(lastNameC);
  firstName = move(firstNameC);
  borrowing.emplace_back(nullptr);
}

Customer::~Customer() {
  for (auto &h : history) {
    delete h;
  }
}

DVDMovie *&Customer::getMovie(char type, const string &strA,
                              const string &strB) {
  for (int i = 1; i < borrowing.size(); i++) {
    if (type == 'F' && borrowing[i]->title == strA &&
        borrowing[i]->date == strB) {
      return borrowing[i];
    }
    if (type == 'D' && borrowing[i]->director == strA &&
        borrowing[i]->title == strB) {
      return borrowing[i];
    }
    if (type == 'C' && borrowing[i]->date == strA &&
        dynamic_cast<Classic *>(borrowing[i])->majorActor == strB) {
      return borrowing[i];
    }
  }
  cerr << "Error: Customer " << customerID
       << " has borrowed no movies with variables " << type << " " << strA
       << " " << strB << "!" << endl;
  return borrowing[0];
}

void Customer::removeMovie(char type, const string &strA, const string &strB) {
  for (int i = 1; i < borrowing.size(); i++) {
    if (type == 'F' && borrowing[i]->title == strA &&
        borrowing[i]->date == strB) {
      borrowing.erase(borrowing.begin() + i);
    }
    if (type == 'D' && borrowing[i]->director == strA &&
        borrowing[i]->title == strB) {
      borrowing.erase(borrowing.begin() + i);
    }
    if (type == 'C' && borrowing[i]->date == strA &&
        dynamic_cast<Classic *>(borrowing[i])->majorActor == strB) {
      borrowing.erase(borrowing.begin() + i);
    }
  }
}