#include "dvdmovie.h"

ComedyFactory strangeComedyFactory;
DramaFactory strangeDramaFactory;
ClassicFactory strangeClassicFactory;

ostream &DVDMovie::print(ostream &out) const {
  out << "Media: " << media << endl;
  out << "Genre: " << genre << endl;
  out << "Title: " << title << endl;
  out << "Director: " << director << endl;
  out << "Release Year: " << date << endl;
  out << "Borrowed Stock: " << maxStock - currStock << endl;
  out << "Remaining Stock: " << currStock << endl;
  return out;
}

ostream &operator<<(ostream &out, const DVDMovie &mov) {
  return mov.print(out);
}

void DVDMovie::rememberType(const char &type, DVDMovieFactory *factory) {
  getFactories().emplace(type, factory);
}

DVDMovie *DVDMovie::create(const char &type) {
  if (getFactories().count(type) > 0) {
    return getFactories().at(type)->create();
  }
  cerr << "Error: No factory exists for " << type << "!" << endl;
  return nullptr;
}

map<char, DVDMovieFactory *> &DVDMovie::getFactories() {
  static map<char, DVDMovieFactory *> factories;
  return factories;
}