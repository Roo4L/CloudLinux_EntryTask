#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char** print_tree_dir(char* dir_name, char** parents, int depth);
char *joinstr (const char **s, size_t len, const char *sep);

int main() {
    char ** parents;
    parents = print_tree_dir(".", NULL, 0);
    free(parents);
}


/*
 * Description:
 *  Prints directory content recursively
 * Arguments:
 *  dir_name - directory name
 *  parents - parents of selected directory.
 *  depth - parents array length
 * Return:
 *  Returns pointer to parents, which may have changed during reallocation operation.
 */
char** print_tree_dir(char* dir_name, char** parents, int depth) {
	DIR* dir;

    // update parents info
    depth++;
    parents = (char**) realloc(parents, sizeof(char*) * depth);
    parents[depth - 1] = dir_name;
	dir = opendir(joinstr(parents, depth, "/"));
	if (!dir) {
		printf("An error occured. Can't open directory: %s\n", dir_name);
	}

	// print each filename recursively
	struct dirent* file;
	while (file = readdir(dir), file != NULL) {
	    // avoid cycles
	    if (strcmp(file->d_name,".") == 0 || strcmp(file->d_name, "..") == 0)
	        continue;
	    // print offset depending on parents directory
	    for (int i = 0; i < depth - 1; i++)
	        printf("\t");
	    printf("%s\n", file->d_name);
		if (file->d_type == DT_DIR) {
			parents = print_tree_dir(file->d_name, parents, depth);
		}
	}

	// free all resources
	free(file);
	closedir(dir);

	return parents;
}

char* joinstr(const char **s, size_t len, const char *sep)
{
    char *joined = NULL;
    size_t lensep = strlen (sep),
    sz = 0;
    int first = 1;

    for (int i = 0; i < len; i++) {
        size_t len = strlen (s[i]);
        /* allocate/reallocate joined */
        void *tmp = realloc (joined, sz + len + (first ? 0 : lensep) + 1);
        if (!tmp) {
            perror("realloc-tmp");
            exit (EXIT_FAILURE);
        }
        joined = tmp;
        if (!first) {
            strcpy (joined + sz, sep);
            sz += lensep;
        }
        strcpy (joined + sz, s[i]);
        first = 0;
        sz += len;
    }

    return joined;
}