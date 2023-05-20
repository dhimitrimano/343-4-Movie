#include "dvdmovie.h"

ComedyFactory::ComedyFactory() { DVDMovie::rememberType('F', this); }

DVDMovie *ComedyFactory::create() const { return new Comedy(); }