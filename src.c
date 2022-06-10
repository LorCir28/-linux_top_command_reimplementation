#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "functions.h"


int main(int argc, char** argv) {

	// Lorenzo
	DIR* pdir = opendir("/proc");
	check_opendir(pdir);

	struct dirent* pdirent = readdir(pdir);
	
	printf("PID\tSTATE\tPPID\tCOMMAND\n");
	
	print_process_informations(pdir, pdirent);

	//fine Lorenzo
		
	// Lorenzo
	int cld = closedir(pdir);
	check_closedir(cld);
	
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
		check_action_inserted(signal_inserted);

		if (strcmp(signal_inserted, "q") == 0) {
			break;
		}

		printf("inserire pid del processo (q to quit): ");
		scanf("%s", pid_signal);
		
		// Lorenzo	
		DIR* control_pdir = opendir("/proc");
		check_opendir(control_pdir);

		struct dirent* control_pdirent = readdir(control_pdir);
		
		int int_pid_signal = atoi(pid_signal);
		char current_state;
	
		while (control_pdirent != NULL) {
			int control_pid = atoi(control_pdirent->d_name);
			int_pid_signal = atoi(pid_signal);
	
			if (int_pid_signal == control_pid && control_pid != 0) {
				char pattern[] = "/proc/";
				strcat(pattern, pid_signal);
				strcat(pattern, "/stat");

				FILE* fdd=fopen(pattern,"r");
				check_openfile(fdd);

				int unused_variable;
			//	char* command = (char*)malloc(sizeof(char));
				char unused_command[1000];
				int unused_ppid;
				fscanf(fdd, "%d %s %c %d", &unused_variable, unused_command, &current_state, &unused_ppid);
				int clff = fclose(fdd);
				check_closefile(clff);

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
		
		int cldd = closedir(control_pdir);
		check_closedir(cldd);
	
		if (strcmp(signal_inserted, "k") == 0 && strcmp(pid_signal, "q") != 0) {
			kill(int_pid_signal, SIGKILL);
			printf("processo killato\n");
		}
		
		// Angelo
		else if(strcmp(signal_inserted, "s") == 0 && strcmp(pid_signal, "q") != 0)	{
			if (current_state != 'T') {
				kill(int_pid_signal, SIGSTOP);
				printf("processo sospeso\n");
			}
			else {
				printf("processo già sospeso\n");
			}
		}
		// Lorenzo
		else if(strcmp(signal_inserted, "r") == 0 && strcmp(pid_signal, "q") != 0)	{
			if (current_state == 'T') {
				kill(int_pid_signal, SIGCONT);
				printf("processo riesumato\n");
			}
			else {
				printf("tentata resume di un processo non sospeso\n");
			}
		}
		else if(strcmp(signal_inserted, "t") == 0 && strcmp(pid_signal, "q") != 0)	{
			kill(int_pid_signal, SIGTERM);
			printf("processo terminato\n");
		}
	
	}
	
	
	return 0;
}
