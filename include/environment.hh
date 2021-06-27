#pragma once

#include <string>
#include <charconv>

#include "vector.hh"
#include "cuboid.hh"
#include "handling.hh"
#include "lacze_do_gnuplota.hh"

class Drone;
class Scene;

class SceneObject{
private:
  Cuboid Structure;

  static int ObjCount;
public:
  friend class SpikyHill;
  friend class Plateau;
  friend class Ridge;

  virtual double GetDiameter();

  bool DoDiametersInterfere(double, Vector3);


  friend class Drone;
};



class SpikyHill : public SceneObject {
  Vector3 Bottom;
public:
  SpikyHill CreateSpikyHill(const char *, Vector3 StartPoint ,PzG::LaczeDoGNUPlota);

  SpikyHill operator + (Vector3 &tmp);

  SpikyHill operator - (Vector3 &tmp);
};


class Plateau : public SceneObject {
  Vector3 Bottom;
public:
  Plateau CreatePlateau(const char *, Vector3 StartPoint , PzG::LaczeDoGNUPlota);

  Plateau operator + (Vector3 &tmp);

  Plateau operator - (Vector3 &tmp);
};

class Ridge : public SceneObject {
  Vector3 Bottom;
public:
  Ridge CreateRidge(const char *, Vector3 StartPoint , PzG::LaczeDoGNUPlota);

  Ridge operator + (Vector3 &tmp);

  Ridge operator - (Vector3 &tmp);
};
