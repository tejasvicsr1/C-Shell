#ifndef _JOBS_H
#define _JOBS_H

void process_jobs(char **list,int siz) {
	if(siz > 2) {
		fprintf(stderr,"Invalid command");
		return;
	}
	int only_running = 0;
	int only_stopped = 0;
	if(siz == 2) {
		if(strcmp(list[1],"-r") == 0) {
			only_running = 1;
		}
		else if(strcmp(list[1],"-s") == 0) {
			only_stopped = 1;
		}
		else {
			fprintf(stderr,"Invalid flags");
			return;
		}
	}
	for(int i = 0 ; i < bgsiz ; i++) {
		char path[bufsiz];
		sprintf(path,"/proc/%d/stat",jobs_arr[i].id);
		FILE* fd = fopen(path,"r");
		if(fd == NULL) {
			perror("jobs");
			printf("%s [%d]\n",jobs_arr[i].command,jobs_arr[i].id);
			continue;
		}
		int pid;
		char pname[bufsiz];
		char status;
		fscanf(fd,"%d %s %c",&pid,pname,&status);
		if(only_running && status != 'S' && status != 'R') continue;
		if(only_stopped && status != 'T') continue;
		printf("[%d] ",jobs_arr[i].num);
		if(status == 'T')
			printf("Stopped ");
		else if(status == 'S' || status == 'R')
			printf("Running ");
		else
			printf("Unknown");
		printf("%s [%d]\n",jobs_arr[i].command,jobs_arr[i].id);
		fclose(fd);
	}
	
}

#endif
