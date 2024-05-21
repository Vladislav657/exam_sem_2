#include "vector.h"

Vector::Vector() {
    this->capacity = 2;
    this->coords = new double [2];
    this->coords[0] = this->coords[1] = 0;
}

Vector::Vector(int capacity, const double *coords) {
    if (capacity < 2) throw invalid_argument("vector capacity should be >= 2");
    this->capacity = capacity;
    this->coords = new double [capacity];
    for (int i = 0; i < capacity; ++i) this->coords[i] = coords[i];
}

Vector::Vector(initializer_list<double> input) {
    this->capacity = (int)input.size();
    this->coords = new double[this->capacity];
    const double *current = input.begin();
    for (int i = 0; i < input.size(); ++i) this->coords[i] = *current++;
}

Vector::Vector(const Vector &vector) {
    this->capacity = vector.capacity;
    this->coords = new double[vector.capacity];
    for (int i = 0; i < vector.capacity; ++i) this->coords[i] = vector.coords[i];
}

Vector::Vector(Vector &&vector)  noexcept {
    this->capacity = vector.capacity;
    this->coords = vector.coords;
}

ostream &operator<<(ostream &out, Vector vector) {
    out << "\n{";
    for (int i = 0; i < vector.capacity; ++i){
        out << vector.coords[i];
        if (i < vector.capacity - 1) out << ", ";
    }
    out << "}\n";
    return out;
}

Vector Vector::operator+(Vector &other) const {
    if (this->capacity != other.capacity) throw invalid_argument("vector capacity should be equal");
    auto *newCoords = new double [this->capacity];
    for (int i = 0; i < this->capacity; ++i) newCoords[i] = this->coords[i] + other.coords[i];
    Vector result(this->capacity, newCoords);
    delete[] newCoords;
    return result;
}

Vector Vector::operator-(Vector &other) const{
    if (this->capacity != other.capacity) throw invalid_argument("vector capacity should be equal");
    auto *newCoords = new double [this->capacity];
    for (int i = 0; i < this->capacity; ++i) newCoords[i] = this->coords[i] - other.coords[i];
    Vector result(this->capacity, newCoords);
    delete[] newCoords;
    return result;
}

Vector Vector::operator^(Vector &other) const{
    if (!(this->capacity == 3 && other.capacity == 3))
        throw invalid_argument("vector capacity should be = 3");
    double ax = this->coords[0], ay = this->coords[1], az = this->coords[2];
    double bx = other.coords[0], by = other.coords[1], bz = other.coords[2];
    Vector result = {ay * bz - by * az, ax * bz - bx * az, ax * by - bx * ay};
    return result;
}

double Vector::operator*(Vector &other) const{
    if (this->capacity != other.capacity)
        throw invalid_argument("vector capacity should be equal");
    double result = 0;
    for (int i = 0; i < this->capacity; ++i) result += this->coords[i] * other.coords[i];
    return result;
}

Vector operator*(Vector vector, double other) {
    auto *newCoords = new double [vector.capacity];
    for (int i = 0; i < vector.capacity; ++i) newCoords[i] = vector.coords[i] * other;
    Vector result(vector.capacity, newCoords);
    delete[] newCoords;
    return result;
}

Vector operator*(double other, Vector vector) {
    auto *newCoords = new double [vector.capacity];
    for (int i = 0; i < vector.capacity; ++i) newCoords[i] = vector.coords[i] * other;
    Vector result(vector.capacity, newCoords);
    delete[] newCoords;
    return result;
}

Vector Vector::operator/(double other) const{
    if (other == 0) throw invalid_argument("other should be != 0");
    auto *newCoords = new double [this->capacity];
    for (int i = 0; i < this->capacity; ++i) newCoords[i] = this->coords[i] / other;
    Vector result(this->capacity, newCoords);
    delete[] newCoords;
    return result;
}

Vector Vector::operator+=(Vector &other) {
    if (this->capacity != other.capacity) throw invalid_argument("vector capacity should be equal");
    for (int i = 0; i < this->capacity; ++i) this->coords[i] += other.coords[i];
    return *this;
}

Vector Vector::operator-=(Vector &other) {
    if (this->capacity != other.capacity) throw invalid_argument("vector capacity should be equal");
    for (int i = 0; i < this->capacity; ++i) this->coords[i] -= other.coords[i];
    return *this;
}

Vector Vector::operator*=(double other) {
    for (int i = 0; i < this->capacity; ++i) this->coords[i] *= other;
    return *this;
}

Vector Vector::operator^=(Vector &other) {
    if (!(this->capacity == 3 && other.capacity == 3))
        throw invalid_argument("vector capacity should be = 3");
    double ax = this->coords[0], ay = this->coords[1], az = this->coords[2];
    double bx = other.coords[0], by = other.coords[1], bz = other.coords[2];
    this->coords[0] = ay * bz - by * az;
    this->coords[1] = ax * bz - bx * az;
    this->coords[2] = ax * by - bx * ay;
    return *this;
}

Vector Vector::operator/=(double other) {
    if (other == 0) throw invalid_argument("other should be != 0");
    for (int i = 0; i < this->capacity; ++i) this->coords[i] /= other;
    return *this;
}

Vector Vector::operator-() const{
    auto *newCoords = new double [this->capacity];
    for (int i = 0; i < this->capacity; ++i) newCoords[i] = -this->coords[i];
    Vector result(this->capacity, newCoords);
    delete[] newCoords;
    return result;
}

Vector Vector::operator = (const Vector& other) {
    this->capacity = other.capacity;
    this->coords = new double[other.capacity];
    for (int i = 0; i < other.capacity; ++i) this->coords[i] = other.coords[i];
    return *this;
}

Vector Vector::operator = (Vector&& other) noexcept{
    this->capacity = other.capacity;
    this->coords = other.coords;
    return *this;
}

bool Vector::operator==(Vector &other) const {
    if (this->capacity != other.capacity) throw invalid_argument("vector capacity should be equal");
    for (int i = 0; i < this->capacity; ++i) if (this->coords[i] != other.coords[i]) return false;
    return true;
}

bool Vector::operator!=(Vector &other) const {
    return !(*this == other);
}

Vector::~Vector() {
    delete[] this->coords;
}
