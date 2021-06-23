#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include <cmath>

/*!
*\brief Klasa macierzy kwadratowej dowolnego rozmiaru, jej metody oraz
* funkcje
*
* Klasa zawiera definicje, metody i funkcje macierzy potrzebne do zrealizowania
* obrotu 3D za pomoca lacza do GNUplota.
*
*
*/
template<typename T, unsigned int dime>
class Matrix {
private:
    T value[dime][dime];

public:

    Matrix();

    Matrix(T [dime][dime]);

    Vector<T, dime> operator * (Vector<T, dime> tmp);

    bool operator == (Matrix<T, dime> const tmp) const ;

    Matrix operator + (Matrix<T, dime> tmp);

    Matrix operator * (Matrix<T, dime> tmp);

    T  &operator () (unsigned int row, unsigned int column);

    const T &operator () (unsigned int row, unsigned int column) const;

    void TransFill(Vector3, double &, char &);
};

typedef Matrix<double, 2> Matrix2x2;
typedef Matrix<double, 3> Matrix3x3;
typedef Matrix<double, 4> Matrix4x4;

template<typename T, unsigned int dime>
std::istream &operator>>(std::istream &in, Matrix<T, dime> &mat);

template<typename T, unsigned int dime>
std::ostream &operator<<(std::ostream &out, Matrix<T, dime> const &mat);

template<typename T, unsigned int dime>
T GaussMethod(Matrix<T, dime>);

/*!
* Konstruktor klasy Matrix.
*
*\param[in] Brak argumentow.
*\retval Macierz wypelnione wartoscia 0.
*/
template<typename T, unsigned int dime>
Matrix<T, dime>::Matrix() {
    for (unsigned int i = 0; i < dime; ++i) {
        for (unsigned int j = 0; j < dime; ++j) {
            value[i][j] = 0;
        }
    }
}

/*!
* Konstruktor parametryczny klasy Matrix.
*
*\param[in] tmp - dwuwymiarowa tablica z elementami typu double.
*\retval determinant -  Macierz wypelniona wartosciami podanymi w argumencie.
*/
template<typename T, unsigned int dime>
Matrix<T, dime>::Matrix(T tmp[dime][dime])
{
    for (unsigned int i = 0; i < dime; ++i) {
        for (unsigned int j = 0; j < dime; ++j) {
            value[i][j] = tmp[i][j];
        }
    }
}

