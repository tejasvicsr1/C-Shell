#ifndef _HANDLERS_H
#define _HANDLERS_H

void remid(int ind) {
	int job_num = jobs_arr[ind].num;
	for(int i = ind ; i + 1 < bgsiz ; i ++) {
		jobs_arr[i].id = jobs_arr[i + 1].id;
		strcpy(jobs_arr[i].command,jobs_arr[i + 1].command);
		jobs_arr[i].num = jobs_arr[i + 1].num;
	}
	bgsiz--;
	for(int i = 0 ; i < bgsiz ; i++) {
		if(jobs_arr[i].num > job_num) jobs_arr[i].num--;
	}
}
void exit_bgp(int sig) {
	for(int i = 0 ; i < bgsiz ; i++) {
		int status;
		if(waitpid(jobs_arr[i].id,&status,WNOHANG) > 0) {
			if(WIFEXITED(status))
				fprintf(stderr,"%s with pid %d exited normally\n",jobs_arr[i].command,jobs_arr[i].id);
			else
				fprintf(stderr,"%s with pid %d exited abnormally\n",jobs_arr[i].command,jobs_arr[i].id);
			remid(i);
		}
	}
}
void handle_ctrlc() {
	if(fgpid <= 0) {
		return;
	}
	kill(fgpid,SIGINT);
	fgpid = 0;
}
void handle_ctrlz() {
	if(fgpid <= 0) {
		return;
	}
	kill(fgpid,SIGTSTP);
	fgpid = 0;
}
#endif
