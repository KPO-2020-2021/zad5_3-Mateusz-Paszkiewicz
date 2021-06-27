#include "../include/drone.hh"

#define TIME_UNIT 10.00 //in miliseconds
#define TIME_UNIT_INT 10
#define MAX_HEIGHT 80
#define VELOCITY 30   //Units per second
#define ROTATION_VELOCITY 25*M_PI/180


/*!
 * Funckja czytajaca z plikow dane dla drona
*
*\param[in] const char* File_Names[7] to tablica 7 const charow gdzie
* - 1 nazwa pliku korpusu drona
* - 4 nazwy plikow rotorow
* - 1 nazwa trasy przelotu
* - nullptr
*\retval dron BEZ przydzielonych plikow, z danymi przydzielonymi do odpowiednich pol
*/
Drone Drone::Create(const char* File_Names[7])
{
  CoordsReadFromFile(File_Names[0], this->Body);
  CoordsReadFromFile(File_Names[1], this->Rotor[0]);
  CoordsReadFromFile(File_Names[2], this->Rotor[1]);
  CoordsReadFromFile(File_Names[3], this->Rotor[2]);
  CoordsReadFromFile(File_Names[4], this->Rotor[3]);

  return (*this);
}

/*!
 * Funckja zmieniajaca aktualnie wpisane pliki dronow
*
*\param[in] const char* File_Names[7] to tablica 7 const charow gdzie
* - 1 nazwa pliku korpusu drona
* - 4 nazwy plikow rotorow
* - 1 nazwa trasy przelotu
* - nullptr
*\retval dron z przydzielonymi plikami
*/
Drone Drone::ChangeFiles(const char* File_Names[7])
{
  this->File_Names[0]=const_cast <char *>(File_Names[0]);
  this->File_Names[1]=const_cast <char *>(File_Names[1]);
  this->File_Names[2]=const_cast <char *>(File_Names[2]);
  this->File_Names[3]=const_cast <char *>(File_Names[3]);
  this->File_Names[4]=const_cast <char *>(File_Names[4]);
  this->File_Names[5]=const_cast <char *>(File_Names[5]);
  this->File_Names[6]=const_cast <char *>(File_Names[6]);

  return (*this);
}

/*!
* Funckja zapisuje aktualnie znajdujace sie w klasie dron dane do plikow
*
*/
void Drone::UpdateFiles()
{
  SaveCoordsToFile(this->File_Names[0],     this->Body);
  SaveCoordsToFile(this->File_Names[1], this->Rotor[0]);
  SaveCoordsToFile(this->File_Names[2], this->Rotor[1]);
  SaveCoordsToFile(this->File_Names[3], this->Rotor[2]);
  SaveCoordsToFile(this->File_Names[4], this->Rotor[3]);
}


/*!
 * Funkcja realizujaca lot drona po linii prostej o jakis wektor
*
*\param[in] Vector3 Trans - wektor o ktory przesuniety zostanie dron
*\retval przesuniety dron o wektor Trans
*/
Drone Drone::Displacement(Vector3 Trans)
{
  (*this).Body=(*this).Body+Trans;
  (*this).Position=(*this).Position+Trans;

  for(int i=0; i<4; i++)
    (*this).Rotor[i]=(*this).Rotor[i]+Trans;

  return (*this);
}

/*!
 * Funckja planujaca trase drona czytajac z pliku o nazwie zapisanej w klasie
* liczy wektor trasy
*
*\retval Wektor o ktory powinien sie poruszyc dron (calosciowo)
*/
Vector3 Drone::PlanPath()
{
  Vector3 PathCoordsVecStart=Vector3();
  Vector3 PathCoordsVecFinish=Vector3();

  std::ifstream  fin;

  if(this->File_Names[5]==nullptr){
    std::cout<<"No file name!"<<std::endl;
    return 0;
  }


  fin.open(this->File_Names[5]);
  if (!fin.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << this->File_Names[5] << "\"" << std::endl
   << ":(  nie powiodla sie." << std::endl;
    return 0;
    }

 fin.ignore(1000,'\n');

 fin>>PathCoordsVecStart[0]; fin>>PathCoordsVecStart[1]; fin>>PathCoordsVecStart[2];
 fin>>PathCoordsVecFinish[0]; fin>>PathCoordsVecFinish[1]; fin>>PathCoordsVecFinish[2];

 fin.close();

 return PathCoordsVecFinish-PathCoordsVecStart;
}


