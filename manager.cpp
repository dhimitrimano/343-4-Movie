#include "manager.h"

Manager::Manager(vector<string> vec) {
  for (int i = 0; i < vec.size(); i += 3) {
    createStore(vec[i], vec[i + 1], vec[i + 2]);
  }
}

Manager::~Manager() {
  for (auto &i : stores) {
    delete i;
  }
}

void Manager::createStore(const string &a, const string &b, const string &c) {
  stores.emplace_back(new MovieStore(a, b, c));
}