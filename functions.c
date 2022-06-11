// funzioni

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "functions.h"

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

void check_openfile(FILE* fd) {
	if (fd == NULL) {
		printf("errore apertura file stat\n");
		exit(EXIT_FAILURE);
	}
}

void check_closefile(int clf) {
	if (clf == EOF) {
		printf("errore chiusura file\n");
		exit(EXIT_FAILURE);
	}
}

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

		//	char path[] = "/proc/";
			char* path = (char*)malloc(20*sizeof(char));
			strcpy(path, "/proc/");
			strcat(path, pid);
			strcat(path, "/stat");
			
			FILE* fd=fopen(path,"r");
			check_openfile(fd);

			int unused;
			char* command = (char*)malloc(100*sizeof(char));
		//	char command[1000];
			char state;
			int ppid;
			int pgrp;
			int session_id;
			fscanf(fd, "%d %s %c %d %d %d", &unused, command, &state, &ppid, &pgrp, &session_id);
				
			printf("%c\t", state);
			printf("%d\t", ppid);
			printf("%d\t\t", pgrp);
			printf("%d\t\t", session_id);
			printf("%s\n", command);
			
			int clf = fclose(fd);
			check_closefile(clf);
			
			free(path);
			free(command);
									
		}
		
		pdirent = readdir(pdir);
	
	}
}
