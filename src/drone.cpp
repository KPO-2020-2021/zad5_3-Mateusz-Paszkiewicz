#include "../include/drone.hh"

#define TIME_UNIT 10.00 //in miliseconds
#define TIME_UNIT_INT 10
#define MAX_HEIGHT 80
#define VELOCITY 30   //Units per second
#define ROTATION_VELOCITY 25*M_PI/180


Drone Drone::Create(const char* File_Names[7])
{
  CoordsReadFromFile(File_Names[0], this->Body);
  CoordsReadFromFile(File_Names[1], this->Rotor[0]);
  CoordsReadFromFile(File_Names[2], this->Rotor[1]);
  CoordsReadFromFile(File_Names[3], this->Rotor[2]);
  CoordsReadFromFile(File_Names[4], this->Rotor[3]);

  return (*this);
}

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

void Drone::UpdateFiles()
{
  SaveCoordsToFile(this->File_Names[0],     this->Body);
  SaveCoordsToFile(this->File_Names[1], this->Rotor[0]);
  SaveCoordsToFile(this->File_Names[2], this->Rotor[1]);
  SaveCoordsToFile(this->File_Names[3], this->Rotor[2]);
  SaveCoordsToFile(this->File_Names[4], this->Rotor[3]);
}


Drone Drone::Displacement(Vector3 Trans)
{
  (*this).Body=(*this).Body+Trans;
  (*this).Position=(*this).Position+Trans;

  for(int i=0; i<4; i++)
    (*this).Rotor[i]=(*this).Rotor[i]+Trans;

  return (*this);
}

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

bool Drone::AdjustOrientation(PzG::LaczeDoGNUPlota Lacze)
{
  double Angle;
  double OrientationToPathScalar=this->FindOrientation()*this->PlanPath();

  /*std::cout<<this->Orientation;

  std::cout<<OrientationToPathScalar<<std::endl;
  std::cout<<Orientation.Length()<<std::endl;
  std::cout<<this->PlanPath().Length()<<std::endl;*/

  Angle=acos( OrientationToPathScalar/Orientation.Length()/this->PlanPath().Length()  );
  std::cout<<Angle*180/M_PI;

  if(Angle*180/M_PI>180)
    Angle=Angle-2*M_PI;

  std::cout<<Angle*180/M_PI;

  this->DrawDroneRotation(Angle*180/M_PI/2, Lacze);

  return 1;
}

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

double Drone::GetRadius()
{
  return (this->Rotor[0].GetPosition() - this->Body.GetPosition()).Length();
}
