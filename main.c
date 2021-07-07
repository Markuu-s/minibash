#include "Executable.h"

int main(){

    setHomePath();
    while(1)
    {
        display();
        char *strFromInput = readLine();
        Vector /*<Command>*/ data = parse(strFromInput);
        free(strFromInput);
    }
    return 0;
}