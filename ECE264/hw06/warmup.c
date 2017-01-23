 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char* string){
	int len = 0;
	while(string[len] != '\0'){
		len++;
	}
	return(len);
}

char* my_strdup(const char* original) {
	// TODO
	char *dupstr = malloc(my_strlen(original)*sizeof(original));
	int len = 0;
	while(original[len] != '\0'){
		dupstr[len] = original[len];
		len++;
	}
	dupstr[len] = '\0';
	return(dupstr);
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}
