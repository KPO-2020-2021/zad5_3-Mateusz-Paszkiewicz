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

  std::cout<<Radius<<" "<<this->GetDiameter()<<std::endl;

  /*std::cout<<Radius+this->GetDiameter()<<std::endl;
  std::cout<<CentersConnected.Length()<<std::endl;*/

  if( Radius+this->GetDiameter() >= CentersConnected.Length())
    return true;
  else
    return false;
}

bool Drone::IsLandingPossible( const Scene &Current_Scene ) const
{
  //std::shared_ptr<SceneObject> WOb=std::make_shared<Drone>(*this);

  for (const std::shared_ptr<SceneObject> &Ptr_SceneObjects : Current_Scene.GetSceneObjList()  ) {
    //SceneObject *tmp=Ptr_SceneObjects.get();
    if (Ptr_SceneObjects.get() == this ) {continue;}
    if (Ptr_SceneObjects->DoDiametersInterfere( const_cast<Drone *>(this)->GetDiameter(), const_cast<Drone *>(this)->Body.GetPosition()+const_cast<Drone *>(this)->PlanPath() )==true)
    {
      std::cout<<"Landing site obstructed! Aborted flight!"<<std::endl;
      return false;
    }
  }
  std::cout<<"Landing site clear, flying..."<<std::endl;
  return true;
}
