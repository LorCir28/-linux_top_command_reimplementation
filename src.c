#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int main(int argc, char** argv) {

	// Lorenzo
	DIR* pdir = opendir("/proc");
	
	if (pdir == NULL) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	
	struct dirent* pdirent = readdir(pdir);
	
	while (pdirent != NULL) {
		char* pid = pdirent->d_name;
		printf("%s\t", pid);
		
		pdirent = readdir(pdir);
	}
	
	closedir(pdir);
	
	printf("\n");
	
	return 0;
	
}
