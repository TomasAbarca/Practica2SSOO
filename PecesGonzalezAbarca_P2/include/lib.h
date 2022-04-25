/*  Aarón Peces García, Tomás Abarca Cerro, Fernando González García.

    lib.h: This header file that we use to include all the libraries we need, and
    define some variables such a colour codes for the standard output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <sstream>  
#include <mutex>
#include <algorithm>
#include <functional>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define NUMBER_CHAR_TO_ERASE 1