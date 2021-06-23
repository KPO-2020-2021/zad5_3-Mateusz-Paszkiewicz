#include "../include/environment.hh"

int SceneObject::ObjCount=0;

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

double SpikyHill::GetRadius()
{
  double RadiusArr[3] ={(this->Structure(6,0)-this->Structure(5,0))/2,
                        (this->Structure(6,1)-this->Structure(5,1))/2,
                        (this->Structure(6,2)-this->Structure(5,2))/2};

  Vector3 Radius = Vector3(RadiusArr);

  return Radius.Length();
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

  std::cout<<this->Bottom;

  Lacze.DodajNazwePliku(const_name);
  Lacze.Rysuj();

  return (*this);
}

double Plateau::GetRadius()
{
  double RadiusArr[3] ={(this->Structure(6,0)-this->Structure(5,0))/2,
                        (this->Structure(6,1)-this->Structure(5,1))/2,
                        (this->Structure(6,2)-this->Structure(5,2))/2};

  Vector3 Radius = Vector3(RadiusArr);

  return Radius.Length();
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

  std::cout<<this->Bottom;

  Lacze.DodajNazwePliku(const_name);
  Lacze.Rysuj();

  return (*this);
}

double Ridge::GetRadius()
{
  double RadiusArr[3] ={(this->Structure(6,0)-this->Structure(5,0))/2,
                        (this->Structure(6,1)-this->Structure(5,1))/2,
                        (this->Structure(6,2)-this->Structure(5,2))/2};

  Vector3 Radius = Vector3(RadiusArr);

  return Radius.Length();
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
