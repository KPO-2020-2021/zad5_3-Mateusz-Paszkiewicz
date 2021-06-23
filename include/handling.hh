#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <limits>

#include"rectangle.hh"
#include"vector.hh"
#include"cuboid.hh"
#include"prism.hh"

bool CoordsReadFromFile(const char *, Rectangle &);

bool CoordsReadFromFile(const char *, Cuboid &);

void CoordsToStream(std::ostream&, Rectangle &);

void CoordsToStream(std::ostream&, Cuboid &);

bool SaveCoordsToFile( const char *,  Rectangle &);

bool SaveCoordsToFile( const char *,  Cuboid &);

bool CoordsReadFromFile(const char *, Prism &);

void CoordsToStream(std::ostream&, Prism &);

bool SaveCoordsToFile( const char *,  Prism &);
