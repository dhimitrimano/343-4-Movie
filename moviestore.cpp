#include "moviestore.h"

MovieStore::MovieStore(const string &customersInput, const string &moviesInput,
                       const string &commandsInput) {
  string str;
  ifstream inputA(customersInput);
  if (inputA) {
    while (getline(inputA, str)) {
      customerQueue.push(str);
    }
    processCustomerData();
  } else {
    cerr << "Error: Invalid filename " << customersInput << "!" << endl;
  }
  ifstream inputB(moviesInput);
  if (inputB) {
    while (getline(inputB, str)) {
      movieQueue.push(str);
    }
    processMovieData();
  } else {
    cerr << "Error: Invalid filename " << moviesInput << "!" << endl;
  }
  ifstream inputC(commandsInput);
  if (inputC) {
    while (getline(inputC, str)) {
      commandQueue.push(str);
    }
    processCommands();
  } else {
    cerr << "Error: Invalid filename " << commandsInput << "!" << endl;
  }
}

string MovieStore::subStringUntilChar(string &str, int &start, char ch) {
  string ret;
  for (int i = start; i < str.size(); i++) {
    if (str[i] == ch) {
      start += 1;
      return ret;
    }
    ret += str[i];
    start += 1;
  }
  return ret;
}

void MovieStore::processCustomerData() {
  string idNumber;
  string lastN;
  string firstN;
  int index{0};
  while (!customerQueue.empty()) {
    index = 5;
    idNumber = customerQueue.front().substr(0, 4);
    // clang-format demanded this comment to exist to stop its loop
    lastN = subStringUntilChar(customerQueue.front(), index, ' ');
    firstN = customerQueue.front().substr(index);
    customers.insert(new Customer(idNumber, lastN, firstN));
    customerQueue.pop();
  }
}

void MovieStore::processDramedyDVDMovie(string &str) {
  int index{3};
  DVDMovie *newMov = DVDMovie::create(str[0]);
  newMov->maxStock = stoi(subStringUntilChar(str, index, ','));
  newMov->currStock = newMov->maxStock;
  index += 1;
  newMov->director = subStringUntilChar(str, index, ',');
  index += 1;
  newMov->title = subStringUntilChar(str, index, ',');
  index += 1;
  newMov->date = str.substr(index);
  movies['D'].insert(newMov);
}

void MovieStore::processClassicDVDMovie(string &str) {
  int index{3};
  auto *newMov = dynamic_cast<Classic *>(DVDMovie::create(str[0]));
  newMov->maxStock = stoi(subStringUntilChar(str, index, ','));
  newMov->currStock = newMov->maxStock;
  index += 1;
  newMov->director = subStringUntilChar(str, index, ',');
  index += 1;
  newMov->title = subStringUntilChar(str, index, ',');
  index += 1;
  newMov->majorActor = subStringUntilChar(str, index, ' ');
  newMov->majorActor += ' ';
  newMov->majorActor.append(subStringUntilChar(str, index, ' '));
  string date = subStringUntilChar(str, index, ' ');
  if (date.size() == 1) {
    date = '0' + date;
  }
  string yearN = subStringUntilChar(str, index, ' ');
  yearN += " ";
  yearN.append(date);
  newMov->date = yearN;
  cout << newMov->date << " yo!!" << endl;
  movies['D'].insert(newMov);
}

void MovieStore::processMovieData() {
  while (!movieQueue.empty()) {
    char mediaN = 'D'; // no other option
    char genreN = movieQueue.front()[0];
    if (mediaN == 'D') {
      if (genreN == 'F' || genreN == 'D') {
        processDramedyDVDMovie(movieQueue.front());
      } else if (genreN == 'C') {
        processClassicDVDMovie(movieQueue.front());
      } else {
        cerr << "Error: Genre " << genreN << " doesn't exist!" << endl;
      }
    } else {
      cerr << "Error: Media type " << mediaN << " doesn't exist!" << endl;
    }
    movieQueue.pop();
  }
}

void MovieStore::processComedyDVDMovieTransaction(string &str,
                                                  Customer *&customer) {
  int index{11};
  Transaction *transact = Transaction::create(str[0]);
  string titleN = subStringUntilChar(str, index, ',');
  string yearN = str.substr(index + 1);
  DVDMovie *mov = nullptr;
  movies['D'].retrieve(str[9], titleN, yearN, mov);
  if (mov != nullptr) {
    if (transact->transactionType == 'B') {
      if (mov->currStock > 0) {
        transact->movie = mov;
        mov->currStock -= 1;
        customer->borrowing.emplace_back(mov);
        customer->history.push_back(transact);
      } else {
        delete transact;
        cerr << "Error: No stock left for movie " << str[0] << " " << titleN
             << " " << yearN << "!" << endl;
      }
    } else if (transact->transactionType == 'R') {
      DVDMovie *customerMov = customer->getMovie(str[9], titleN, yearN);
      if (mov == customerMov) {
        customer->removeMovie(str[9], titleN, yearN);
        transact->movie = mov;
        mov->currStock += 1;
        customer->history.push_back(transact);
      }
    }
  } else {
    delete transact;
    cerr << "Error: Comedy movie " << titleN << " " << yearN
         << " doesn't exist!" << endl;
  }
}

