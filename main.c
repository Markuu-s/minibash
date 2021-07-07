#include "Executable.h"

extern Process foreground;
extern Vector backroundProcesses;

int main()
{
    foreground.id = -1;
    foreground.finish = true;
    init_vector(&backroundProcesses, sizeof(Process));
    setHomePath();

    signal(SIGINT, endForeground);
    signal(SIGCHLD, endTask);

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
            else if (strcmp(command.argv[0], "cd") == 0)
            {
                cd(command.argv);
            }
            else
            {
                undefinedProcess(&command);
            }
        }
        else // This command has pipe
        {
        }
    }

    freeVector(&backroundProcesses);
    return 0;
}