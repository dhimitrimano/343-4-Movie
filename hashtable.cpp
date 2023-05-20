#include "hashtable.h"

HashTable::HashTable() {
  hashTable = new HashNode *[buckets];
  for (int i = 0; i < buckets; i++) {
    hashTable[i] = nullptr;
  }
}

int HashTable::getHash(string &num) const {
  return ((num[0] - '0') + (2 * (num[1] - '0')) + (3 * (num[2] - '0')) +
          (4 * (num[3] - '0'))) %
         buckets;
}

bool HashTable::insert(Customer *newCustomer) {
  auto *newNode = new HashNode(newCustomer);
  int index = getHash(newCustomer->customerID);
  HashNode *nod = hashTable[index];
  while (nod != nullptr && nod->next != nullptr) {
    if (nod->val->customerID == newCustomer->customerID) {
      delete newNode;
      return false;
    }
    nod = nod->next;
  }
  if (nod == nullptr) {
    hashTable[index] = newNode;
    return true;
  }
  nod->next = newNode;
  return true;
}

void HashTable::retrieve(string idNumber, Customer *&ret) {
  HashNode *nod = hashTable[getHash(idNumber)];
  while (nod != nullptr) {
    if (nod->val->customerID == idNumber) {
      ret = nod->val;
      return;
    }
    nod = nod->next;
  }
  ret = nullptr;
  cerr << "Error: Customer of ID Number " << idNumber << " doesn't exist!"
       << endl;
}

HashTable::~HashTable() {
  for (int i = 0; i < buckets; i++) {
    if (hashTable[i] != nullptr) {
      HashNode *nod = hashTable[i];
      HashNode *temp;
      while (nod != nullptr) {
        delete nod->val;
        temp = nod->next;
        delete nod;
        nod = temp;
      }
    }
  }
  delete[] hashTable;
}