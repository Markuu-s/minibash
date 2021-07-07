#include "Executable.h"

int main()
{

    setHomePath();
    while (1)
    {
        display();
        char *strFromInput = readLine();
        Vector /*<Command>*/ data = parse(strFromInput);
        free(strFromInput);

        if (data.size == 0)
        {
            continue;
        }
        else if (data.size == 1)
        {
            Command command = *(Command *)get(&data, 0);

            if (strcmp(command.argv[0], "ls") == 0)
            {
                ls(command.argv);
            }
        }
        else // This command has pipe
        {
        }
    }
    return 0;
}