#ifndef _BACKG_H
#define _BACKG_H
void sort_jobs() {
	for(int i = 0 ; i < bgsiz - 1 ; i++) {
		int sorted = 1;
		for(int j = 0;  j < bgsiz - 1 - i ; j++) {
			int swap = 0;
			int len1 = strlen(jobs_arr[j].command);
			int len2 = strlen(jobs_arr[j + 1].command);
			int len = len1 > len2 ? len2 : len1;
			for(int k = 0 ; k < len ; k++) {
				if(jobs_arr[j].command[k] == jobs_arr[j + 1].command[k]) {
					continue;
				}
				if(jobs_arr[j].command[k] > jobs_arr[j + 1].command[k])
					swap = 1;
				else
					swap = 2;
				break;
			}
			if(swap == 0 && len2 < len1) swap = 1;
			if(swap == 1) {
				sorted = 0;
				int temp_id = jobs_arr[j].id;
				char* temp_command = (char*)malloc(bufsiz);
				strcpy(temp_command, jobs_arr[j].command);
				int temp_num = jobs_arr[j].num;

				jobs_arr[j].id = jobs_arr[j + 1].id;
				strcpy(jobs_arr[j].command,jobs_arr[j + 1].command);
				jobs_arr[j].num = jobs_arr[j + 1].num;

				jobs_arr[j + 1].id = temp_id;
				strcpy(jobs_arr[j + 1].command,temp_command);
				jobs_arr[j + 1].num = temp_num;
			}
		}
		if(sorted) break;
	}
}
void handle_bg(char **list,int inbg) {
	int id = fork();
	int stat;
	if(id == -1) {
		perror("");
		return;
	}
	else {
		if(!inbg) {
			if(id == 0)  {
				if(setpgid(0,0) < 0)
					perror("");
				if(execvp(list[0],list) < 0) {
					perror("execvp");
				}
				exit(1);
			}
			else {
				fgpid = id;
				signal(SIGTTOU,SIG_IGN);
				signal(SIGTTIN,SIG_IGN);
				tcsetpgrp(STDIN_FILENO,id);
				waitpid(id,&stat,WUNTRACED);
				tcsetpgrp(STDIN_FILENO,getpgrp());
				if(WIFSTOPPED(stat)) {
					
					jobs_arr[bgsiz].id = id;
					jobs_arr[bgsiz].command = makecommand(list);
					jobs_arr[bgsiz].num = bgsiz + 1;
					bgsiz++;
					sort_jobs();

				}
				signal(SIGTTOU,SIG_DFL);
				signal(SIGTTIN,SIG_DFL);
				fgpid = 0;
			}
		}
		else {
			if(id == 0) {
				if(setpgid(0,0) < 0)
					perror("");
				if(execvp(list[0],list) < 0) {
					perror("execvp");
				}
				exit(1);
			}
			else {
				jobs_arr[bgsiz].id = id;
				jobs_arr[bgsiz].command = makecommand(list);
				jobs_arr[bgsiz].num = bgsiz + 1;
				bgsiz++;
				fprintf(stderr,"[%d] %d\n",bgsiz,jobs_arr[bgsiz - 1].id);
				sort_jobs();
			}
		}
	}
}
#endif
