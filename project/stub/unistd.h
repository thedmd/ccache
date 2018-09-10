#pragma once
#include <process.h> // getpid
#include <io.h> // dup
//#include <stdint.h> // intptr_t

typedef int pid_t;

typedef int ssize_t;

typedef unsigned int useconds_t;

int usleep(useconds_t);

# define STDIN_FILENO  _fileno(stdin)
# define STDERR_FILENO _fileno(stderr)