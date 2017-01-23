#include "team.h"

char* _strdup(char *s){
	return strcpy(malloc(sizeof(*s) * (strlen(s) + 1)), s);
}

static int maxlength(struct Team *team){
	int maxlength = 0;
	struct PersonNode *tempNode = team -> head;
	while(tempNode != NULL){
		if(strlen(tempNode -> value -> name) > maxlength){
			maxlength = strlen(tempNode -> value -> name);
		}
		tempNode = tempNode -> next;
	}
	return maxlength;
}

struct Team create_team(char *name, int population, struct Person *people){
	struct Team team;
	team.name = _strdup(name); //need to free this later
	struct PersonNode *newHead = NULL;
	struct PersonNode *newTail = NULL;
	team.head = newHead;
	team.tail = newTail;
	for(int j = 0; j < population; j++){
		if(team.head == NULL){
			team.head = malloc(sizeof(struct PersonNode));	//need to free this in loop later
			team.head -> value = malloc(sizeof(struct Person));		//need to free this later in a loop
			team.head -> value -> name = _strdup(people[j].name);
			team.head -> next = NULL;
			team.head -> prev = NULL;
			team.tail = team.head;
		}
		else{
			struct PersonNode *newNode = malloc(sizeof(struct PersonNode));	//need to free this later in a loop
			team.tail -> next = newNode;
			newNode -> value = malloc(sizeof(struct Person));
			newNode -> value -> name = _strdup(people[j].name);
			newNode -> prev = team.tail -> prev;
			team.tail = newNode;
			team.tail -> next = NULL;
		}
	}
	if(team.head != NULL){
		struct PersonNode *favAdder = team.head;
		for(int k = 0; k < population; k++){
			favAdder -> value -> favorite = find_person(&team, people[k].favorite -> name);  
			favAdder = favAdder -> next;
		}
	}
	return(team);
}

struct Person *find_person(struct Team *team, char *name){
	struct PersonNode *searchHead = team -> head;
	while(searchHead != NULL){
		if(strcmp(searchHead -> value -> name, name) == 0){
			return searchHead -> value;
		}
		searchHead = searchHead -> next;
	}
	return NULL;
}

struct Person *add_person(struct Team *team, char *name, char *favorite_name){
	if(team -> head == NULL){
		team -> head = malloc(sizeof(struct PersonNode));
		team -> head -> value = malloc(sizeof(struct Person));
		team -> head -> value -> name = _strdup(name);
		team -> head -> value -> favorite = find_person(team, favorite_name);
		team -> head -> next = NULL;
		team -> head -> prev = NULL;
		team -> tail = team -> head;
	}
	else{
		struct PersonNode *newNode = malloc(sizeof(struct PersonNode));
		team -> tail -> next = newNode;
		newNode -> value = malloc(sizeof(struct Person));
		newNode -> value -> name = _strdup(name);
		newNode -> value -> favorite = find_person(team,favorite_name);
		newNode -> prev = team -> tail -> prev;
		team -> tail = newNode;
		team -> tail -> next = NULL;
	}
	return team -> tail -> value;
}

struct Person *detach_person(struct Team *team, char *name){
	struct PersonNode *searchHead = team -> head;
	struct PersonNode *tempNode = searchHead;
	struct Person *returnVal;
	
	if(searchHead == NULL){
		return NULL;
	}
	
	while(strcmp(searchHead -> value -> name, name) != 0){
		tempNode = searchHead;
		if(searchHead -> next != NULL){
			searchHead = searchHead -> next;
		}
		else{
			return NULL;
		}
	}
	
	if(strcmp(searchHead -> value -> name, team -> tail -> value -> name)==0){
		if(team -> head == team -> tail){
			team -> head -> prev = NULL;
			team -> head = NULL;
		}
		team -> tail = tempNode;
		if(team -> head == team -> tail){
			team -> head -> prev = NULL;
			team -> head -> next = NULL;
		}
	}
	else if(strcmp(searchHead -> value -> name, team -> head -> value -> name)==0){
		team -> head = searchHead -> next;
		team -> head -> prev = NULL;
	}
	else{
		tempNode -> next = searchHead -> next;
		searchHead -> next -> prev = tempNode;
	}
	returnVal = searchHead -> value;
	free(searchHead);
	return(returnVal);
}

void free_person(struct Person *person){
	if(person != NULL){
		free(person -> name);
	}
	free(person);
}

void free_team(struct Team *team){
	free(team -> name);
	while(team -> head  != NULL){
		struct PersonNode *delNode = team -> head -> next;
		free_person(team -> head -> value);
		free(team -> head);
		team -> head = delNode;
	}
}

void fprint_team(struct Team *team, FILE *stream){
	struct PersonNode *printer = team -> head;
	int maxlen = maxlength(team);
	fprintf(stream, "%s\n", team -> name);
	fprintf(stream, "- members: ");
	if(printer == NULL){
		fprintf(stream, "(none)\n");
	}
	else{
		while(printer != NULL){
			if(printer == team -> head){
				fprintf(stream, "%s", printer -> value  -> name);
			}
			else{
				fprintf(stream, "           ");
				fprintf(stream, "%s", printer -> value -> name);
			}
			for(int j = 0; j < maxlen - strlen(printer -> value -> name)+1;j++){
				fprintf(stream, " ");
			}
			fprintf(stream, "(favorites: %s)\n", printer -> value -> favorite -> name);
			printer = printer -> next;
		}
	}
}
