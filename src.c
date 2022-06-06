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
	printf("PID\tSTATE\tPPID\tCOMMAND\n");
	
	while (pdirent != NULL) {

		char* pid = pdirent->d_name;
		printf("%s\t", pid);

		if(atoi(pdirent->d_name)!=0){

			// Angelo
			char path[] = "/proc/";
			strcat(path, pid);
			strcat(path, "/stat");
			printf("%s\n", path);
			FILE* fd=fopen(path,"r");
			int unused;
			char command[1000];
			char state;
			int ppid;
			fscanf(fd, "%d %s %c %d", &unused, command, &state, &ppid);
			
			printf("%c\t", state);
			printf("%d\t", ppid);
			printf("%s\n", command);
			//fine Angelo
		}
		
		pdirent = readdir(pdir);
	
	}
	//fine Lorenzo
	
	closedir(pdir);
	
	printf("\n");
	
	return 0;
	
}
