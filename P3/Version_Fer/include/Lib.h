#include <iostream>
#include <time.h>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <condition_variable>
#include <atomic>
#include <string>
#include <dirent.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define CLIENTS 50
#define CONCURRENT_CLIENTS 4
#define LIMIT_WORDS 10
#define CREDITS 20
