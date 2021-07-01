#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void errExit(char* text){

    printf("\n%s: \n", text);
    exit(1);
}

int main(int argc, char *argv[])
{
    int pfd[2];          /* Файловые дескрипторы канала */
    if (pipe(pfd) == -1) /* Создаем канал */
        errExit("pipe");
    switch (fork())
    {
    case -1:
        errExit("fork");
    case 0:                      /* Первый потомок выполняет 'ls', записывая результат в канал */
        if (close(pfd[0]) == -1) /* Считывающий конец не используется */
            errExit("close 1 ");
        /* Дублируем стандартный вывод на записывающем конце канала;
 закрываем лишний дескриптор */
        if (pfd[1] != STDOUT_FILENO)
        { /* Проверка на всякий случай */
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
                errExit("dup2 1");
            if (close(pfd[1]) == -1)
                errExit("close 2");
        }
        execlp("ls", "ls", (char *)NULL); /* Записывает в канал */
        errExit("execlp ls");
    default: /* Родитель выходит из этого блока, чтобы создать следующего потомка */
        break;
    }
    switch (fork())
    {
    case -1:
        errExit("fork");
    case 0:                      /* Второй потомок выполняет 'wc', считывая ввод из канала */
        if (close(pfd[1]) == -1) /* Записывающий конец не используется */
            errExit("close 3");
        /* Дублируем стандартный ввод на считывающем конце канала;
 закрываем лишний дескриптор */
        if (pfd[0] != STDIN_FILENO)
        { /* Проверка на всякий случай */
            if (dup2(pfd[0], STDIN_FILENO) == -1)
                errExit("dup2 2");
            if (close(pfd[0]) == -1)
                errExit("close 4");
        }
        execlp("grep", "grep", "a", (char *)NULL); /* Читает из канала */
        errExit("execlp wc ");
    default: /* Родитель выходит из этого блока */
        break;
    }
    /* Родитель закрывает лишние дескрипторы канала и ждет завершения дочерних процессов */
    if (close(pfd[0]) == -1)
        errExit("close 5");
    if (close(pfd[1]) == -1)
        errExit("close 6");
    if (wait(NULL) == -1)
        errExit("wait 1");
    if (wait(NULL) == -1)
        errExit("wait 2");
    exit(EXIT_SUCCESS);
}