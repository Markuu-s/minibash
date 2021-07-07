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
#include "Vector.h"
#include "Command.h"

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
 * @brief 
 * 
 * @return char* 
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

#endif // EXECUTABLE_H