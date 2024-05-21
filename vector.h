#include <iostream>
#include <initializer_list>

using namespace std;

#ifndef MATH_VECTOR_VECTOR_H
#define MATH_VECTOR_VECTOR_H

class Vector{
private:
    int capacity;
    double *coords;

public:
    Vector();

    Vector(int capacity, const double *coords);

    Vector(initializer_list<double> input);

    Vector(const Vector& vector);

    Vector(Vector&& vector) noexcept ;

    friend ostream& operator << (ostream& out, Vector vector);

    Vector operator + (Vector& other) const;

    Vector operator - (Vector& other) const;

    Vector operator ^ (Vector& other) const; // векторное произведение

    double operator * (Vector& other) const; // скалярное произведение

    friend Vector operator * (Vector vector, double other);

    friend Vector operator * (double other, Vector vector);

    Vector operator / (double other) const;

    Vector operator += (Vector& other);

    Vector operator -= (Vector& other);

    Vector operator *= (double other);

    Vector operator ^= (Vector& other);

    Vector operator /= (double other);

    Vector operator - () const;

    bool operator == (Vector& other) const;

    bool operator != (Vector& other) const;

    Vector operator = (const Vector& other);

    Vector operator = (Vector&& other) noexcept ;

    ~Vector();
};

#endif //MATH_VECTOR_VECTOR_H
