#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "functions.h"


int main(int argc, char** argv) {

	// Lorenzo
	
	// apertura directory /proc
	DIR* pdir = opendir("/proc");
	check_opendir(pdir);

	// puntatore a struct dirent per ciclare sul contenuto di /proc
	struct dirent* pdirent = readdir(pdir);
	
	printf("PID\tSTATE\tPPID\tCOMMAND\n");
	
	print_process_informations(pdir, pdirent);

	// chiusura directory /proc
	int cld = closedir(pdir);
	check_closedir(cld);
	
	// gestione segnali
	char* signal_inserted = (char*)malloc(sizeof(char));
	char* pid_signal = (char*)malloc(sizeof(char));
	
	// ciclo per evitare la terminazione del programma
	while (1) {
		
		// inserimento azione sul processo
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

		// inserimento pid del processo
		printf("inserire pid del processo (q to quit): ");
		scanf("%s", pid_signal);
		
		// Lorenzo
		
		// controllo pid inserito
		DIR* control_pdir = opendir("/proc");
		check_opendir(control_pdir);

		struct dirent* control_pdirent = readdir(control_pdir);
		
		int int_pid_signal = atoi(pid_signal);
		char current_state;
	
		while (control_pdirent != NULL) {
			// atoi serve per prendere solo le sottocartelle che sono numeri (ossia i pid dei processi)
			int control_pid = atoi(control_pdirent->d_name);
			int_pid_signal = atoi(pid_signal);
			
			// caso in cui il pid inserito è presente in /proc
			if (int_pid_signal == control_pid && control_pid != 0) {
				// salvataggio dello stato corrente per i controlli successivi su suspend e resume
				char pattern[] = "/proc/";
				strcat(pattern, pid_signal);
				strcat(pattern, "/stat");

				FILE* fdd=fopen(pattern,"r");
				check_openfile(fdd);

				int unused_variable;
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
			
			// caso in cui il ciclo su /proc è finito o il pid inserito è una stringa di caratteri (e quindi il pid inserito non è valido)
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
	
		// kill di un processo
		if (strcmp(signal_inserted, "k") == 0 && strcmp(pid_signal, "q") != 0) {
			kill(int_pid_signal, SIGKILL);
			printf("processo killato\n");
		}
		
		// Angelo
		// sospensione di un processo
		else if(strcmp(signal_inserted, "s") == 0 && strcmp(pid_signal, "q") != 0)	{
			if (current_state != 'T') {
				kill(int_pid_signal, SIGSTOP);
				printf("processo sospeso\n");
			}
			else {
				printf("processo già sospeso\n");
			}
		}
		// resume di un progetto
		else if(strcmp(signal_inserted, "r") == 0 && strcmp(pid_signal, "q") != 0)	{
			if (current_state == 'T') {
				kill(int_pid_signal, SIGCONT);
				printf("processo riesumato\n");
			}
			else {
				printf("tentata resume di un processo non sospeso\n");
			}
		}
		// Lorenzo
		// terminazione di un processo
		else if(strcmp(signal_inserted, "t") == 0 && strcmp(pid_signal, "q") != 0)	{
			kill(int_pid_signal, SIGTERM);
			printf("processo terminato\n");
		}
	
	}
	
	
	return 0;
}