void MovieStore::processDramaDVDMovieTransaction(string &str,
                                                 Customer *&customer) {
  int index{11};
  Transaction *transact = Transaction::create(str[0]);
  string directorN = subStringUntilChar(str, index, ',');
  index += 1;
  string titleN = subStringUntilChar(str, index, ',');
  DVDMovie *mov = nullptr;
  movies['D'].retrieve(str[9], directorN, titleN, mov);
  if (mov != nullptr) {
    if (transact->transactionType == 'B') {
      if (mov->currStock > 0) {
        transact->movie = mov;
        mov->currStock -= 1;
        customer->borrowing.emplace_back(mov);
        customer->history.push_back(transact);
      } else {
        delete transact;
        cerr << "Error: No stock left for movie " << str[0] << " " << directorN
             << " " << titleN << "!" << endl;
      }
    } else if (transact->transactionType == 'R') {
      DVDMovie *customerMov = customer->getMovie(str[9], directorN, titleN);
      if (mov == customerMov) {
        customer->removeMovie(str[9], directorN, titleN);
        transact->movie = mov;
        mov->currStock += 1;
        customer->history.push_back(transact);
      }
    }
  } else {
    delete transact;
    cerr << "Error: Drama movie " << directorN << " " << titleN
         << " doesn't exist!" << endl;
  }
}

void MovieStore::processClassicDVDMovieTransaction(string &str,
                                                   Customer *&customer) {
  int index{11};
  Transaction *transact = Transaction::create(str[0]);
  string date = subStringUntilChar(str, index, ' ');
  if (date.size() == 1) {
    date = '0' + date;
  }
  string yearN = subStringUntilChar(str, index, ' ');
  yearN += " ";
  yearN.append(date);
  string majorActorN = str.substr(index);
  DVDMovie *mov = nullptr;
  movies['D'].retrieve(str[9], yearN, majorActorN, mov);
  if (mov != nullptr) {
    if (transact->transactionType == 'B') {
      if (mov->currStock > 0) {
        transact->movie = mov;
        mov->currStock -= 1;
        customer->borrowing.emplace_back(mov);
        customer->history.push_back(transact);
      } else {
        delete transact;
        cerr << "Error: No stock left for movie " << str[0] << " " << yearN
             << " " << majorActorN << "!" << endl;
      }
    } else if (transact->transactionType == 'R') {
      DVDMovie *customerMov = customer->getMovie(str[9], yearN, majorActorN);
      if (mov == customerMov) {
        customer->removeMovie(str[9], yearN, majorActorN);
        transact->movie = mov;
        mov->currStock += 1;
        customer->history.push_back(transact);
      }
    }
  } else {
    delete transact;
    cerr << "Error: Classic movie " << yearN << " " << majorActorN
         << " doesn't exist!" << endl;
  }
}

void MovieStore::processTransaction(string &str) {
  char mediaN = str[7];
  char genreN = str[9];
  Customer *cus = nullptr;
  customers.retrieve(str.substr(2, 4), cus);
  if (cus != nullptr) {
    if (mediaN == 'D') {
      if (genreN == 'F') {
        processComedyDVDMovieTransaction(str, cus);
      } else if (genreN == 'D') {
        processDramaDVDMovieTransaction(str, cus);
      } else if (genreN == 'C') {
        processClassicDVDMovieTransaction(str, cus);
      } else {
        cerr << "Error: Genre " << genreN << " doesn't exist!" << endl;
      }
    } else {
      cerr << "Error: Media type " << mediaN << " doesn't exist!" << endl;
    }
  } else {
    delete cus;
  }
}

void MovieStore::processCommands() {
  while (!commandQueue.empty()) {
    char command = commandQueue.front()[0];
    if (command == 'B' || command == 'R') {
      processTransaction(commandQueue.front());
    } else if (command == 'I') {
      cout << "Printing inventory!" << endl;
      movies['D'].display('F');
      movies['D'].display('D');
      movies['D'].display('C');
    } else if (command == 'H') {
      Customer *cus;
      customers.retrieve(commandQueue.front().substr(2, 4), cus);
      if (cus != nullptr) {
        cout << "Printing history for " << cus->customerID << "!" << endl;
        for (auto &i : cus->history) {
          cout << *i << endl;
        }
      }
    } else {
      cerr << "Error: No command " << command << " exists!" << endl;
    }
    commandQueue.pop();
  }
}