// Angelo

#include <dirent.h>
#include <stdio.h>

// prototipo funzioni
void check_opendir(DIR* pdir);
void check_closedir(int cld);
void check_openfile(FILE* fd);
void check_closefile(int clf);
void check_action_inserted(char* signal_inserted);
void print_process_informations(DIR* pdir, struct dirent* pdirent);
