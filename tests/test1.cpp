#include "../libdillpp.h"

#include <iostream>

int main()
{
    static int32_t counter = 0;

//    auto func = dill::go( []() {return;} );

    auto cr1 = dill::go( []() { ++counter; return;} );
    //errno_assert(cr1 >= 0);
    auto cr2 = dill::go( [](int nb) { counter+=nb; return;}, 3 );
    //errno_assert(cr2 >= 0);
    /*int rc = hclose(cr1);
    errno_assert(rc == 0);
    rc = hclose(cr2);
    errno_assert(rc == 0);
    */

    std::cout << counter << std::endl;

    return counter;
}
