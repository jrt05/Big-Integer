#include <iostream>
#include <ctime>

#include "BInt.h"

int main()
{
    clock_t begin = clock();
    //BInt j(2, 74207281);
    //BInt j(2, 74200;
    //BInt j(200000000);
    BInt j(10);
    BInt k(-3);
    //j + 245;
    //j = j + -4;
    //j.add(234567893);
    //BigInteger j(-20);

    //for(int x = 0; x != 1000; ++x) {
    //    //j.multiply(435434343);
    //    j = j + 435434343;
    //}

    for(int x = 0; x != 1000; ++x) {
        if(x % 2 == 0) {
            j = (BInt) x + j;
        }
        else {
            j = (BInt) x - j;
        }
    }

    //j = j - 100;

    //j = j - k;

    j.print();
    std::cout << "\n";
    k.print();
    std::cout << "\n";
    //std::cout << j << "\n";
    //char a = getchar();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << "\n";
    return 0;
}


