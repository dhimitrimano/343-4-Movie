#include "dvdmovie.h"

ClassicFactory::ClassicFactory() { DVDMovie::rememberType('C', this); }

DVDMovie *ClassicFactory::create() const { return new Classic(); }