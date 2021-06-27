// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../external/doctest/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>

#include "exampleConfig.h"
#include "vector.hh"
#include "matrix.hh"
#include "handling.hh"
#include "rectangle.hh"
#include "cuboid.hh"
#include "prism.hh"
#include "drone.hh"
#include "environment.hh"
#include "scene.hh"
#include "lacze_do_gnuplota.hh"


#define CUBOID_MODEL_FILE      "../datasets/bryly_wzorcowe/szescian.dat"
#define SPIKY_HILL             "../datasets/bryly_wzorcowe/szescian.dat"
#define PRISM6_MODEL_FILE      "../datasets/bryly_wzorcowe/graniastoslup6.dat"
#define DRONE_BODY_FILE        "../datasets/dat/korpus_drana1.dat"

#define WORK_FILE__DRONE1_BODY    "../datasets/dat/PlikRoboczy_Dron1_Korpus.dat"
#define WORK_FILE__DRONE1_ROTOR1  "../datasets/dat/PlikRoboczy_Dron1_Rotor1.dat"
#define WORK_FILE__DRONE1_ROTOR2  "../datasets/dat/PlikRoboczy_Dron1_Rotor2.dat"
#define WORK_FILE__DRONE1_ROTOR3  "../datasets/dat/PlikRoboczy_Dron1_Rotor3.dat"
#define WORK_FILE__DRONE1_ROTOR4  "../datasets/dat/PlikRoboczy_Dron1_Rotor4.dat"

#define ACTUAL_FILE__DRONE1_BODY    "../datasets/dat/PlikWlasciwy_Dron1_Korpus.dat"
#define ACTUAL_FILE__DRONE1_ROTOR1  "../datasets/dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define ACTUAL_FILE__DRONE1_ROTOR2  "../datasets/dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define ACTUAL_FILE__DRONE1_ROTOR3  "../datasets/dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define ACTUAL_FILE__DRONE1_ROTOR4  "../datasets/dat/PlikWlasciwy_Dron1_Rotor4.dat"

#define ACTUAL_FILE__MOUNTAIN1 "../datasets/dat/gora1.dat"
#define ACTUAL_FILE__MOUNTAIN2  "../datasets/dat/gora2.dat"
#define ACTUAL_FILE__MOUNTAIN3  "../datasets/dat/gora3.dat"
#define ACTUAL_FILE__PLATEAU  "../datasets/dat/plaskowyz1.dat"

#define ROUTE_FILE "../datasets/dat/trasa_przelotu.dat"
#define PLAIN_FILE "../datasets/bryly_wzorcowe/plaszczyzna.dat"


const char *WorkFileNames[7] = {      WORK_FILE__DRONE1_BODY,
                                      WORK_FILE__DRONE1_ROTOR1,
                                      WORK_FILE__DRONE1_ROTOR2,
                                      WORK_FILE__DRONE1_ROTOR3,
                                      WORK_FILE__DRONE1_ROTOR4,
                                      ROUTE_FILE,
                                      nullptr };

const char *ActualFileNames[7] = {  ACTUAL_FILE__DRONE1_BODY,
                                    ACTUAL_FILE__DRONE1_ROTOR1,
                                    ACTUAL_FILE__DRONE1_ROTOR2,
                                    ACTUAL_FILE__DRONE1_ROTOR3,
                                    ACTUAL_FILE__DRONE1_ROTOR4,
                                    ROUTE_FILE,
                                    nullptr };

int main() {

  PzG::LaczeDoGNUPlota  Lacze;
  Scene Main_Scene=Scene();

  //Config Begin--------------------------------
  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
  Lacze.UstawRotacjeXZ(50,250); // Tutaj ustawiany jest widok
  Lacze.DodajNazwePliku(WORK_FILE__DRONE1_BODY);
  Lacze.DodajNazwePliku(WORK_FILE__DRONE1_ROTOR1);
  Lacze.DodajNazwePliku(WORK_FILE__DRONE1_ROTOR2);
  Lacze.DodajNazwePliku(WORK_FILE__DRONE1_ROTOR3);
  Lacze.DodajNazwePliku(WORK_FILE__DRONE1_ROTOR4);
  Lacze.DodajNazwePliku(ROUTE_FILE);
  Lacze.DodajNazwePliku(PLAIN_FILE);
  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 90);
  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

  double ascension[3]={0,0,80};
  Vector3 AscensionVector=Vector3(ascension);
  double descent[3]={0,0,-80};
  Vector3 DescentVector=Vector3(descent);
  //Config End--------------------------------------


  Drone Drone1=Drone();
  Drone1.Create(ActualFileNames);
  Drone1.ChangeFiles(WorkFileNames);

  Main_Scene.AddDrone(Drone1);

