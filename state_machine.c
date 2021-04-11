#include <stdio.h>
#include <stdlib.h>

enum state_codes {entry, first, second, end};
enum ret_codes { ok, fail, repeat};

struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};


struct transition state_transitions[] = {
	{entry, ok, first },
	{entry, fail, end},
	{first, ok, second},
	{first, fail, end},
	{first, repeat, first},
	{second, ok, end},
	{second, fail, end},
	{second, repeat, second},
};

int entry_state(void){
	printf("Entry\n");
	return ok;
}
int first_state(void){
	printf("First\n");
	return ok;
}
int second_state(void){
	printf("Second\n");
	return ok;
}
int end_state(void){
	printf("End\n");
	return ok;
}

int (*state[])(void) = {entry_state, first_state, second_state, end_state};


#define EXIT_STATE end
#define ENTRY_STATE entry

int lookup_transitions(int cur_state, int rc){
	for(int i = 0; i < sizeof(state_transitions) / sizeof(*state_transitions); i++){
		if(cur_state == state_transitions[i].src_state){
			if(rc == state_transitions[i].ret_code)
				return state_transitions[i].dst_state;
		}
		
	}
	printf("Error\n");
	return 0;
}



int main(int argc, char *argv[]) {
    enum state_codes cur_state = ENTRY_STATE;
    enum ret_codes rc;
    int (* state_fun)(void);

    for (;;) { 
		sleep(1);
        state_fun = state[cur_state];
        rc = state_fun();
        if (EXIT_STATE == cur_state)
            break;
        cur_state = lookup_transitions(cur_state, rc);
    }

    return EXIT_SUCCESS;
}
	

