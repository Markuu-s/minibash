#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void read_from_pipe(int file, int *pipefd)
{
    FILE *stream;
    int c;
    stream = fdopen(file, "r");
    char buf;
    close(pipefd[1]);
    while (read(pipefd[0], &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);
    write(STDOUT_FILENO, "\n", 1);
    close(pipefd[0]);
}
/* Пишем некоторый произвольный текст в канал. */
void write_to_pipe(int file, int *pipefd, char *argv)
{
    close(pipefd[0]); /* Закрывает неиспользуемый конец для чтения */
    write(pipefd[1], argv, strlen(argv[1]));
    close(pipefd[1]); /* Читатель видит EOF */
}
int main(void)
{
    pid_t pid;
    int mypipe[2];
    /* Create the pipe. */
    if (pipe(mypipe))
    {
        fprintf(stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    /* Создаем дочерний процесс. */
    pid = fork();
    if (pid == (pid_t)0)
    {
        /* Это - дочерний процесс. */
        read_from_pipe(mypipe[0]);
        return EXIT_SUCCESS;
    }
    else if (pid < (pid_t)0)
    {
        /* The fork failed. */
        fprintf(stderr, "Fork failed.\n");
        return EXIT_FAILURE;
    }
    else
    {
        /* Это - родительский процесс. */
        write_to_pipe(mypipe[1]);
        return EXIT_SUCCESS;
    }
}