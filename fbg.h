#ifndef _FBG_H
#define _FBG_H

void process_fg(char **list,int ind){
	if(ind != 2) {
		fprintf(stderr,"Invalid arguments\n");
		return;
	}
	int index = atoi(list[1]);
	if(index > bgsiz || index == 0) {
		fprintf(stderr,"Invalid job number\n");
		return;
	}
	int pid = jobs_arr[index - 1].id;
	if(kill(pid,SIGCONT) == -1) {
		fprintf(stderr,"signal failed\n");
		return;
	}
	fgpid = pid;
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	tcsetpgrp(STDIN_FILENO,pid);
	int status;
	waitpid(pid,&status,WUNTRACED);
	tcsetpgrp(STDIN_FILENO,getpgrp());
	if(!WIFSTOPPED(status)) {
		fgpid = 0;
		remid(index - 1);
	}
	signal(SIGTTOU,SIG_DFL);
	signal(SIGTTIN,SIG_DFL);
}
void process_bg(char **list,int ind) {
	if(ind != 2) {
		fprintf(stderr,"Invalid arguments\n");
		return;
	}
	int index = atoi(list[1]);
	if(index > bgsiz || index == 0) {
		fprintf(stderr,"Invalid job number\n");
		return;
	}
	int pid = jobs_arr[index - 1].id;;
	if(kill(pid,SIGCONT) == -1) {
		fprintf(stderr,"signal failed\n");
		return;
	}
}
#endif
