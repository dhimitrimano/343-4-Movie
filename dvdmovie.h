#pragma once
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class DVDMovie;

class DVDMovieFactory {
public:
  // virtual to build the DVDMovie
  virtual DVDMovie *create() const = 0;
};

class DVDMovie {
  // for cout
  friend ostream &operator<<(ostream &out, const DVDMovie &mov);

  // also for cout, but it works with overloading
  virtual ostream &print(std::ostream &out) const;

public:
  // virtual destructor for virtual class
  virtual ~DVDMovie() = default;

  // remembers the different types of factories
  static void rememberType(const char &type, DVDMovieFactory *factory);

  // creates a DVDMovie
  static DVDMovie *create(const char &type);

protected:
  // the date of the DVDMovie's release
  string date;

  // the title of the DVDMovie
  string title;

  // the director of the DVDMovie
  string director;

  // the max stock of the DVDMovie
  int maxStock;

  // the current stock of the DVDMovie
  int currStock;

  // the genre of the DVDMovie, denoted by one letter
  char genre;

  // the media type of the DVDMovie, denoted by one letter
  char media;

private:
  // factory list
  static map<char, DVDMovieFactory *> &getFactories();

  friend class MovieStore;

  friend class Inventory;

  friend class Customer;
};

class Comedy : public DVDMovie {
public:
  // returns true if this is higher than mov
  bool operator>(const Comedy *&mov) const;

  // returns true if this is equal to mov
  bool operator==(const Comedy *&mov) const;

private:
  // the constructor
  explicit Comedy();

  // for corresponding factory to access it
  friend class ComedyFactory;

  friend class MovieStore;

  friend class Inventory;

  friend class Customer;
};

class Drama : public DVDMovie {
public:
  // returns true if this is higher than mov
  bool operator>(const Drama *&mov) const;

  // returns true if this is equal to mov
  bool operator==(const Drama *&mov) const;

private:
  // the constructor
  explicit Drama();

  // for corresponding factory to access it
  friend class DramaFactory;

  friend class MovieStore;

  friend class Inventory;

  friend class Customer;
};

class Classic : public DVDMovie {
public:
  // returns true if this is higher than mov
  bool operator>(const Classic *&mov) const;

  // returns true if this is equal to mov
  bool operator==(const Classic *&mov) const;

  // for cout
  friend ostream &operator<<(ostream &out, const Classic &cla);

  // also for cout, but it works with overloading
  ostream &print(std::ostream &out) const override;

private:
  // the major actor of the classic
  string majorActor;

  // the month of release
  int month;
  
  // the constructor
  explicit Classic();

  // for corresponding factory to access it
  friend class ClassicFactory;

  friend class MovieStore;

  friend class Inventory;

  friend class Customer;
};

class ComedyFactory : public DVDMovieFactory {
public:
  // the constructor
  ComedyFactory();

  // overrided create function that returns a comedy movie
  DVDMovie *create() const override;
};

class DramaFactory : public DVDMovieFactory {
public:
  // the constructor
  DramaFactory();

  // overrided create function that returns a drama movie
  DVDMovie *create() const override;
};

class ClassicFactory : public DVDMovieFactory {
public:
  // the constructor
  ClassicFactory();

  // overrided create function that returns a classic movie
  DVDMovie *create() const override;
};

//  Comedy (‘F’) sorted by Title, then Year it released 
//  Dramas (‘D’) are sorted by Director, then Title 
//  Classics (‘C’) are sorted by Release date, then Major actor

//  Comedy: F, Stock, Director, Title, Year it released 
//  Drama: D, Stock, Director, Title, Year it released
//  Classics: C, Stock, Director, Title, Major actor Release date
