#pragma once

#include <memory>
#include <list>
#include <vector>

#include "drone.hh"
#include "environment.hh"

class Scene {
  std::list<std::shared_ptr<SceneObject>>  _SceneObjectList;
  std::list<std::shared_ptr<Drone>>        _DroneList;
public:

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


/*bool Drone::IsLandingPossible( const Scene &Current_Scene ) const
{
  for (const std::shared_ptr<ObiektSceny> &Ptr_SceneObjects : Current_Scene.GetSceneObjList()  ) {
    if (&Ptr_SceneObjects == this) continue;
    if (Ptr_SceneObjects.CzyNakladajaSieNaSiebie(GetPosition(),WezPromienObrysu())) {
      if (!Ptr_SceneObjects.IsLandingPossible()) return true;
    }
  }
  return true;
}*/
