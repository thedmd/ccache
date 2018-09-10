# include "windirent.h"
# include <windows.h>

#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)

static int dir_exists(const char* filename)
{
    struct _stati64 st;
    if (0 == _stat64(filename, &st) && S_ISDIR(st.st_mode))
        return 1; // true
    else
        return 0; // false
}

// The idea here is to read all the directory names into a string table
// (separated by nulls) and when one of the other dir functions is called
// return the pointer to the current file name.
DIR* opendir(const char* filename)
{
    DIR* dirp = NULL;
    size_t idx;

    size_t len = strlen(filename);
    if (len > MAX_PATH)
        return NULL;

    // check to see if filename is a directory
    if (!dir_exists(filename))
        return NULL;

    // Get us a DIR structure
    dirp = malloc(sizeof(DIR));
    memset(dirp, 0, sizeof(DIR));

    // Create the search pattern
    char scanname[MAX_PATH + 3];
    strcpy(scanname, filename);

    // bare drive name means look in cwd for drive
    if (len == 2 && isalpha(scanname[0]) && scanname[1] == ':')
    {
        scanname[len++] = '.';
        scanname[len++] = '/';
    }
    else if (scanname[len - 1] != '/' && scanname[len - 1] != '\\')
    {
        scanname[len++] = '/';
    }
    scanname[len++] = '*';
    scanname[len] = '\0';

    // do the FindFirstFile call
    WIN32_FIND_DATA wFindData;
    HANDLE fh = FindFirstFileEx(scanname, FindExInfoStandard, &wFindData, FindExSearchNameMatch, NULL, 0);

    dirp->handle = (void*)fh;
    if (fh == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        // FindFirstFile() fails on empty drives!
        switch (err)
        {
            case ERROR_FILE_NOT_FOUND:
                return dirp;
            case ERROR_NO_MORE_FILES:
            case ERROR_PATH_NOT_FOUND:
                errno = ENOENT;
                break;
            case ERROR_NOT_ENOUGH_MEMORY:
                errno = ENOMEM;
                break;
            default:
                errno = EINVAL;
                break;
        }

        free(dirp);
        return NULL;
    }

    // now allocate the first part of the string table for
    // the filenames that we find.
    //sk::string buffer = sk_internal::PlatformStringToString(wFindData.cFileName);

    idx = strlen(wFindData.cFileName) + 1;
    if (idx < 256)
        dirp->size = 128;
    else
        dirp->size = idx;
    dirp->start = (char*)malloc(dirp->size);
    strcpy(dirp->start, wFindData.cFileName);
    dirp->nfiles++;
    dirp->end = dirp->curr = dirp->start;
    dirp->end += idx;
    return dirp;
}

// Readdir just returns the current string pointer and bumps the
// string pointer to the nDllExport entry.
struct dirent* readdir(DIR* dirp)
{
    int res;

    if (dirp->curr)
    {
        // first set up the structure to return
        size_t len = strlen(dirp->curr);
        strcpy(dirp->dirstr.d_name, dirp->curr);
        dirp->dirstr.d_namlen = len;

        // Fake an inode
        dirp->dirstr.d_ino = dirp->curr - dirp->start;

        // Now set up for the next call to readdir
        dirp->curr += len + 1;
        if (dirp->curr >= dirp->end)
        {
            // finding the next file that matches the wildcard
            // (which should be all of them in this directory!).
            WIN32_FIND_DATA wFindData;
            if ((res = FindNextFile(dirp->handle, &wFindData)))
            {
                size_t endpos = dirp->end - dirp->start;
                size_t newsize = endpos + strlen(wFindData.cFileName) + 1;
                // bump the string table size by enough for the
                // new name and its null terminator
                while (newsize > dirp->size)
                {
                    size_t curpos = dirp->curr - dirp->start;
                    dirp->size *= 2;
                    dirp->start = (char*)realloc(dirp->start, dirp->size);
                    dirp->curr = dirp->start + curpos;
                }
                strcpy(dirp->start + endpos, wFindData.cFileName);
                dirp->end = dirp->start + newsize;
                dirp->nfiles++;
            }
            else
                dirp->curr = NULL;
        }
        return &(dirp->dirstr);
    }
    else
        return NULL;
}

// Telldir returns the current string pointer position
long telldir(DIR* dirp)
{
    return (long)(dirp->curr - dirp->start);
}


// Seekdir moves the string pointer to a previously saved position
// (returned by telldir).
void seekdir(DIR *dirp, long loc)
{
    dirp->curr = dirp->start + loc;
}

// free the memory allocated by opendir
int closedir(DIR* dirp)
{
    if (dirp->handle != INVALID_HANDLE_VALUE)
        FindClose(dirp->handle);

    free(dirp->start);
    free(dirp);
    return 1;
}