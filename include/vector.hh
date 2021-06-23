#pragma once

#include "size.hh"
#include <iostream>
#include <cmath>


/*!
*\brief Klasa wektora dowolnego rozmiaru, jego metody oraz
* funkcje
*
* Klasa zawiera definicje, metody i funkcje wektora potrzebne do zrealizowania
* obrotu 3D za pomoca lacza do GNUplota
*
*/
template<typename T, unsigned int dime>
class Vector {
private:
    T size[dime];

public:

    Vector();

    Vector(T [dime]);

    Vector operator + (const Vector<T, dime> v);

    Vector operator - (const Vector<T, dime> v);

    Vector operator * (const T &tmp);

    T operator * (const Vector &tmp);

    Vector operator / (const T &tmp);

    const T &operator [] (unsigned int index) const;

    T &operator [] (unsigned int index);

    bool operator == (const Vector<T, dime> ) const;

    double Length() const;

};

typedef Vector<double, 2> Vector2;
typedef Vector<double, 3> Vector3;

template<typename T, unsigned int dime>
std::ostream &operator << (std::ostream &out, Vector<T, dime> const &tmp);

template<typename T, unsigned int dime>
std::istream &operator >> (std::istream &in, Vector<T, dime> &tmp);

/*!
* Konstruktor klasy Vector.
*
* \param[in] - Brak argumentow.
* \retvalue - Tablice wypelniona wartoscia 0.
*/
template<typename T, unsigned int dime>
Vector<T, dime>::Vector() {
    for (unsigned int i = 0; i < dime; ++i) {
        size[i] = 0;
    }
}

/*!
*  Konstruktor parametryczny klasy Vector.
*
* \param[in] - tmp - Jednowymiarowa tablica typu double.
* \retvalue - Tablice wypelniona wartosciami podanymi w argumencie.
*/
template<typename T, unsigned int dime>
Vector<T, dime>::Vector(T tmp[dime]) {
    for (unsigned int i = 0; i < dime; ++i) {
        size[i] = tmp[i];
    }
}

/*!
* Realizuje dodawanie dwoch wektorow.
*
* \param[in] - this - pierwszy skladnik dodawania,
* \param[in] - v - drugi skladnik dodawania.
* \retvalue - Sume dwoch skladnikow przekazanych jako wskaznik
*               na parametr.
*/
template<typename T, unsigned int dime>
Vector<T, dime> Vector<T, dime>::operator + (const Vector<T, dime> v) {
    Vector<T, dime> result;
    for (unsigned int i = 0; i < dime; ++i) {
        result[i] = size[i] += v[i];
    }
    return result;
}

/*!
* Realizuje odejmowanie dwoch wektorow.
*
* \param[in] - this - pierwszy skladnik odejmowania,
* \param[in] - v - drugi skladnik odejmowania.
* \retvalue - Roznice dwoch skladnikow przekazanych jako wskaznik
*               na parametr.
*/
template<typename T, unsigned int dime>
Vector<T, dime> Vector<T, dime>::operator - (const Vector<T, dime> v) {
    Vector<T, dime> result;
    for (unsigned int i = 0; i < dime; ++i) {
        result[i] = size[i] -= v[i];
    }
    return result;
}

/*!
*  Realizuje mnozenie wektora przez liczbe zmiennoprzecinkowa.
*
* \param[in] - this - pierwszy skladnik mnozenia (wektor),
* \param[in] - v - drugi skladnik mnozenia (liczba typu typename).
* \retvalue - Iloraz dwoch skladnikow przekazanych jako wskaznik
*               na parametr.
*/
template<typename T, unsigned int dime>
Vector<T, dime> Vector<T, dime>::operator * (const T &tmp) {
    Vector<T, dime> result;
    for (unsigned int i = 0; i < dime; ++i) {
        result[i] = size[i] *= tmp;
    }
    return result;
}

template<typename T, unsigned int dime>
T Vector<T, dime>::operator * (const Vector<T, dime> &tmp) {
    T result;
    for (unsigned int i = 0; i < dime; ++i) {
        result+=this->size[i]*tmp[i];
    }
    return result;
}

/*!
*  Realizuje dzielenie dwoch wektorow.
*
* \param[in] - this - licznik dzielenia,
* \param[in] - v - mianownik dzielenia.
* \retvalue - Iloraz dwoch skladnikow przekazanych jako wskaznik
*               na parametr.
*/
template<typename T, unsigned int dime>
Vector<T, dime> Vector<T, dime>::operator / (const T &tmp) {
    Vector<T, dime> result;

    for (unsigned int i = 0; i < dime; ++i) {
        result[i] = size[i] / tmp;
    }

    return result;
}

/*!
*  Funktor wektora.
*
* \param[in] - index - index wektora.
* \retvalue - Wartosc wektora w danym miejscu tablicy jako stala.
*/
template<typename T, unsigned int dime>
const T &Vector<T, dime>::operator [] (unsigned int index) const {
    if (index < 0 || index >= dime) {
        std::cerr << "Error: Wektor jest poza zasiegiem!" << std::endl;
    } // lepiej byłoby rzucić wyjątkiem stdexcept
    return size[index];
}


/*!
*  Funktor wektora.
*
* \param[in] - index wektora.
* \retvalue - Wartosc wektora w danym miejscu tablicy.
*/
template<typename T, unsigned int dime>
T &Vector<T, dime>::operator[] (unsigned int index) {
    return const_cast<T &>(const_cast<const Vector *>(this)->operator[](index));
}

template<typename T, unsigned int dime>
double Vector<T, dime>::Length () const{
  double length=0;

  for(unsigned int i=0; i<dime; i++)
    length+=(*this)[i]*(*this)[i];

  length=sqrt(length);

  return length;
}

/*!
* przeciazenie operatora == dla wektora
*
*\param[in] (*this) - one of the vectors to be compared
*\param[in] v - second vector to be compared
*\retval true - if the compared vectors are equal
*\retval false - if not
*/
template<typename T, unsigned int dime>
bool Vector<T, dime>::operator == (const Vector<T, dime> v) const
  {
    bool equal=true;
    for(unsigned int i=0; i<dime; ++i)
    {
      if(abs((*this).size[i]-v.size[i])>0.0000001)
        equal=false;
    }

    return equal;
  }

/*!
* Przeciazenie operatora <<
*
*\param[in] out - strumien wejsciowy,
*\param[in] tmp - wektor.
*/
template<typename T, unsigned int dime>
std::ostream &operator << (std::ostream &out, Vector<T, dime> const &tmp) {
    for (unsigned int i = 0; i < dime; ++i) {
        out << "[ " << tmp[i] << " ]\n";
    }
    return out;
}

/*!
* Przeciazenie operatora >>
*
*\param[in] in - strumien wyjsciowy,
*\param[in] tmp - wektor.
*/
template<typename T, unsigned int dime>
std::istream &operator >> (std::istream &in, Vector<T, dime> &tmp) {
    for (unsigned int i = 0; i < dime; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}
