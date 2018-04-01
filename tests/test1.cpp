#include "../libdillpp.h"

#include <iostream>

#include <assert.h>
//#include <errno.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <unistd.h>
#include <vector>


int main(int argc, char *argv[])
{
    int port = 5555;
    if(argc > 1) port = atoi(argv[1]);


    struct ipaddr addr;
    int rc = ipaddr_local(&addr, NULL, port, 0);
    if (rc < 0) {
        perror("Can't open listening socket");
        return 1;
    }
    int ls = tcp_listen(&addr, 10);
    assert( ls >= 0 );
    
    while(1) {
        int r = tcp_accept(ls, NULL, -1);
        assert(r >= 0);
        printf("New connection! %i\n", r);


        dill::go([r]{
            int s = crlf_attach(r);
            assert(s >= 0);
        
            int rc = msend(s, "What's your name?", 17, -1);
            if(rc != 0) return rc;

            char inbuf[256];
            ssize_t sz = mrecv(s, inbuf, sizeof(inbuf), -1);
            if(sz < 0)
            {
                rc = hclose(s);
                return rc;
            }

            inbuf[sz] = 0;
            char outbuf[256];
            rc = snprintf(outbuf, sizeof(outbuf), "Hello, %s!", inbuf);
            rc = msend(s, outbuf, rc, -1);

            rc = hclose(s);
            assert(rc == 0);
        });
    }
    
    /*static int32_t counter = 0;

    dill::coroutine cr1( []() { ++counter; return;} );
    dill::coroutine cr2 = dill::go( [](int nb) { counter+=nb; return;}, 3 );

    dill::coroutine cr3( []() { 
        while(1)
        {
            ++counter;
            if (msleep(now()+500) < 0 && errno == ECANCELED)
            return;

        }} );
        
    dill::coroutine cr4 = dill::go( []() { 
        while(1)
        {
            std::cout << counter << std::endl;
            if (msleep(now()+1000) < 0 && errno == ECANCELED)
            return;

        }} );

    msleep(now()+2500);

    cr3.cancel();

    msleep(now()+2000);

    std::cout << counter << std::endl;

    return counter;*/
}