/*!
* Funkcja obracajaca rotorki o jakis zadany konkretny kat
*
*\param[in] Angle - kat do obrotu
*\retval dron z obroconymi rotorami
*/
bool Drone::SpinRotors(double Angle)
{
  Vector3 CurrentRotorPosition[4];

  for(int i=0; i<4; i++){
      CurrentRotorPosition[i]=this->Rotor[i].GetPosition();
    }

  for(int i=0; i<4; i++){
      this->Rotor[i]=this->Rotor[i]-CurrentRotorPosition[i];
    }

  for(int i=0; i<4; i++){
      this->Rotor[i].AngleTrans(Angle,'z');
    }

  for(int i=0; i<4; i++){
      this->Rotor[i]=this->Rotor[i]+CurrentRotorPosition[i];
    }

      return 1;
}

/*!
* Funkcja znajdujaca kat orientacji w przestrzeni
*
*
*\retval wektor jednostokwy celujacy do przadu od srodka drona
*/
Vector3 Drone::FindOrientation()
{
  double FrontPlateArr[3]={this->Body(0,0)-(this->Body(0,0)-this->Body(4,0))/2,
                           this->Body(0,1)-(this->Body(0,1)-this->Body(4,1))/2,
                           this->Body(0,2)-(this->Body(0,2)-this->Body(4,2))/2};

  Vector3 OrientationUnitVector=Vector3();
  Vector3 MidOfFrontalPlateVector=Vector3(FrontPlateArr);

  OrientationUnitVector=MidOfFrontalPlateVector-this->Body.GetPosition();
  OrientationUnitVector=OrientationUnitVector/OrientationUnitVector.Length();

  this->Orientation=OrientationUnitVector;

  return OrientationUnitVector;
}

/*!
* Dron stoi i w powietrzu obraca rotorami i nic nie robi przez time czasu
*
*\param[in] time - czas przez ktory dron bedzie stal
*\retval czy operacja sie powiodla
*/
bool Drone::Idle(float time,PzG::LaczeDoGNUPlota Lacze)
{
    for(int timer=0;timer<TIME_UNIT*10*time; timer+=TIME_UNIT)
    {
      this->SpinRotors(ROTATION_VELOCITY);
      this->UpdateFiles();

      Lacze.Rysuj();

      std::this_thread::sleep_for(std::chrono::milliseconds(TIME_UNIT_INT));
    }

    return 1;
}

/*!
* Funkcja drona o konkretny kat (calego drona) w obliczanym czasie
*
*\param[in] Angle - kat do obrotu
*\retval dron i wszystkie jego elementy obrocone w czasie zaleznym od kata
*/
bool Drone::DrawDroneRotation(double TotalAngle,PzG::LaczeDoGNUPlota Lacze)
{
    Vector3 BodyPosition=this->Body.GetPosition();
    int RotationDirection=1;

    double RotationTime = abs(TotalAngle*M_PI/180/(ROTATION_VELOCITY));

    if(TotalAngle<0){
      RotationDirection=-1;}

    for(int timer=0; timer<=RotationTime*100; timer+=TIME_UNIT/10)
    {
      this->SpinRotors(ROTATION_VELOCITY);

      this->Body=this->Body-BodyPosition;
      this->Body.AngleTrans(RotationDirection*ROTATION_VELOCITY*TIME_UNIT/1000,'z');
      this->Body=this->Body+BodyPosition;

      for(int i=0; i<4; i++){
        this->Rotor[i]=this->Rotor[i]-BodyPosition;
        this->Rotor[i].AngleTrans(RotationDirection*ROTATION_VELOCITY*TIME_UNIT/1000,'z');
        this->Rotor[i]=this->Rotor[i]+BodyPosition;
      }
      this->UpdateFiles();

      Lacze.Rysuj();


    }

    return 1;
}

