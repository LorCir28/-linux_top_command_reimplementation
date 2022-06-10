#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

// prototipo funzioni

// Angelo
void check_opendir(DIR* pdir);
void check_closedir(int cld);
void check_openfile(FILE* fd);
void check_closefile(int clf);
void check_action_inserted(char* signal_inserted);
void print_process_informations(DIR* pdir, struct dirent* pdirent);


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




// funzioni

// Angelo
void check_opendir(DIR* pdir) {
	if (pdir == NULL) {
		printf("errore apertura directory /proc");
		exit(EXIT_FAILURE);
	}
}

void check_closedir(int cld) {
	if (cld == -1) {
		printf("errore chiusura directory /proc\n");
		exit(EXIT_FAILURE);
	}
}

// Lorenzo
void check_openfile(FILE* fd) {
	if (fd == NULL) {
		printf("errore aperture file stat\n");
		exit(EXIT_FAILURE);
	}
}

void check_closefile(int clf) {
	if (clf == EOF) {
		printf("errore chiusura file\n");
		exit(EXIT_FAILURE);
	}
}

// Angelo
void check_action_inserted(char* signal_inserted) {
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
}

//Lorenzo
void print_process_informations(DIR* pdir, struct dirent* pdirent) {
	while (pdirent != NULL) {
		if (atoi(pdirent->d_name) != 0) {
			char* pid = pdirent->d_name;
			printf("%s\t", pid);

			char path[] = "/proc/";
			strcat(path, pid);
			strcat(path, "/stat");

			FILE* fd=fopen(path,"r");
			check_openfile(fd);

			int unused;
		//	char* command = (char*)malloc(sizeof(char));
			char command[1000];
			char state;
			int ppid;
			fscanf(fd, "%d %s %c %d", &unused, command, &state, &ppid);
				
			printf("%c\t", state);
			printf("%d\t", ppid);
			printf("%s\n", command);
			
			int clf = fclose(fd);
			check_closefile(clf);

		}
		
		pdirent = readdir(pdir);
	
	}
}
