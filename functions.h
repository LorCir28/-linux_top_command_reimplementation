// Angelo

#include <dirent.h>
#include <stdio.h>

// prototipo funzioni

// verifica corretta apertura directory
void check_opendir(DIR* pdir);

// verifica corretta chiusura directory
void check_closedir(int cld);

// verifica corretta apertura file
void check_openfile(FILE* fd);

// verifica corretta chiusura file
void check_closefile(int clf);

// verifica correttezza azione inserita
void check_action_inserted(char* signal_inserted);

// stampa informazioni processi
void print_process_informations(DIR* pdir, struct dirent* pdirent);
