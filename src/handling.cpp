#include<iostream>

#include"../include/handling.hh"

/*!
 * Funkcja odczytu zestawu punktow prostokata
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 *\param[in] Rect - objekt klasy rectangle do ktorego zapisane zostana dane
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool CoordsReadFromFile(char *sNazwaPliku, Rectangle &Rect)
{
    std::ifstream  fin;

  fin.open(sNazwaPliku);
  if (!fin.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
   << ":(  nie powiodla sie." << std::endl;
    return false;
    }

  fin >> Rect(0,0);   fin >> Rect(0,1);
  fin >> Rect(1,0);   fin >> Rect(1,1);
  fin >> Rect(2,0);   fin >> Rect(2,1);
  fin >> Rect(3,0);   fin >> Rect(3,1);
  fin >> Rect(0,0);   fin >> Rect(0,1);

  return true;
}


/*!
 * Przyklad zapisu wspolrzednych zbioru punktow prostopadloscianu do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool CoordsReadFromFile(const char * sNazwaPliku, Cuboid &Cub)
{
    std::ifstream  fin;

  fin.open(sNazwaPliku);
  if (!fin.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
   << ":(  nie powiodla sie." << std::endl;
    return false;
    }

    fin.ignore(10000,'\n');

    for(int i=0;i<8;i+=2){
      for(int j=0;j<3;j++)
        fin >> Cub(i,j);
      for(int j=0;j<3;j++)
        fin >> Cub(i+1,j);

      fin.ignore(10000,'\n');
      fin.ignore(10000,'\n');
      fin.ignore(10000,'\n');
      fin.ignore(10000,'\n');
    }


  fin.close();
  return true;
}




/*!
 * Przyklad zapisu wspolrzednych zbioru punktow prostopadloscianu do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void CoordsToStream( std::ostream& StrmWy, Rectangle &Rect)
{


  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Rect(0,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Rect(0,1) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Rect(1,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Rect(1,1) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Rect(2,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Rect(2,1) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Rect(3,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Rect(3,1) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Rect(0,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Rect(0,1) << std::endl;
                             // Jeszcze raz zapisujemy pierwszy punkt,
                             // aby gnuplot narysowal zamkniętą linię.
}



/*!
 * Funkcja zapisu zestawu punktow prostopadloscianu do strumienia
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 *\param[in] Cub - objekt klasy cuboid do ktorego zapisane zostana dane
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void CoordsToStream( std::ostream& StrmWy, Cuboid &Cub)
{
  double HalfHeight[3]={(Cub(1,0)-Cub(0,0))/2, (Cub(1,1)-Cub(0,1))/2, (Cub(1,2)-Cub(0,2))/2};
  Vector3 VecHalfHeight=Vector3(HalfHeight);

  Vector3 UpperCenter=Cub.GetPosition()+VecHalfHeight;
  Vector3 LowerCenter=Cub.GetPosition()-VecHalfHeight;


for(int i=0;i<8;i+=2){
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[2]<< std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Cub(i,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(i,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(i,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Cub(i+1,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(i+1,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(i+1,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[2]<< std::endl;
         StrmWy<<std::endl;
  }

  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[2]<< std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Cub(0,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(0,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(0,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Cub(1,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(1,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Cub(1,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[2]<< std::endl;
         StrmWy<<std::endl;
                             // Jeszcze raz zapisujemy pierwsze dwa punkt,
                             // aby gnuplot narysowal zamkniętą figure.
}

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool SaveCoordsToFile(const char *sNazwaPliku,  Rectangle &Rect)
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }

  CoordsToStream(StrmPlikowy, Rect);

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool SaveCoordsToFile(const char * sNazwaPliku,  Cuboid &Cub)
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }

  CoordsToStream(StrmPlikowy, Cub);

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow graniastoslupa do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool CoordsReadFromFile(const char *sNazwaPliku, Prism &Pri)
{
    std::ifstream  fin;

  fin.open(sNazwaPliku);
  if (!fin.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
   << ":(  nie powiodla sie." << std::endl;
    return false;
    }

fin.ignore(10000,'\n');

for(int i=0;i<12;i+=2){
  for(int j=0;j<3;j++){
    fin >> Pri(i,j);}
  for(int j=0;j<3;j++){
    fin >> Pri(i+1,j);}
  fin.ignore(10000,'\n');
  fin.ignore(10000,'\n');
  fin.ignore(10000,'\n');
  fin.ignore(10000,'\n');
}


  fin.close();
  return true;
}



/*!
 * Funkcja zapisu zestawu punktow graniastoslupa do strumienia
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 *\param[in] Pri - objekt klasy prism do ktorego zapisane zostana dane
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void CoordsToStream( std::ostream& StrmWy, Prism &Pri)
{

Vector3 UpperCenter=Vector3();
Vector3 LowerCenter=Vector3();

double HalfHeight[3]={(Pri(1,0)-Pri(0,0))/2, (Pri(1,1)-Pri(0,1))/2, (Pri(1,2)-Pri(0,2))/2};
Vector3 VecHalfHeight=Vector3(HalfHeight);

UpperCenter=Pri.GetPosition()+VecHalfHeight;
LowerCenter=Pri.GetPosition()-VecHalfHeight;

for(int i=0;i<12;i+=2){
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[2]<< std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Pri(i,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(i,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(i,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Pri(i+1,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(i+1,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(i+1,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[2]<< std::endl;
         StrmWy<<std::endl;
      }

  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << LowerCenter[2]<< std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Pri(0,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(0,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(0,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Pri(1,0)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(1,1)
         << std::setw(16) << std::fixed << std::setprecision(10) << Pri(1,2) << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[0]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[1]
         << std::setw(16) << std::fixed << std::setprecision(10) << UpperCenter[2]<< std::endl;
         StrmWy<<std::endl;
                             // Jeszcze raz zapisujemy pierwsze dwa punkt,
                             // aby gnuplot narysowal zamkniętą figure.
}


/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool SaveCoordsToFile(const char * sNazwaPliku,  Prism &Pri)
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }

  CoordsToStream(StrmPlikowy, Pri);

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}
