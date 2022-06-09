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
		//	char* command = (char*)malloc(sizeof(char));
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
		
	// manage signals
	char* signal_inserted = (char*)malloc(sizeof(char));
	char* pid_signal = (char*)malloc(sizeof(char));
	
	while (1) {
		
		printf("inserire l'azione sul processo:\n");
		printf("-k per killare\n");
		printf("-s per sospendere\n");
		printf("-r per riesumare\n");
		printf("-t per terminare\n");
		printf("-q to quit\n");
		scanf("%s", signal_inserted);

		// Angelo
		while(strcmp(signal_inserted, "k") != 0 && strcmp(signal_inserted, "s") != 0 && strcmp(signal_inserted, "r") && strcmp(signal_inserted, "t") != 0 && strcmp(signal_inserted, "q") != 0){
			printf("Azione inserita non valida\n");
			printf("Inserire l'azione sul processo:\n");
			printf("-k per killare\n");
			printf("-s per sospendere\n");
			printf("-r per riesumare\n");
			printf("-t per terminare\n");
			printf("-q to quit\n");
			scanf("%s", signal_inserted);
		}
		
		if (strcmp(signal_inserted, "q") == 0) {
			break;
		}

		printf("inserire pid del processo (q to quit): ");
		scanf("%s", pid_signal);
		
	//	int int_pid_signal = atoi(pid_signal);
	//	printf("%d", int_pid_signal);
	
		if (strcmp(pid_signal, "q") == 0) {
			break;
		}
	//	if (atoi(pid_signal) == 0) {
	//		printf("HAI INSERITO UNA FRASE");
	//	}
		
		// Lorenzo	
		DIR* control_pdir = opendir("/proc");
		if (control_pdir == NULL) {
			printf("error\n");
			exit(EXIT_FAILURE);
		}
			
		struct dirent* control_pdirent = readdir(control_pdir);
		
		int int_pid_signal = atoi(pid_signal);
	//	printf("%d\n", int_pid_signal);
		
		while (control_pdirent != NULL) {
			int control_pid = atoi(control_pdirent->d_name);
	//		printf("DIRECTORY %d\n", control_pid);
			int_pid_signal = atoi(pid_signal);
			
	//		printf("%d\n", int_pid_signal);
	
	
			if (int_pid_signal == control_pid && control_pid != 0) {
				break;
			}
		
			if (strcmp(pid_signal, "q") == 0) {
				break;
			}
			
			control_pdirent = readdir(control_pdir);
			
			if (control_pdirent == NULL || int_pid_signal == 0) {
				printf("pid inserito non valido\n");
				printf("inserire pid del processo (q to quit): ");
				scanf("%s", pid_signal);
				
				control_pdir = opendir("/proc");
				control_pdirent = readdir(control_pdir);
			}
	
		}
	
	//	if (strcmp(pid_signal, "q") == 0) {
	//		break;
	//	}
	
	
		if (strcmp(signal_inserted, "k") == 0) {
			kill(int_pid_signal, SIGKILL);
			printf("processo killato\n");
		}
		
		// Angelo
		else if(strcmp(signal_inserted, "s") == 0)	{
			kill(int_pid_signal, SIGSTOP);
			printf("processo sospeso\n");
		}
		else if(strcmp(signal_inserted, "r") == 0)	{
			kill(int_pid_signal, SIGCONT);
			printf("processo riesumato\n");
		}
		// Lorenzo
		else if(strcmp(signal_inserted, "t") == 0)	{
			kill(int_pid_signal, SIGTERM);
			printf("processo terminato\n");
		}
	
	}
	
	
	return 0;
}
