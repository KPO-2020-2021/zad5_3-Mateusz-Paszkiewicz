#pragma once

#include <memory>
#include <list>
#include <vector>

#include "environment.hh"
#include "drone.hh"

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
    std::shared_ptr  Ptr_Drone = std::make_shared<Drone>( Arg );
    _SceneObjectList.push_back(Ptr_Drone);
    _DroneList.push_back(Ptr_Drone);
  }

  void AddPlateau( Plateau &Arg )
  {
   std::shared_ptr Ptr_Mountain = std::make_shared<SceneObject>( Arg );
   _SceneObjectList.push_back(Ptr_Mountain);
  }

  void AddRidge( Ridge &Arg )
  {
   std::shared_ptr Ptr_Mountain = std::make_shared<SceneObject>( Arg );
   _SceneObjectList.push_back(Ptr_Mountain);
  }

};

bool SceneObject::DoDiametersInterfere( SceneObject Bandit )
{
  Vector3 CentersConnected = this->Structure.GetPosition() - Bandit.Structure.GetPosition();

  if( Bandit.GetDiameter()+this->GetDiameter() > CentersConnected.Length())
    return false;
  else
    return true;
}

bool Drone::IsLandingPossible( const Scene &Current_Scene ) const
{
  std::shared_ptr<SceneObject> WOb=std::make_shared<Drone>(*this);

  for (const std::shared_ptr<SceneObject> &Ptr_SceneObjects : Current_Scene.GetSceneObjList()  ) {
    SceneObject *tmp=Ptr_SceneObjects.get();
    if ( &Ptr_SceneObjects == &WOb ) continue;
    if (Ptr_SceneObjects->DoDiametersInterfere(*tmp)){
      std::cout<<"Landing site obstructed! Aborted flight!"<<std::endl;
      return false;
    }
  }
  std::cout<<"Landing site clear, flying..."<<std::endl;
  return true;
}
