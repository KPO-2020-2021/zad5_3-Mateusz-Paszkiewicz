#pragma once

#include"matrix.hh"

//    CUBOID OBJECT :
//
//    point[punkt][0]=x_punktu
//    point[punkt][1]=y_punktu
//    point[punkt][2]=z_punktu
//
//        *------------* 4
//      / | 6        / |
//    *------------* 5 |
//    | 7 | 0      |   |
//    |   *--------|---* 2
//    | / 1        | /
//    *------------* 3
//


/*!
*\brief Klasa prostopadloscianu w postaci tablicy dwuwymiarowej
* oraz jej metody.
*
*
* Klasa prostopadloscianu w postaci tablicy 8x3 gdzie kazdy
* kazdy z rzedow jest zestawem punktow x, y ,z oraz metody i funkcje
* potrzebne do zrealizowania obrotow 3D.
*
*/
class Cuboid{
private:
  double point[8][3];
  Vector3 Position;
public:

  Cuboid();

  Cuboid(double [8][3]);

  Cuboid operator * (Matrix3x3 &);

  Cuboid operator + (Vector3 &);

  Cuboid operator - (Vector3 &);

  const double &operator () (unsigned int, unsigned int) const;

  double &operator () (unsigned int, unsigned int);

  Cuboid AngleTrans(double Angle, char axis);

  Vector3 GetPosition();

  friend class Drone;
};
