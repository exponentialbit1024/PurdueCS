#include "team.h"

char* _strdup(char *s){
	return strcpy(malloc(sizeof(*s) * (strlen(s) + 1)), s);
}

static int _maxlength(struct Team *team){
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

//generic function to create and allocate basic names to nodes of the Team linked list, this has been written to reduce the amount of repetative code required by other functions, by doing the redundant task of creating node and incrementing tail for the other functions to take charge after the task is done.
//Also this function returns the node address for any other function to do anything with.
//This could create a confusion regarding the number of times malloc is assigned, but seen on a bigger scale, it is actually creates a better readability by localizing instances of mallocs
struct PersonNode *_nodeCreator(struct Team *team, int headFlag, char * data){
	if(headFlag == 1){
		team -> head = malloc(sizeof(*team->head));		// need to free this later in a loop
		team -> head -> value = malloc(sizeof(*team->head->value));		//need to free this later in a loop
		team -> head -> value -> name = _strdup(data);
		team -> head -> next = NULL;
		team -> head -> prev = NULL;
		team -> tail = team -> head;
		return team -> head;
	}
	else if(headFlag == 0){
		struct PersonNode *newNode = malloc(sizeof(*newNode));	//need to free this later in a loop
		team -> tail -> next = newNode;
		newNode -> value = malloc(sizeof(*newNode -> value));		//need to free this later in a loop
		newNode -> value -> name = _strdup(data);
		newNode -> prev = team -> tail -> prev;
		team -> tail = newNode;
		team -> tail -> next = NULL;
		return team -> tail;
	}
	return NULL; // if something tries to break the conditional switch, and later hopefully the program exits gracefully.
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
			_nodeCreator(&team, 1, people[j].name); 		//one instance of redundancy decreased
		}
		else{
			_nodeCreator(&team, 0, people[j].name);
		}
	}
	struct PersonNode *favAdder = team.head;
	int k = 0;
	while(favAdder != NULL){
			favAdder -> value -> favorite = find_person(&team, people[k].favorite -> name); 
			favAdder = favAdder -> next;
			k++;
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
		struct PersonNode *newNode = _nodeCreator(team, 1, name);
		newNode -> value -> favorite = find_person(team, favorite_name);
	}
	else{
		struct PersonNode *newNode = _nodeCreator(team, 0, name);
		newNode -> value -> favorite = find_person(team, favorite_name);
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

struct Team copy_team(struct Team *team){
	struct Team copy_team; 
	struct PersonNode *traverser = team -> head;
	struct PersonNode *copyNewHead = NULL;
	struct PersonNode *copyNewTail = NULL;

	copy_team.name = _strdup(team -> name);

	copy_team.head = copyNewHead;
	copy_team.tail = copyNewTail;
	
	if(team -> head == NULL){
		return copy_team;
	}

	_nodeCreator(&copy_team, 1, traverser -> value -> name);
	traverser = traverser -> next;

	while(traverser != NULL){
		_nodeCreator(&copy_team, 0, traverser -> value -> name);
		traverser = traverser -> next;
	}
	
	struct PersonNode *copyFavAdder = copy_team.head;
	traverser = team -> head;
	while(copyFavAdder != NULL){
			copyFavAdder -> value -> favorite = find_person(&copy_team, traverser -> value -> favorite -> name); 
			copyFavAdder = copyFavAdder -> next;
			traverser = traverser -> next;
	}
	return copy_team;
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
	int maxlen = _maxlength(team);
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
				fprintf(stream,"           ");
				fprintf(stream, "%s", printer -> value -> name);
			}
			for(int j = 0; j < maxlen - strlen(printer -> value -> name)+1;j++){
				fprintf(stream, " ");
			}
			fprintf(stream, "(favorite: %s)\n", printer -> value -> favorite -> name);
			printer = printer -> next;
		}
	}
}
