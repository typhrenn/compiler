#include <stdbool.h>
#include <string.h>

#include "error/error_handle.h"
#include "utils/file.h"
#include "parameters/parameters.h"

#ifdef _WIN32
    #define DEFAULT_OUT "a.exe"
#else
    #define DEFAULT_OUT "a.out"
#endif

static const char *TARGET_EXT = ".acf";

bool validate_ext(const char *path, Error err) {
    if (!path) return false;
    
    const char *dot = strrchr(path, '.');
    if (!dot || dot == path) {
        err("Unknown source file type:\n\t%s <-", path);
        return false;
    }
    
    if (strcmp(dot, TARGET_EXT) != 0) {
        err("Unexpected file extension '%s' (expected %s):\n\t%s <-", dot, TARGET_EXT, path);
        return false;
    }
    
    return true;
}

void init_ci(CompileInfo *info, int argc) {
	info->include.target = malloc(sizeof(Target) * (argc - 1));
	info->source.target = malloc(sizeof(Target) * (argc - 1));

	info->include.count = 0;
	info->source.count = 0;

	info->output = NULL;
}

void append_ci(TargetList *list, Target target) {
	list->target[list->count] = target;
	list->count++;
}

void free_ci(CompileInfo *info) {
	free(info->source.target);
	free(info->include.target);
}

void chckargs(CompileInfo *info, int argc, char **argv, Error err) {
    if (argc < 2) err("No arguments provided\n\tExpected usage: compiler <options> <input files>");
    init_ci(info, argc);

    for (int i = 1; i < argc; i++) {
        if (!(argv[i] != NULL && argv[i][0] == '-' && argv[i][1] != '\0')) {
            if (validate_ext(argv[i], err)) append_ci(&info->source, argv[i]);
        } else if (argv[i] != NULL && argv[i][0] == '-' && argv[i][1] != '\0') {
            switch (argv[i][1]) {
                case 'I': {
                    if (argv[i][2] != '\0') {
                        append_ci(&info->include, argv[i] + 2);
                    } else if (i + 1 < argc) {
                        i++;
                        append_ci(&info->include, argv[i]);
                    } else err("Missing path after -I option");
                    break;
				}

                case 'o': {
                    if (argv[i][2] != '\0') {
                        info->output = argv[i] + 2;
                    } else if (i + 1 < argc) {
                        i++;
                        info->output = argv[i];
                    } else err("Missing filename after -o option");
                    break;
				}

                default: {
                    err("unknown parameter\n\t%s <-", argv[i]);
                    break;
				}
            }
        } else err("unknown parameter\n\t%s <-", argv[i]);
    }

	if(info->output == NULL) info->output = DEFAULT_OUT;
}

void print_ci(CompileInfo *info) {
	printf("Output file -> %s\n\n", info->output);

	printf("Source files ->\n");
	for (int i = 0; i < info->source.count; i++) {
		printf("\t-> %s\n", info->source.target[i]);
	}

	printf("Include paths ->\n");
	for (int i = 0; i < info->include.count; i++) {
		printf("\t-> %s\n", info->include.target[i]);
	}
}