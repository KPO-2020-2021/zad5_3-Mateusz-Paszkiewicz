#pragma once

#include <memory>
#include <list>
#include <vector>

#include "environment.hh"
#include "drone.hh"

/*!
*\brief Klasa Scene zawiera listy ze wszystkimi obiektami na scenie
*
*
* Ta klasa za pomoca dwoch list shared_ptr przechowuje wskazniki
* na kazdy obiekt ktory bedzie wyswietlony na scenie
*
*/
class Scene {
  std::list<std::shared_ptr<SceneObject>>  _SceneObjectList;
  std::list<std::shared_ptr<Drone>>        _DroneList;
public:
  friend class Drone;

  const  std::list<std::shared_ptr<SceneObject>> & GetSceneObjList() const
  {
    return _SceneObjectList;
  }

  void AddSpikyHill( SpikyHill &Arg )
  {
   std::shared_ptr Ptr_Mountain = std::make_shared<SceneObject>( Arg );
   _SceneObjectList.push_back(Ptr_Mountain);
  }

  void AddDrone(Drone &Arg)
  {
    std::cout<<"dodano drona"<<std::endl;

    std::shared_ptr  Ptr_Drone = std::make_shared<Drone>( Arg );
    _SceneObjectList.push_back(Ptr_Drone);
    _DroneList.push_back(Ptr_Drone);
  }

  void AddPlateau( Plateau &Arg )
  {
    std::cout<<"dodano plaskowyz"<<std::endl;

   std::shared_ptr Ptr_Mountain = std::make_shared<SceneObject>( Arg );
   _SceneObjectList.push_back(Ptr_Mountain);
  }

  void AddRidge( Ridge &Arg )
  {
   std::shared_ptr Ptr_Mountain = std::make_shared<SceneObject>( Arg );
   _SceneObjectList.push_back(Ptr_Mountain);
  }

};

bool SceneObject::DoDiametersInterfere( double Radius, Vector3 Center )
{
  Vector3 CentersConnected = this->Structure.GetPosition() - Center;
  CentersConnected[2]=0;

  if( Radius+this->GetDiameter() >= CentersConnected.Length())
    return true;
  else
    return false;
}

bool Drone::IsLandingPossible( const Scene &Current_Scene ) const
{
  for (const std::shared_ptr<SceneObject> &Ptr_SceneObjects : Current_Scene.GetSceneObjList()  ) {
    if (Ptr_SceneObjects.get() == this ) continue;
    if (Ptr_SceneObjects->DoDiametersInterfere( const_cast<Drone *>(this)->GetDiameter(), const_cast<Drone *>(this)->Body.GetPosition()+const_cast<Drone *>(this)->PlanPath() )==true)
    {
      std::cout<<"Landing site obstructed! Aborted flight!"<<std::endl;
      return false;
    }
  }
  std::cout<<"Landing site clear, flying..."<<std::endl;
  return true;
}
