#include "error/error_handle.h"
#include "utils/file.h"
#include <stdbool.h>

static const char *TARGET_EXT = ".acf";

static inline bool validate_ext(const char *path) {
    if (!path) return false;
    
    const char *dot = strrchr(path, '.');
    if (!dot || dot == path) {
        return false;
    }
    
    return strcmp(dot, TARGET_EXT) == 0;
}

typedef char* Target;
typedef struct {
    Target *target;

    int t_count;
    int t_capacity;
} TargetList;

typedef struct {
    Target include;

    TargetList header;
    TargetList source;
} CompileInfo;

static inline bool checkpar(const char *arg) {
    return (arg != NULL && arg[0] == '-' && arg[1] != '\0' && arg[2] != '\0');
}

void chckargc(CompileInfo *info, int argc, char **argv, Error err) {
    if (argc < 2) {
        err("No arguments provided\n\tExpected usage: compiler <options> <input files>");
    }


}