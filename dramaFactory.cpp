#include "dvdmovie.h"

DramaFactory::DramaFactory() { DVDMovie::rememberType('D', this); }

DVDMovie *DramaFactory::create() const { return new Drama(); }