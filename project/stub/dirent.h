#pragma once

#include <sys/stat.h>
#include <stdlib.h> // _MAX_PATH
#include <direct.h> // mkdir

#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)

#include "windirent.h"

#define PATH_MAX _MAX_PATH