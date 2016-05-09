#include <iostream>
#include <ctime>

#include "BInt.h"

int main()
{
    clock_t begin = clock();
    //BInt j(2, 74207281);
    //BInt j(2, 74200;
    //BInt j(200000000);
    BInt j(2);
    //j + 245;
    //j = j + -23452;
    //j.add(234567893);
    //BigInteger j(-20);

    //for(int x = 0; x != 1000; ++x) {
    //    //j.multiply(435434343);
    //    j = j + 435434343;
    //}

    for(int x = 0; x != 1000; ++x) {
        j = j + j;
    }

    j.print();
    //std::cout << j << "\n";
    //char a = getchar();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << "\n";
    return 0;
}


