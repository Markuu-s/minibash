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

#endif // EXECUTABLE_H