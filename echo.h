#ifndef _ECHO_H
#define _ECHO_H

void process_echo(char **list,int tot) {
	for(int i = 1 ; i < tot ; i++) {
		printf("%s",list[i]);
		if(i < tot - 1)
			printf(" ");
	}
	puts("");
}

#endif