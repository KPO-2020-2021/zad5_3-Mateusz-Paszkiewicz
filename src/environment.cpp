#include "../include/environment.hh"

int SceneObject::ObjCount=0;

double SceneObject::GetDiameter()
{
  return ( this->Structure.GetPosition() - this->Structure(0) ).Length() ;
}

SpikyHill SpikyHill::CreateSpikyHill(const char *File_Name, Vector3 StartPoint , PzG::LaczeDoGNUPlota Lacze)
{
  ++this->ObjCount;

  std::string name="../datasets/dat/object";
  name += std::to_string(this->ObjCount);
  name+=".dat";
  const char *const_name=name.c_str();

  CoordsReadFromFile(File_Name, this->Structure);

  double BottomArr[3]={this->Structure.GetPosition()[0] + (this->Structure(6,0)-this->Structure(0,0))/2,
                       this->Structure.GetPosition()[1] + (this->Structure(6,1)-this->Structure(0,1))/2,
                       this->Structure.GetPosition()[2] + (this->Structure(6,2)-this->Structure(0,2))/2,};
  Vector3 Tmp = Vector3(BottomArr);

  this->Bottom=Tmp;

  (*this)=(*this)-Tmp+StartPoint;

  SaveCoordsToFile(const_name, this->Structure);

  Lacze.DodajNazwePliku(const_name);
  Lacze.Rysuj();

  return (*this);
}

SpikyHill SpikyHill:: operator + (Vector3 &tmp)
{
  this->Structure = this->Structure + tmp;
  this->Bottom = this->Bottom + tmp;

  return (*this);
}

SpikyHill SpikyHill:: operator - (Vector3 &tmp)
{
  this->Structure = this->Structure - tmp;
  this->Bottom = this->Bottom - tmp;

  return (*this);
}

Plateau Plateau::CreatePlateau(const char *File_Name, Vector3 StartPoint , PzG::LaczeDoGNUPlota Lacze)
{
  ++this->ObjCount;

  std::string name="../datasets/dat/object";
  name += std::to_string(this->ObjCount);
  name +=".dat";
  const char *const_name=name.c_str();


  CoordsReadFromFile(File_Name, this->Structure);

  double BottomArr[3]={this->Structure.GetPosition()[0] + (this->Structure(6,0)-this->Structure(0,0))/2,
                       this->Structure.GetPosition()[1] + (this->Structure(6,1)-this->Structure(0,1))/2,
                       this->Structure.GetPosition()[2] + (this->Structure(6,2)-this->Structure(0,2))/2};
  Vector3 Tmp = Vector3(BottomArr);

  this->Bottom=Tmp;

  (*this)=(*this)-Tmp+StartPoint;

  SaveCoordsToFile(const_name, this->Structure);

  Lacze.DodajNazwePliku(const_name);
  Lacze.Rysuj();

  return (*this);
}

Plateau Plateau:: operator + (Vector3 &tmp)
{
  this->Structure = this->Structure + tmp;
  this->Bottom = this->Bottom + tmp;

  return (*this);
}

Plateau Plateau:: operator - (Vector3 &tmp)
{
  this->Structure = this->Structure - tmp;
  this->Bottom = this->Bottom - tmp;

  return (*this);
}

Ridge Ridge::CreateRidge(const char *File_Name, Vector3 StartPoint , PzG::LaczeDoGNUPlota Lacze)
{
  ++this->ObjCount;

  std::string name="../datasets/dat/object";
  name += std::to_string(this->ObjCount);
  name +=".dat";
  const char *const_name=name.c_str();


  CoordsReadFromFile(File_Name, this->Structure);

  double BottomArr[3]={this->Structure.GetPosition()[0] + (this->Structure(6,0)-this->Structure(0,0))/2,
                       this->Structure.GetPosition()[1] + (this->Structure(6,1)-this->Structure(0,1))/2,
                       this->Structure.GetPosition()[2] + (this->Structure(6,2)-this->Structure(0,2))/2};
  Vector3 Tmp = Vector3(BottomArr);

  this->Bottom=Tmp;

  (*this)=(*this)-Tmp+StartPoint;

  SaveCoordsToFile(const_name, this->Structure);

  Lacze.DodajNazwePliku(const_name);
  Lacze.Rysuj();

  return (*this);
}

Ridge Ridge:: operator + (Vector3 &tmp)
{
  this->Structure = this->Structure + tmp;
  this->Bottom = this->Bottom + tmp;

  return (*this);
}

Ridge Ridge:: operator - (Vector3 &tmp)
{
  this->Structure = this->Structure - tmp;
  this->Bottom = this->Bottom - tmp;

  return (*this);
}
