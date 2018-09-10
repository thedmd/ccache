#ifndef _WINDIRENT_H_
#define _WINDIRENT_H_
# include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dirent
{
    size_t    d_ino;          // inode number (not used by MS-DOS)
    size_t    d_namlen;       // name length
    char      d_name[257];    // file name
} _DIRECT;

typedef struct _dir_struc
{
    char    *start;         // starting position
    char    *curr;          // current position
    size_t  size;           // allocated size of string table
    size_t  nfiles;         // number of filenames in table
    struct dirent dirstr;   // directory structure to return
    void*   handle;         // system handle
    char    *end;           // position after last filename
} DIR;

// The idea here is to read all the directory names into a string table
// (separated by nulls) and when one of the other dir functions is called
// return the pointer to the current file name.
DIR* opendir(const char* filename);
struct dirent* readdir(DIR* dirp);
long telldir(DIR* dirp);
void seekdir(DIR *dirp, long loc);
int closedir(DIR* dirp);

#ifdef __cplusplus
}
#endif

#endif  /* _WINDIRENT_H_ */
