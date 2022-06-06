#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>


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
		if (atoi(pdirent->d_name) != 0) {
			char* pid = pdirent->d_name;
			printf("%s\t", pid);

			// Angelo
			char path[] = "/proc/";
			strcat(path, pid);
			strcat(path, "/stat");

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
	
	// Lorenzo
	closedir(pdir);
	
	char signal_inserted;
	
	printf("inserire l'azione sul processo:\n");
	printf("-t per terminare\n");
	scanf("%c", &signal_inserted);
	
	int pid_signal;
	
	printf("inserire pid del processo: ");
	scanf("%d", &pid_signal);
	
	if (signal_inserted == 't') {
		kill(pid_signal, 9);
		printf("processo terminato");
	}
	
	printf("\n");
	
	return 0;
	
}
