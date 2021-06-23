#include<cmath>

#include"../include/prism.hh"

/*!
 * Konstruktor objektu klasy Prism (bezparametryczny)
*
* \retval Prism Class object of coords 0
*/
Prism::Prism()
  {
    for(int i=0; i<12; i++)
      for(int j=0; j<3; j++)
        point[i][j]=0;
  }

  /*!
   * Konstruktor objektu klasy Prism (parametryczny)
  *
  *\param[in] tmp[12][3] - array of coords where the row is
  *the point number and column is the axis
  *\retval Prism Class object of coords 0
  */
Prism::Prism(double tmp[12][3])
  {
    for(int i=0; i<12; i++)
      for(int j=0; j<3; j++)
        point[i][j]=tmp[i][j];
  }

  /*!
  * przeciazenie operatora mnozenia dla graniastoslupa
  * (UWAGA) to dzialanie wychodzi poza matamtyczne definicje
  * i jest stworzone wylacznie dla prostoty rachunkow w dalszych
  * czesciach implementacji. To przeciazenie polega przemnozeniu
  * macierzy przez kazdy z punktow graniastoslupa (czyli przez
  * zestaw wspolrzednych jako kazdy rzad tablicy Prism) tak samo
  * jak przez wektor (takie mnozenie macierzy przez wektor 12 razy)
  *
  *\param[in] (*this) - LHS operand of multiplication
  *\param[in] tmp - RHS operand of multiplication
  *\retval result of multiplication of (*this) and tmp
  */
Prism Prism::operator * (Matrix3x3 &tmp)
  {
    double temp1, temp2;

    for(int i=0; i<12; i++){
        temp1=point[i][0];
        temp2=point[i][1];

        point[i][0]=point[i][0]*tmp(0, 0)+point[i][1]*tmp(0, 1)+point[i][2]*tmp(0, 2);
        point[i][1]=temp1*tmp(1, 0)+point[i][1]*tmp(1, 1)+point[i][2]*tmp(1, 2);
        point[i][2]=temp1*tmp(2, 0)+temp2*tmp(2, 1)+point[i][2]*tmp(2, 2);
       }
    return (*this);
  }

  /*!
   * przeciazenie operatora dodawania dla dwoch macierzy
  *
  *\param[in] (*this) - LHS operand of addition
  *\param[in] tmp - RHS operand of addition
  *\retval result of addition of (*this) and tmp
  */
Prism Prism::operator + (Vector3 &tmp)
  {
    for(int i=0; i<12; i++) {
      for(int j=0; j<3; j++) {
          point[i][j]+=tmp[j];
      }
    }
      return (*this);
  }

/*!
* przeciazenie operatora odejmowania dla graniastoslupa i wektora
*
*\param[in] (*this) - LHS operand of subtraction
*\param[in] tmp - RHS operand of subtraction
*\retval result of addition of (*this) and tmp (of type prism)
*/
Prism Prism::operator - (Vector3 &tmp)
  {
    for(int i=0; i<12; i++) {
      for(int j=0; j<3; j++) {
          point[i][j]-=tmp[j];
      }
    }
      return (*this);
  }

/*!
 * funktor () graniastoslupa
*
*\param[in] (*this) Prism of the coordinate to be extracted
*\param[in] pointNum - number of the wanted point
*\param[in] axis - axis of the wanted coordinate
*\retval const value of the coordinate of indicated values
*/
const double &Prism::operator () (unsigned int pointNum, unsigned int axis) const
{
    if (axis >= 3) {
        std::cout << "Error: Wrong parameter. Only 3 axis in a solid";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }
      if (pointNum >= 12) {
        std::cout << "Error: Wrong parameter. Only 12 points in a Prism";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }
      return point[pointNum][axis];
}

/*!
 * funktor () graniastoslupa
*
*\param[in] (*this) Prism of the coordinate to be extracted
*\param[in] pointNum - number of the wanted point
*\param[in] axis - axis of the wanted coordinate
*\retval value of the coordinate of indicated values
*/
double &Prism::operator () (unsigned int pointNum, unsigned int axis)
{
    if (axis >= 3) {
        std::cout << "Error: Wrong parameter. Only 3 axis in a solid";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }
      if (pointNum >= 12) {
        std::cout << "Error: Wrong parameter. Only 12 points in a Prism";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }
      return point[pointNum][axis];
}

std::ostream &operator<<(std::ostream &out, Prism &pri)
{
      for (int i = 0; i < 12; ++i) {
          for (int j = 0; j < 3; ++j) {
              out << pri(i, j) << "   ";
          }
          std::cout << std::endl;
      }
      return out;
}


Prism Prism::AngleTrans(double Angle, char axis)
{
  float sign=1;

  if(Angle<0){
     sign=-1;
     Angle=2*M_PI-Angle;}

  if(axis=='z')
    {
      double TransX[][3]={{cos(Angle),-sin(Angle)*sign,0},{sin(Angle)*sign,cos(Angle),0},{0,0,1}};
      Matrix3x3 TransMat=Matrix3x3(TransX);

      (*this)=(*this)*TransMat;
    }
  else if(axis=='y')
    {
      double TransY[][3]={{cos(Angle),0,-sin(Angle)*sign},{0,1,0},{sin(Angle)*sign,0,cos(Angle)}};
      Matrix3x3 TransMat=Matrix3x3(TransY);

      (*this)=(*this)*TransMat;
    }
  else if(axis=='x')
  {
    double TransZ[][3]={{1,0,0},{0,cos(Angle),-sin(Angle)*sign},{0,sin(Angle)*sign,cos(Angle)}};
    Matrix3x3 TransMat=Matrix3x3(TransZ);

    (*this)=(*this)*TransMat;
  }
  else
    {
      std::cerr<<"Error! Wrong axis argument (Neither x, y or z)"<<std::endl;
      return 0;
    }



  return (*this);

}

Vector3 Prism::GetPosition()
{
  double p0_arr[3]={(*this)(0,0),(*this)(0,1),(*this)(0,2)};  //points opposite to each other
  double p7_arr[3]={(*this)(7,0),(*this)(7,1),(*this)(7,2)};

  Vector3 p0_vec=Vector3(p0_arr);
  Vector3 p7_vec=Vector3(p7_arr);

  Vector3 temp=Vector3();

  temp=p7_vec-p0_vec;
  temp=temp/2;

  (*this).Position=p0_vec+temp;

  return (*this).Position;
}
