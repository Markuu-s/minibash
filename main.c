#include "Executable.h"

int main(){

    setHomePath();
    while(1)
    {
        display();
        char *strFromInput = readLine();
        free(strFromInput);
    }
    return 0;
}