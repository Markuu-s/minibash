#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include <stddef.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "Vector.h"
#include "Command.h"
#include "Process.h"

/**
 * @brief Get the Current Name of session
 * 
 * @return char* is string of name user
 */
char *getCurrentName();

/**
 * @brief Displays a current user name and a current directory
 * 
 */
void display();

/**
 * @brief Set directory as home path
 * 
 */
void setHomePath();

/**
 * @brief read line from standart input
 * 
 * @return char* is a line read
 */
char *readLine();

/**
 * @brief this function parse string into command
 * 
 * @param str is command from input
 * @return Vector<Command>
 */
Vector parse(char *str);

/**
 * @brief ls is system command. It shows information about files in directory
 * 
 * @param argv is command and arguments for it
 */
void ls(char **argv);

/**
 * @brief cd is system command. It allows navigate by folders.
 * 
 * @param argv is command and arguments for it.
 */
void cd(char **argv);

/**
 * @brief 
 * 
 * @param
 */
void undefinedProcess(Command *command);

/**
 * @brief 
 * 
 * @param sigInt 
 */
void endForeground(int sigInt);

/**
 * @brief 
 * 
 * @param sigInt 
 */
void endTask(int sigInt);

#endif // EXECUTABLE_H