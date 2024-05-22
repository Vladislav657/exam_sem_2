#include <iostream>
#include "vector.h"

int main(){
    Vector v1 = {-4, 3, 1}, v2 = {-3, 5, 5};

    double d = v2 ^ v1;

    Vector v3 = v2 * v1;

    Vector v4 =  v2 * 4.;

    Vector v5 = 4 * v2;

    Vector v6 = v3;

    Vector v7 = v6 + v1 - v2;

    cout << d  << endl << v3 << v4 << v5 << v6 << v7;

    return 0;
}
