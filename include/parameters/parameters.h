#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <string.h>

typedef const char* Target;
typedef struct {
    Target *target;

    size_t count;
} TargetList;

typedef struct {
	Target output;

    TargetList include;
    TargetList source;
} CompileInfo;

bool validate_ext(const char *path, Error err);

void init_ci(CompileInfo *info, int argc);
void append_ci(TargetList *list, Target target);
void free_ci(CompileInfo *info);

void chckargs(CompileInfo *info, int argc, char **argv, Error err);
void print_ci(CompileInfo *info);

#endif