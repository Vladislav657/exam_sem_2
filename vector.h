#include <iostream>
#include <initializer_list>
#include <type_traits>

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

    double operator ^ (Vector& other) const; // скалярное произведение

    template<typename U, typename V>
    friend Vector operator * (const U& arg1, const V& arg2);

    Vector operator / (double other) const;

    Vector operator += (Vector& other);

    Vector operator -= (Vector& other);

    Vector operator *= (double other);

    Vector operator *= (Vector& other);

    Vector operator /= (double other);

    Vector operator - () const;

    bool operator == (Vector& other) const;

    bool operator != (Vector& other) const;

    Vector operator = (const Vector& other);

    Vector operator = (Vector&& other) noexcept ;

    ~Vector();
};

template<typename U, typename V>
Vector operator*(const U& arg1, const V& arg2) {
    if constexpr (is_same<U, Vector>::value && is_same<V, Vector>::value){
        if (!(arg1.capacity == 3 && arg2.capacity == 3))
            throw invalid_argument("vector capacity should be = 3");
        double ax = arg1.coords[0], ay = arg1.coords[1], az = arg1.coords[2];
        double bx = arg2.coords[0], by = arg2.coords[1], bz = arg2.coords[2];
        Vector result = {ay * bz - by * az, ax * bz - bx * az, ax * by - bx * ay};
        return result;
    } else if constexpr (is_same<U, Vector>::value && (is_same<V, double>::value || is_same<V, int>::value)){
        auto *newCoords = new double [arg1.capacity];
        for (int i = 0; i < arg1.capacity; ++i) newCoords[i] = arg1.coords[i] * arg2;
        Vector result(arg1.capacity, newCoords);
        delete[] newCoords;
        return result;
    } else if constexpr ((is_same<U, double>::value || is_same<U, int>::value) && is_same<V, Vector>::value){
        auto *newCoords = new double [arg2.capacity];
        for (int i = 0; i < arg2.capacity; ++i) newCoords[i] = arg2.coords[i] * arg1;
        Vector result(arg2.capacity, newCoords);
        delete[] newCoords;
        return result;
    }
}

#endif //MATH_VECTOR_VECTOR_H
