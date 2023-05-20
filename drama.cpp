#include "dvdmovie.h"

Drama::Drama() {
  media = 'D';
  genre = 'D';
}

bool Drama::operator>(const Drama *&mov) const {
  if (this->director > mov->director) {
    return true;
  }
  if (this->director == mov->director) {
    if (this->title > mov->title) {
      return true;
    }
  }
  return false;
}

bool Drama::operator==(const Drama *&mov) const {
  return this->director == mov->director && this->title == mov->title;
}