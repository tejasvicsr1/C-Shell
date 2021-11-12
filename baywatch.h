#ifndef _baywatch_H
#define _baywatch_H
void handler(int sig) {
	stoploop = 1;
}
void check_interrupt() {
	while(1) {
		char ch = fgetc(stdin);
		if(ch == EOF)
			break;
		if(ch == 'q') {
			kill(getppid(),45);
			exit(0);
		}
	}
}
void process_baywatch(char **list,int siz) {
	if(siz != 4) {
		fprintf(stderr,"Invalid number of arguments");
		return;
	}
	if(strcmp(list[1],"-n")) {
		fprintf(stderr,"Invalid command");
		return;
	}
	int interval = 0;
	for (int i = 0; i < list[2][i] != '\0'; i++)
	{
		if (list[2][i] < '0' || list[2][i] > '9')
		{
			fprintf(stderr,"Invalid argument");
			return;
		}
		else
		{
			interval= 10 * interval + list[2][i] - '0';
		}
	}
	if(strcmp(list[siz - 1],"interrupt") == 0) {
		FILE* fp = fopen("/proc/interrupts","r");
		if(fp == NULL) {
			perror("interrupts");
			return;
		}
		char* columns = (char*) malloc(bufsiz);
		getline(&columns,&bufsiz,fp);
		int len = strlen(columns);
		columns[len - 1] = '\0';
		char* part = strtok(columns," ");
		int cpucount = 0;
		while (part != NULL) {
			cpucount++;
			printf("%s ",part);
			part = strtok(NULL," ");
		}
		puts("");
		int id = fork();
		if(id == -1) {
			perror("fork");
			return;
		}
		else if(id == 0)
			check_interrupt();
		else {
			while(1) {
				signal(45,handler);
				if(stoploop) {
					stoploop = 0;
					break;
				}
				char* interrupts = (char*) malloc(bufsiz);
				int irq = -1;
				fseek(fp,0,SEEK_SET);
				while(getline(&interrupts,&bufsiz,fp)) {
					if(irq == 1)
						break;
					irq++;
				}
				char* part2 = strtok(interrupts," ");
				int ind = 0;
				while (part2 != NULL) {
					if(ind >= 1 && ind <= cpucount)
						printf("%4s ",part2);
					part2 = strtok(NULL," ");
					ind++;
				}
				puts("");
				sleep(interval);
			}
		}
				
	}
	else if(strcmp(list[siz - 1],"newborn") == 0) {
		int id = fork();
		if(id == -1) {
			perror("fork");
			return;
		}
		else if(id == 0)
			check_interrupt();
		else {
			while(1) {
				signal(45,handler);
				if(stoploop) {
					stoploop = 0;
					break;
				}
				FILE* fp = fopen("/proc/loadavg","r");
				if(fp == NULL) {
					perror("newborn");
					return;
				}
				char* line = (char*)malloc(bufsiz);
				getline(&line,&bufsiz,fp);
				char* part = strtok(line," ");
				char* last_pid = (char*)malloc(bufsiz);
				while(part != NULL) {
					strcpy(last_pid,part);
					part = strtok(NULL," ");
				}
				printf("%s",last_pid);
				sleep(interval);
			}
		}
	}
	else if(strcmp(list[siz - 1],"dirty") == 0) {
		int id = fork();
		if(id == -1) {
			perror("fork");
			return;
		}
		else if(id == 0)
			check_interrupt();
		else {
			while(1) {
				signal(45,handler);
				if(stoploop) {
					stoploop = 0;
					break;
				}
				FILE* fp = fopen("/proc/meminfo","r");
				if(fp == NULL) {
					perror("dirty");
					return;
				}
				char* line = (char*)malloc(bufsiz);
				int line_no = 17;
				while(line_no--)
					getline(&line,&bufsiz,fp);
				char* part = strtok(line," ");
				int cnt = 0;
				while(part != NULL) {
					if(cnt > 0) {
						printf("%s",part);
						if(cnt == 1)
							printf(" ");
					}
					part = strtok(NULL," ");
					cnt++;
				}
				sleep(interval);
			}
		}
	}
	else {
		fprintf(stderr,"Invalid command");
		return;
	}
}
#endif