/*!
* Funkcja wywolujaca obrot o odpowiedni kat (taki jaki trzeba )
*
*\param[in] Angle - kat do obrotu
*\param[in] Lacze - do rysowania
*\retval Czy operacja wykonana poprawnie
*/
bool Drone::AdjustOrientation(PzG::LaczeDoGNUPlota Lacze)
{
  double Angle;
  double OrientationToPathScalar=this->FindOrientation()*this->PlanPath();


  Angle=acos( OrientationToPathScalar/Orientation.Length()/this->PlanPath().Length()  );

  if(Angle*180/M_PI>180)
    Angle=Angle-2*M_PI;


  this->DrawDroneRotation(Angle*180/M_PI/2, Lacze);

  return 1;
}


/*!
* Pionowe przesuniecie drona w czasie
*
*\param[in] PathVector - wektor o ktory przesunie sie dron pionowo
*\param[in] Lacze - do rysowania
*\retval Czy operacja wykonana poprawnie
*/
bool Drone::DrawVerticalFlight(Vector3 PathVector, PzG::LaczeDoGNUPlota Lacze)
{
  Vector3 StartingCoords=this->Body.GetPosition();
  double VerticalTime   = MAX_HEIGHT / VELOCITY;

  for(double timer=0; timer<=VerticalTime  ; timer+=TIME_UNIT/1000)
    {
      this->Displacement(PathVector/VerticalTime*TIME_UNIT/1000);
      this->SpinRotors(ROTATION_VELOCITY);
      this->UpdateFiles();

      Lacze.Rysuj();

      std::this_thread::sleep_for(std::chrono::milliseconds(TIME_UNIT_INT));
    }

  if(this->Body.GetPosition()==StartingCoords+PathVector)
    return true;
  else
    return false;
}



/*!
* Poziome przesuniecie drona w czasie
*
*\param[in] PathVector - wektor o ktory przesunie sie dron poziomo
*\param[in] Lacze - do rysowania
*\retval Czy operacja wykonana poprawnie
*/
bool Drone::DrawHorizontalFlight(Vector3 PathVector, PzG::LaczeDoGNUPlota Lacze)
{
  Vector3 StartingCoords=this->Body.GetPosition();
  double VerticalTime   = PathVector.Length() / VELOCITY;

  for(double timer=0; timer<=VerticalTime  ; timer+=TIME_UNIT/1000)
    {
      this->Displacement(PathVector/VerticalTime*TIME_UNIT/1000);
      this->SpinRotors(ROTATION_VELOCITY);
      this->UpdateFiles();

      Lacze.Rysuj();

      std::this_thread::sleep_for(std::chrono::milliseconds(TIME_UNIT_INT));
    }

  if(this->Body.GetPosition()==StartingCoords+PathVector)
    return true;
  else
    return false;
}


/*!
* Zmiana trasy na wektor podany przez uzytkownika
*
*\param[in] NewPath - nowy wektor zapisany do pliku trasy przelotu
*\retval Czy operacja wykonana poprawnie
*/
bool Drone::ChangeFlightPath(Vector3 NewPath)
{
  std::ofstream  fin;

  fin.open(this->File_Names[5]);
  if (!fin.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << this->File_Names[5] << "\"" << std::endl
   << ":(  nie powiodla sie." << std::endl;
    return 0;
    }

  fin<< this->Body.GetPosition()[0] << " " << this->Body.GetPosition()[1] << " " << this->Body.GetPosition()[2] <<std::endl;
  fin<< this->Body.GetPosition()[0] << " " << this->Body.GetPosition()[1] << " " << 80 <<std::endl;
  fin<< NewPath[0] << " " << NewPath[1] << " " << 80 <<std::endl;
  fin<< NewPath[0] << " " << NewPath[1] << " " << NewPath[2] <<std::endl;

  return 1;
}

/*!
* Obliczenie promienia zajmowanego przez drona okregu w ktory nic nie powinno wejsc
*
*\retval dlugosc promienia
*/
double Drone::GetDiameter()
{
  return ( this->Rotor[0].GetPosition() - this->Rotor[0](0) ).Length() + (this->Body.GetPosition() - this->Body(0) ).Length();
}
