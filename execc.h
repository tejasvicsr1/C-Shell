#ifndef _EXECC_H
#define _EXECC_H
void execute(char* command) {
	read_history(command);
	char* part = strtok(command," \t\r\n\a");
	char* list[30];
	int ind = 0;
	int inbg = 0;
	int indir = -1;
	int outdir = -1;
	int outappdir = -1;
	while (part != NULL) {
		list[ind] = (char*)malloc(bufsiz);
		strcpy(list[ind],part);
		if(!strcmp(part,"<")) indir = ind;
		if(!strcmp(part,">")) outdir = ind;
		if(!strcmp(part,">>")) outappdir = ind;
		part = strtok(NULL," \t\r\n\a");
		ind++;
	}
	if(ind == 0)
		return;
	if(strcmp(list[ind - 1],"&") == 0) {
		inbg = 1;
		list[ind - 1] = NULL;
		ind--;
	}
	else {
		list[ind] = (char*)malloc(2);
		list[ind] = NULL;	
	}
	if(strcmp("quit", list[0]) == 0) exit(0);
	else if(indir > -1 || outdir > -1 || outappdir > -1) redirection(list,indir,outdir,outappdir,inbg);
	else if(strcmp(list[0],"cd") == 0)
		if(ind == 1) process_cd(homedir);
		else if(ind == 2) process_cd(list[1]);
		else printf("Too many arguments\n");
	else if(strcmp(list[0],"pwd") 		== 0) process_pwd();
	else if(strcmp(list[0],"echo") 		== 0) process_echo(list,ind);
	else if(strcmp(list[0],"ls")		== 0) process_ls(list,ind);
	else if(strcmp(list[0],"jobs") 		== 0) process_jobs(list,ind);
	else if(strcmp(list[0],"sig") 		== 0) process_sig(list,ind);
	else if(strcmp(list[0],"fg") 		== 0) process_fg(list,ind);
	else if(strcmp(list[0],"bg") 		== 0) process_bg(list,ind);
	else if(strcmp(list[0],"baywatch")  == 0) process_baywatch(list,ind);
	else if(strcmp(list[0],"replay")    == 0) process_replay(list,ind);
	else if(strcmp(list[0],"pinfo") 	== 0)
		if(ind == 1) process_pinfo(getpid());
		else process_pinfo(atoi(list[1]));
	else if(strcmp(list[0],"history") == 0)
		if(ind == 1) write_history(10);
		else write_history(atoi(list[1]));
	else handle_bg(list,inbg);

}
#endif
