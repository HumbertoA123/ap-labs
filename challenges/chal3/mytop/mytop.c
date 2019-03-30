#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <dirent.h>

void print_status(long tgid);
void clear();

struct Process
{
  long tgid;
  char pPid[5];
  char name[25];
  char state[25];
  float memory;
  char threads[2];
  int openFiles;
}pN;

void print_status(long tgid) {
  char path[40], fdPath[40], line[100], *state, *name, *pPid, *memory, *threads;
  FILE* statusf;
  
  snprintf(fdPath, 40, "/proc/%ld/fd", tgid);
  DIR *dr = opendir(fdPath);
  if(dr == NULL) {
    printf("COULD NOT OPEN DIR");
    return;
  }
  
  int file_count = 0;
    
  struct Process pN = {.tgid = tgid};
  struct dirent *de;
  
  snprintf(path, 40, "/proc/%ld/status", tgid);
    
  statusf = fopen(path, "r");
  if(!statusf)
    return;
  
  while(fgets(line, 100, statusf)) {
    if(strncmp(line, "PPid:", 5) == 0) {
      pPid = line + 6;
      char tmp[5];
      while(isspace(*pPid)) ++pPid;
      for(int i = 0; *pPid != '\n'; i++, pPid++){
	tmp[i] = *pPid;
      }
      strcpy(pN.pPid, tmp);
      memset(tmp, 0, sizeof(tmp));
    }
    else if(strncmp(line, "Name:", 5) == 0) {
      name = line + 6;
      char tmp[25];
      while(isspace(*name)) ++name;
      for(int i = 0; *name != '\n'; i++, name++) {
	tmp[i] = *name;
      }
      strcpy(pN.name, tmp);
      memset(tmp, 0, sizeof(tmp));
    }
    else if(strncmp(line, "State:", 6) == 0) {
      state = line + 7;
      char tmp[25];
      while(isspace(*state)) ++state;
      for(int i = 0; *state != '\n'; i++, state++) {
	tmp[i] = *state;
      }
      strcpy(pN.state, tmp);
      memset(tmp, 0, sizeof(tmp));
    }
    else if(strncmp(line, "VmSize:", 7) == 0) {
      memory = line + 8;
      char tmp[25];
      while(isspace(*memory)) ++memory;
      for(int i = 0; *memory != ' '; i++, memory++) {
        tmp[i] = *memory;
      }
      pN.memory = ((float)atoi(tmp)) / 1024;
      memset(tmp, 0, sizeof(tmp));
    }
    else if(strncmp(line, "Threads:", 8) == 0) {
      threads = line + 9;
      char tmp[2];
      while(isspace(*threads)) ++threads;
      for(int i = 0; *threads != '\n'; i++, threads++) {
        tmp[i] = *threads;
      }
      strcpy(pN.threads, tmp);
      memset(tmp, 0, sizeof(tmp));
    }
    else {
      continue;
    }
  }

  
  while((de = readdir(dr)) != NULL)
    file_count++;
  pN.openFiles = file_count;
  closedir(dr);

  printf("| %10ld    | %10s    | %20s    | %15s    | %10.2f M    | %10s    | %10d    | \n", pN.tgid, pN.pPid, pN.name, pN.state, pN.memory, pN.threads, pN.openFiles);
  fflush(stdout);
  fclose(statusf);
  
}

int main(){
  // Place your magic here
  while(1){
    char* a = "PID";
    char* b = "Parent";
    char* c = "Name";
    char* d = "State";
    char* e = "Memory";
    char* f = "# Threads";
    char* g = "Open files";

    DIR* proc = opendir("/proc");
    struct dirent* ent;
    long tgid;

    if(proc == NULL) {
        perror("opendir(/proc)");
    return 1;
    }

    printf("\n\n| %10s    | %10s    | %20s    | %15s    | %10s      | %10s    | %10s    | \n", a, b, c, d, e, f, g);
    printf("==================================================================================================================================\n");
    while((ent = readdir(proc))) {
        if(!isdigit(*ent->d_name))
            continue;

        tgid = strtol(ent->d_name, NULL, 10);

        print_status(tgid);
    }
    closedir(proc);
    sleep(1);
  }
    
    return 0;
}

void clear() {
    printf("\e[1;1H\e[2J"); 
}
