#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>


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

		// Angelo
		FILE* fd=fopen("/proc/"+pid+"/stat","r");
		int unused;
		char* command = (char*)malloc(sizeof(char));
		char state;
		int ppid;
		fscanf(fd, "%d %s %c %d", &unused, command, &state, &ppid);
		
		printf("%c", state);
		printf("%d", ppid);
		printf("%s", command);
		//fine Angelo
		
		pdirent = readdir(pdir);
	}
	//fine Lorenzo
	
	closedir(pdir);
	
	printf("\n");
	
	return 0;
	
}
