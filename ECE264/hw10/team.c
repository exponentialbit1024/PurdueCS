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
		favAdder -> value -> favorites = people[k].favorites; 
		Favorites tempHead = favAdder -> value -> favorites;
		while(favAdder -> value -> favorites != NULL){
			favAdder -> value -> favorites -> value = find_person(&team, people[k].favorites -> value -> name);
			favAdder -> value -> favorites = favAdder -> value -> favorites -> next;
			people[k].favorites = people[k].favorites -> next;
		}
		favAdder -> value -> favorites = tempHead;
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

struct Person *add_person(struct Team *team, char *name, Favorites favorites){
	if(team -> head == NULL){
		struct PersonNode *newNode = _nodeCreator(team, 1, name);
		newNode -> value -> favorites = favorites; 
	}
	else{
		struct PersonNode *newNode = _nodeCreator(team, 0, name);
		newNode -> value -> favorites = favorites;
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
			copyFavAdder -> value -> favorites = traverser -> value -> favorites; 
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
	pick_leader(team);
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
			fprintf(stream, "(favorite: %s)\n", printer -> value -> favorites -> value -> name);
		//	fprintf(stream, "(favorite: %s)\n", printer -> value -> favorites -> next -> value -> name);
			printer = printer -> next;
		}
	}
	printer = team -> head;
	while(printer != NULL){
		while(printer -> value -> favorites != NULL){
			Favorites tempDel = printer -> value -> favorites -> next;
			free(printer -> value -> favorites);
			printer -> value -> favorites = tempDel;
		}
		printer = printer -> next;
	}
}

Favorites create_favorites(struct Person* first_choice, ...){
	va_list favList;
	va_start (favList, first_choice); 
	Favorites fav = malloc(sizeof(*fav));
	Favorites favHead = fav;
	fav -> prev = NULL;
	struct Person *node = first_choice;
	fav -> value = node;
	node = va_arg(favList, struct Person *);

	while(node != NULL){
		fav -> next = malloc(sizeof(*fav));
		fav -> next -> value = node;
		fav -> next -> prev = fav;
		fav = fav -> next;
		node = va_arg(favList, struct Person *);
		fav -> next = NULL;
	}
	va_end(favList);
	return favHead;
}

int llLength(struct Team *team){
	int length = 0;
	struct PersonNode *trv = team -> head;
	while(trv != NULL){
		length++;
		trv = trv -> next;
	}
	return length;
}

int _maxInd(int *favList, int counter){
	int maxIdx = 0;
	int max = 0;
	for(int j = 0; j < counter; j++){
		if(favList[j] > max){
			max = favList[j];
			maxIdx = j;
		}
	}
	return maxIdx;
}

int _minInd(int *favList, int counter){
	int minIdx = 0;
	int min = 0;
	for(int j = 0; j < counter; j++){
		if(favList[j] < min){
			min = favList[j];
			minIdx = j;
		}
	}
	return minIdx;
}

int *leader_print(struct Team *team, struct PersonNode *traverser, struct PersonNode *t2){
	int maxVotes = 0;
	int population = llLength(team);

	int *firstFavs = malloc(sizeof(int)*population);
	int i = 0;
	while(traverser != NULL){
		while(t2 != NULL){
			if(strcmp(traverser -> value -> name, t2 -> value -> favorites -> value -> name) == 0){
				printf("%s\n", t2 -> value -> favorites -> value -> name);
				maxVotes++;
			}
			t2 = t2 -> next;
		}
		firstFavs[i] = maxVotes;
		i++;
		maxVotes = 0;
		t2 = traverser;
		traverser = traverser -> next;
	}
	int maxIdx = _maxInd(firstFavs, population);
	if((double)firstFavs[maxIdx] * 100 / population > 50){
		struct PersonNode *tv = team -> head;
		for(int t = 0; t < maxIdx; t++){
			tv = tv -> next;
		}
		firstFavs = NULL;
		fprintf(stdout, "- leader:  %s\n", tv -> value -> name);
	}
	return firstFavs;
}

struct Person *pick_leader(struct Team *team){
	int population = llLength(team);
	struct Team cteam = copy_team(team);
	struct PersonNode *traverser = cteam.head;
	struct PersonNode *t2 = cteam.head;
	
	int *favVoteList = leader_print(&cteam, traverser, t2);
	while(favVoteList != NULL){
		int minIdx = _minInd(favVoteList, population);
		struct PersonNode *tvO = cteam.head;
		for(int u = 0; u < minIdx; u++){
			tvO = tvO -> next;
		}
		struct PersonNode *tempDele = tvO;
		tvO = tvO -> next;
		free(tempDele);
		printf("%d\n", minIdx);
		favVoteList = leader_print(&cteam, traverser, t2);
	}
//	double perVotes = 100 * maxVotes / population;
//	if(perVotes > 50){
//		fprintf(stdout, "- leader:  %s\n", traverser -> value -> name);
//	}
	free(favVoteList);
	free_team(&cteam);
	return NULL;
}

void add_favorite(struct Person* fan, struct Person* favorite, int rank){
	struct PersonNode *trvsr = malloc(sizeof(*trvsr));
	
}
