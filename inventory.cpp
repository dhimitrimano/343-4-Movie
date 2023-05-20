#include "inventory.h"

Inventory::~Inventory() {
  for (auto &i : inventory) {
    for (auto &v : i.second) {
      delete v;
    }
  }
}

bool Inventory::compareDF(DVDMovie *mov1, DVDMovie *mov2) {
  if (mov1->title < mov2->title) {
    return true;
  }
  if (mov1->title == mov2->title) {
    if (mov1->date < mov2->date) {
      return true;
    }
  }
  return false;
}

bool Inventory::compareDD(DVDMovie *mov1, DVDMovie *mov2) {
  if (mov1->director < mov2->director) {
    return true;
  }
  if (mov1->director == mov2->director) {
    if (mov1->title < mov2->title) {
      return true;
    }
  }
  return false;
}

bool Inventory::compareDC(DVDMovie *mov1, DVDMovie *mov2) {
  if (mov1->date < mov2->date) {
    return true;
  }
  if (mov1->date == mov2->date) {
    if (dynamic_cast<Classic *>(mov1)->majorActor <
        dynamic_cast<Classic *>(mov2)->majorActor) {
      return true;
    }
  }
  return false;
}

bool Inventory::insert(DVDMovie *mov) {
  if (inventory.count(mov->genre) == 0) {
    vector<DVDMovie *> temp;
    inventory.insert(pair<char, vector<DVDMovie *>>(mov->genre, temp));
  }
  for (int i = 0; i < inventory[mov->genre].size(); i++) {
    if (mov->genre == 'F' && compareDF(mov, inventory[mov->genre][i])) {
      inventory[mov->genre].insert(inventory[mov->genre].begin() + i, mov);
    }
    if (mov->genre == 'D' && compareDD(mov, inventory[mov->genre][i])) {
      inventory[mov->genre].insert(inventory[mov->genre].begin() + i, mov);
    }
    if (mov->genre == 'C' && compareDC(mov, inventory[mov->genre][i])) {
      inventory[mov->genre].insert(inventory[mov->genre].begin() + i, mov);
    }
    if (inventory[mov->genre][i] == mov) {
      cerr << "Error: Movie " << endl
           << *mov << endl
           << "already exists!" << endl;
      return false;
    }
  }
  inventory[mov->genre].insert(inventory[mov->genre].end(), mov);
  return true;
}

void Inventory::retrieve(char type, const string &strA, const string &strB,
                         DVDMovie *&mov) {
  for (int i = 0; i < inventory[type].size(); i++) {
    if (type == 'F' && inventory[type][i]->title == strA &&
        inventory[type][i]->date == strB) {
      mov = inventory[type][i];
      return;
    }
    if (type == 'D' && inventory[type][i]->director == strA &&
        inventory[type][i]->title == strB) {
      mov = inventory[type][i];
      return;
    }
    if (type == 'C' && inventory[type][i]->date == strA &&
        dynamic_cast<Classic *>(inventory[type][i])->majorActor == strB) {
      mov = inventory[type][i];
      return;
    }
  }
  cerr << "Error: No movie exists with variables " << type << " " << strA << " "
       << strB << "!" << endl;
}

void Inventory::display(char ch) {
  for (auto &j : inventory[ch]) {
    cout << *j << endl << endl;
  }
}