#include <stdlib.h>

char* sub_string(char *in_string, int start_index, int end_index){
	char *out_string = (char *)malloc(sizeof(char) * (end_index - start_index));
	int i;
	for(i = 0; i < (end_index - start_index + 1); i++){
		out_string[i] = in_string[i + start_index -1];	
	}
	out_string[i] = '\0';
	return out_string;
}
