#ifndef replay_h
#define replay_h

void process_replay(char** list, int siz) {
    if(siz < 7) {
        fprintf(stderr, "Invalid number of arguments");
        return;
    }
    if(strcmp(list[1],"-command")) {
        fprintf(stderr,"Invalid command");
        return;
    }
    if(strcmp(list[siz - 2],"-period")) {
        fprintf(stderr,"Invalid command");
        return;
    }
    if(strcmp(list[siz - 4],"-interval")) {
        fprintf(stderr,"Invalid command");
        return;
    }
    int interval = 0;
    int period = 0;
    for (int i = 0; i < list[siz - 1][i] != '\0'; i++) {
        if (list[siz - 1][i] < '0' || list[siz - 1][i] > '9')
		{
			fprintf(stderr,"Invalid command");
			return;
		}
		else
		{
			period = 10 * period + list[siz - 1][i] - '0';
		}
    }
    for (int i = 0; i < list[siz - 3][i] != '\0'; i++) {
        if (list[siz - 3][i] < '0' || list[siz - 3][i] > '9')
		{
			fprintf(stderr,"Invalid command");
			return;
		}
		else
		{
			interval = 10 * interval + list[siz - 3][i] - '0';
		}
    }
    int timer = 0;
    list[siz - 4] = NULL;
    while(timer < period) {
        sleep(1);
        timer++;
        if(timer > 0 && timer % interval == 0)
            execute(makecommand(list + 2));
        
    }

}

#endif