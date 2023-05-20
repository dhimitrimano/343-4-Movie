#include "dvdmovie.h"

Comedy::Comedy() {
  media = 'D';
  genre = 'F';
}

bool Comedy::operator>(const Comedy *&mov) const {
  if (this->title > mov->title) {
    return true;
  }
  if (this->title == mov->title) {
    if (this->date > mov->date) {
      return true;
    }
  }
  return false;
}

bool Comedy::operator==(const Comedy *&mov) const {
  return this->title == mov->title && this->date == mov->date;
}