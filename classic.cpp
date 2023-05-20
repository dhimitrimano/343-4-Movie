#include "dvdmovie.h"

Classic::Classic() {
  media = 'D';
  genre = 'C';
}

bool Classic::operator>(const Classic *&mov) const {
  if (this->date > mov->date) {
    return true;
  }
  if (this->date == mov->date) {
    if (this->majorActor > mov->majorActor) {
      return true;
    }
  }
  return false;
}

bool Classic::operator==(const Classic *&mov) const {
  return this->date == mov->date && this->majorActor == mov->majorActor;
}

ostream &Classic::print(ostream &out) const {
  out << "Media: " << media << endl;
  out << "Genre: " << genre << endl;
  out << "Title: " << title << endl;
  out << "Major Actor: " << majorActor << endl;
  out << "Director: " << director << endl;
  out << "Release Year: " << date << endl;
  out << "Borrowed Stock: " << maxStock - currStock << endl;
  out << "Remaining Stock: " << currStock << endl;
  return out;
}