//------ Hardwired objects-----
  double arr1[3]={100, 100, 0};
  double arr2[3]={40, 40, 0};
  double arr3[3]={140, 50, 0};
  Vector3 HWired1=Vector3(arr1);
  Vector3 HWired2=Vector3(arr2);
  Vector3 HWired3=Vector3(arr3);

  Plateau HWObj1=Plateau();
  HWObj1.CreatePlateau(ACTUAL_FILE__PLATEAU, HWired1 , Lacze);
  Main_Scene.AddPlateau(HWObj1);

  SpikyHill HWObj2=SpikyHill();
  HWObj2.CreateSpikyHill(ACTUAL_FILE__MOUNTAIN1, HWired2 , Lacze);
  Main_Scene.AddSpikyHill(HWObj2);

  Ridge HWObj3=Ridge();
  HWObj3.CreateRidge(ACTUAL_FILE__MOUNTAIN3, HWired3 , Lacze);
  Main_Scene.AddRidge(HWObj3);
//------End of Hardwired objects-----

  char option;
  std::string obsticle;

  std::cout<<"h for help"<<std::endl;

Menu:

  std::cin>>option;

  std::cin.clear();

  switch (option) {
    case 'a':
    {
      Vector3 Input=Vector3();
      std::cout<<"please specify obsticle type and coordinates"<<std::endl;
      std::cin>>obsticle;
      std::cin.clear();
      std::cin>>Input;
      std::cin.clear();

      if(obsticle=="spiky_hill")
        {
          SpikyHill Object=SpikyHill();
          Object.CreateSpikyHill(ACTUAL_FILE__MOUNTAIN1, Input , Lacze);
          Main_Scene.AddSpikyHill(Object);
        }
      else if(obsticle=="plateau")
        {
          Plateau Object=Plateau();
          Object.CreatePlateau(ACTUAL_FILE__PLATEAU, Input , Lacze);
          Main_Scene.AddPlateau(Object);
        }
      else if(obsticle=="ridge")
        {
          Ridge Object=Ridge();
          Object.CreateRidge(ACTUAL_FILE__MOUNTAIN3, Input , Lacze);
          Main_Scene.AddRidge(Object);
        }
      else
      {
        std::cout<<"Object not recognized!"<<std::endl;
        goto Menu;
      }

      goto Menu;
    }

    case 'f':
    {
      goto Flying;
    }
    case 'p':
    {
      Vector3 Input;

      std::cout<<"Please enter vector for the new path"<<std::endl;
      std::cin>>Input;

      Drone1.ChangeFlightPath(Input);
      Drone1.PlanPath();

      Lacze.Rysuj();
      goto Menu;
    }
    case 'q':
    {
      exit(0);
      goto Menu;
    }

    case 'h':
    {
      std::cout<<"a - Add obsticle to map"<<std::endl;
      std::cout<<"p - Add new path to file"<<std::endl;
      std::cout<<"f - Fly the drone"<<std::endl;
      std::cout<<"q - exit "<<std::endl;

      goto Menu;
    }
  }

Flying:

  Vector3 PathVec=Drone1.PlanPath();

  if(Drone1.IsLandingPossible(Main_Scene) == false)
    exit(0);

  Drone1.AdjustOrientation(Lacze);
  Drone1.Idle(2, Lacze);
  Drone1.DrawVerticalFlight(AscensionVector, Lacze);
  Drone1.Idle(2, Lacze);
  Drone1.DrawHorizontalFlight(PathVec, Lacze);
  Drone1.Idle(2, Lacze);
  Drone1.DrawVerticalFlight(DescentVector, Lacze);


  return 0;
}