/*!
* Realizuje mnozenie macierzy przez wektor.
*
*\param[in] this - macierz, czyli pierwszy skladnik mnozenia,
*\param[in] v - wektor, czyli drugi skladnik mnozenia.
*\retval determinant -  Iloczyn dwoch skladnikow przekazanych jako wektor.
*/
template<typename T, unsigned int dime>
Vector<T,dime> Matrix<T, dime>::operator * (Vector<T, dime> tmp) {
    Vector<T, dime> result;
    for (unsigned int i = 0; i < dime; ++i) {
        for (unsigned int j = 0; j < dime; ++j) {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}

/*!
* Funktor macierzy
*
*\param[in] row - numer wiersza.
*\param[in] column - numer kolumny.
*\retval determinant -  Wartosc macierzy w danym miejscu tablicy
*/
template<typename T, unsigned int dime>
T &Matrix<T, dime>::operator()(unsigned int row, unsigned int column)
{
   if (row >= dime) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= dime) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

/*!
* Funktor macierzy
*
*\param[in] row - numer wiersza.
*\param[in] column - numer kolumny.
*\retval determinant -  Wartosc macierzy w danym miejscu tablicy jako stala.
*/
template<typename T, unsigned int dime>
const T &Matrix<T, dime>::operator () (unsigned int row, unsigned int column) const {


    if (row >= dime) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= dime) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

/*!
* przeciazenie operatora == dla macierzy
*
*\param[in] (*this) - one of the matrices to be compared
*\param[in] v - second matrix to be compared
*\retval true - if the compared matrices are equal
*\retval false - if not
*/
template<typename T, unsigned int dime>
bool Matrix<T, dime>::operator == (Matrix<T, dime> const tmp) const {
  for (unsigned int i = 0; i < dime; ++i) {
      for (unsigned int j = 0; j < dime; ++j) {
        if(!((*this)(i, j)==tmp(i, j)))
          return false;
        }
      }
  return true;
}

/*!
* Przeciążenie dodawania macierzy
*
*\param[in] this - macierz, czyli pierwszy skladnik dodawania,
*\param[in] v - wektor, czyli drugi skladnik dodawania.
*\retvalue - Macierz - iloczyn dwóch podanych macierzy.
*/
template<typename T, unsigned int dime>
Matrix<T, dime> Matrix<T, dime>::operator + (Matrix<T, dime> tmp) {
    Matrix<T, dime> result;
    for (unsigned int i = 0; i < dime; ++i) {
        for (unsigned int j = 0; j < dime; ++j) {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}


/*!
* przeciazenie operatora * dla macierzy
*
*\param[in] (*this) - LHS matrix of multiplication
*\param[in] v - sRHS matrix of multiplication
*\retval result - the result of the multiplication
*/
template<typename T, unsigned int dime>
Matrix<T, dime> Matrix<T, dime>::operator * (Matrix<T, dime> const tmp)
{
    Matrix<T, dime> result= Matrix<T, dime>();
    for(unsigned int i = 0; i<dime; ++i)
    {
      for(unsigned int j = 0; j<dime; ++j)
        {
          for(unsigned int k = 0; k < dime; ++k)
            result(i, j)+=(*this)(i, k)*tmp(k, j);
        }
    }

    return result;
}

/*!
* Przeciazenie operatora >>
*
*\param[in] in - strumien wyjsciowy,
*\param[in] mat - macierz.
*/
template<typename T, unsigned int dime>
std::istream &operator>>(std::istream &in, Matrix<T, dime> &mat) {
    for (unsigned int i = 0; i < dime; ++i) {
        for (unsigned int j = 0; j < dime; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}

/*!
* Przeciazenie operatora <<
*
*\param[in] out - strumien wejsciowy,
*\param[in]  mat - macierz.
*/
template<typename T, unsigned int dime>
std::ostream &operator<<(std::ostream &out, const Matrix<T, dime> &mat) {
    for (unsigned int i = 0; i < dime; ++i) {
        for (unsigned  int j = 0; j < dime; ++j) {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}

/*!
* funkcja obliczajaca wyznacznik macierzy za pomoca
* eliminacji gaussa
*
*\param[in] (*this) - matrix of which determinant this function will
* evaluate
*\retval determinant - the determinant of the matrix
*/
template<typename T, unsigned int dime>
T GaussMethod(Matrix<T, dime> mat)
{
	 float a[dime+2][dime+2], ratio;
   double determinant=1;
	 int i,j,k, n=dime;

	 /* 2. Reading Augmented Matrix */
	 for(i=1;i<=n;i++)
	 {
		  for(j=1;j<=n;j++)
		  {
			   a[i][j]=mat(i-1,j-1);
		  }
	 }

	/* Applying Gauss Elimination */
	 for(i=1;i<=n-1;i++)
	 {
		  if(a[i][i] == 0.0)
		  {
			   std::cout<<"Mathematical Error!";
			   exit(0);
		  }
		  for(j=i+1;j<=n;j++)
		  {
			   ratio = a[j][i]/a[i][i];

			   for(k=1;k<=n;k++)
			   {
			  		a[j][k] = a[j][k] - ratio*a[i][k];
			   }
		  }
	 }

    for(i=1;i<=n;i++)
    {
      determinant=determinant*a[i][i];
    }

   return determinant;
}

template<typename T,unsigned int dime>
void Matrix<T, dime>::TransFill(Vector3 TransVector, double &Angle, char &axis)
{
  double AngleRad=Angle*M_PI/180;

  if(dime!=4)
    std::cout<<"Error! Wrong matrix size!";
  else
    {
      if(axis=='z')
        {
          double TransX[][4]={{cos(AngleRad),-sin(AngleRad),0,0},{sin(AngleRad),cos(AngleRad),0,0},{0,0,1,0},{0,0,0,1}};
          Matrix4x4 TransMat=Matrix4x4(TransX);

          double TransVec[][4]={{1,0,0,TransVector[0]},{0,1,0,TransVector[1]},{0,0,1,TransVector[2]},{0,0,0,1}};
          Matrix4x4 VecMatrix=Matrix4x4(TransVec);

          (*this)=VecMatrix*TransMat;
        }
      else if(axis=='y')
        {
          double TransY[][4]={{cos(AngleRad),0,-sin(AngleRad),0},{0,1,0,0},{sin(AngleRad),0,cos(AngleRad),0},{0,0,0,1}};
          Matrix4x4 TransMat=Matrix4x4(TransY);

          double TransVec[][4]={{1,0,0,TransVector[0]},{0,1,0,TransVector[1]},{0,0,1,TransVector[2]},{0,0,0,1}};
          Matrix4x4 VecMatrix=Matrix4x4(TransVec);

          (*this)=VecMatrix*TransMat;
        }
      else if(axis=='x')
      {
        double TransZ[][4]={{1,0,0,0},{0,cos(AngleRad),-sin(AngleRad),0},{0,sin(AngleRad),cos(AngleRad),0},{0,0,0,1}};
        Matrix4x4 TransMat=Matrix4x4(TransZ);

        double TransVec[][4]={{1,0,0,TransVector[0]},{0,1,0,TransVector[1]},{0,0,1,TransVector[2]},{0,0,0,1}};
        Matrix4x4 VecMatrix=Matrix4x4(TransVec);

        (*this)=VecMatrix*TransMat;
      }
    }
}
