#ifndef _sig_H
#define _sig_H

void process_sig(char **list , int ind) {
	if(ind != 3) {
		fprintf(stderr,"Invalid number of arguments\n");
		return;
	}
	int index = atoi(list[1]);
	if(index > bgsiz || index == 0) {
		fprintf(stderr,"No such process exists\n");
		return;
	}
	int pid;
	for(int i = 0 ; i < bgsiz ; i++) {
		if(jobs_arr[i].num == index) {
			pid = jobs_arr[i].id;
			break;
		}
	}
	int sig = atoi(list[2]);
	if(kill(pid,sig) == -1) {
		perror("kill");
		return;
	}	
}
#endif
