#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char** argv) {

	// Lorenzo
	DIR* pdir = opendir("/proc");
	
	if (pdir == NULL) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	
	struct dirent* pdirent = readdir(pdir);
	
	while (pdirent != NULL) {
	//	char* pid = pdirent->d_name;
		char pid[] = "1";
	//	printf("%s\n", pid);

		// Angelo
		char path[] = "/proc/";
		strcat(path, pid);
	//	printf("%s", path);
		strcat(path, "/stat");
		printf("%s\n", path);
		FILE* fd=fopen(path,"r");
		int unused;
		char* command = (char*)malloc(sizeof(char));
		char state;
		int ppid;
		fscanf(fd, "%d %s %c %d", &unused, command, &state, &ppid);
		
		printf("%c\n", state);
		printf("%d\n", ppid);
		printf("%s\n", command);
		//fine Angelo
		
		pdirent = readdir(pdir);
	
	}
	//fine Lorenzo
	
	closedir(pdir);
	
	printf("\n");
	
	return 0;
	
}
