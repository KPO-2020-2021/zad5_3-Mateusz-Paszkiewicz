#pragma once

#include <chrono>
#include <thread>
#include <cmath>
#include <tgmath.h>
#include <unistd.h>

#include "lacze_do_gnuplota.hh"
#include "handling.hh"
#include "matrix.hh"
#include "cuboid.hh"
#include "prism.hh"
#include "environment.hh"

/*          DRONE CLASS VISUALISATION (i tried xD)
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▄▄▄▄░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░█▀▀▀░░░░▀▄░░░░░░░░░░░░░░░░░░
░░Prism Rotor[2]░░░░░░░░▄█▀░░░░░░░░░░█░░░░░░░░░░░░░░░░░
░░░█▀▀▀▀▀▀█▄░░░░░░░░░░░░░░░░░░░░░░░░░░░▄░Prism Rotor[1]
░░▀░░░░░░░░░▀█░░░░░░░░░▐░░░░░░░░░░░░░░░░▌░░░░░░░░░░░░░░
░▌░░░░░░░░░░░░█░────────█░░░░░░░░░░░░░░░▌░░░░░░░░░░░░░░
░▌░░░░░░░░░░░░░█░░░░░░░░░█░░░░░░░░░░░░▄▄░░░░░░░░░░░░░░░
░░▄░░░░░░░░░░░░▐░░░░░░░░░░░█▄▄░░░░▄▄▄▀░░░░░░░░░░░░░░░░░
░░░█░░░░░░░░░░░█░░░░░░░░░░░░░░▀▀▀▀─┐░░░░░░░░░░░░░░░░░░░
░░░│▀█░░░░░░░░█░░░░░░░░░░░░░░░░░░░░└──┐░░░░░░░░░░░░░░░░
░░░│░░░▀─┐▄▄▀░░░░░░░░░░░░░░░░░░░░░░░░░└─┐░░░░░░░░░░░░░░
░░░│░░░░░└┐░░░░░░░░░░░░░░░░░░░░░░░░░░░░░└─░░░░░░░░░░░░░
░░░│░░░░░░└┐░░░░░░░░░░░░░░░░░░░░░░░░░░░▄█▀▀▀▀▀█▄▄░░░░░░
░░░│░░░░░░░└┐░░░░░░░░░░░░░░░░░░░░░░░▄▀░░░░░░░░░░░▀█▄░░░
░░░│░░░░░░░░└┐░░Prism Rotor[3]░░░░░█░░░░░░░░░░░░░░░░█░░
░░░│░░░░░░░░▄│▄▄▄▄▄▄▄░░░░░░░░░░░░░░▌░░░░░░░░░░░░░░░░░▌░
░░░└┐░░░░░░░▄█▀▀▀░░░░▀▀▄░░░░░░░░░░░█░░Prism Rotor[0]░▌░
░░░░└┐░░░░▐▀░░░░░░░░░░░░▀█░░░░░░░░░░█░░░░░░░░░░░░░░░█░░
░░░░░└┐░░░▌░░░░░░░░░░░░░░░█░░░░░░░░░░▀▄▄░░░░░░░░░░░█│░░
░░░░░░│░░░▌░░░░░░░░░░░░░░░▐░░░░┌────────░▀▀▀▀▀▀▀▀▀▀░│░░
░░░░░░└┐░░▌░░░░░░░░░░░░░░░▐────┘░░░░░░░░░░░░░░░░░░░░│░░
░░░░░░░└┐░▀▄░░░░░░░░░░░░░░▀░░░░░░░░░░░░░░░░░░░░░░░░░│░░
░░░░░░░░│░░░█▄░░░░░░░░░░▄▀░░░░░░░░░░░░░░░░░░░░░░░░░░│░░
░░░░░░░░└┐░░░░▀▀▀▀▀▀▀▀▀▀░░░░░░░░░░░░░░░░░░░░░░░░░░░░│░░
░░░░░░░░░└┐░░░░┌─░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░│░░
░░░░░░░░░░└┐░░░│░░░░░░░░░░░░░░░░Cuboid Body░░░░░░░░░│░░
░░░░░░░░░░░│░░░│░░░░░░░░░░░░░░░░░░░░░░░░░░░░┌───────┴░░
░░░░░░░░░░░└─┐░│░░░░░░░░░░░░░░░░░┌──────────┘░░░░░░░░░░
░░░░░░░░░░░░░└─┤░░░░░┌───────────┘░░░░░░░░░░░░░░░░░░░░░
*/

class Scene;  //Declaration of Scene class so the compiler knows it's coming

class Drone : public SceneObject, Cuboid, Prism{
private:
  Cuboid Body;
  Prism Rotor[4];
  Vector3 Position;
  Vector3 Orientation;

  char *File_Names[6];
public:

  Drone Create(const char*[7]);

  Drone ChangeFiles(const char**);

  Drone Displacement(Vector3);

  void UpdateFiles();

  Vector3 PlanPath();

  bool SpinRotors(double);

  Vector3 FindOrientation();

  bool AdjustOrientation(PzG::LaczeDoGNUPlota);

  bool Idle(float, PzG::LaczeDoGNUPlota);

  bool DrawDroneRotation(double, PzG::LaczeDoGNUPlota);

  bool DrawVerticalFlight(Vector3, PzG::LaczeDoGNUPlota);

  bool DrawHorizontalFlight(Vector3, PzG::LaczeDoGNUPlota);

  double GetRadius();

  bool IsLandingPossible( const Scene & ) const;

};
