#include<stdlib.h>
#include "team.h"

int _strlength(char *string);

int _strlength(char *string){
	int len = 0;
	while(string[len] != '\0'){
		len++;
	}
	len++;
	return(len);
}

struct Team create_team(int population, char* names[], int* favorites){
	struct Team team;
	team.population = population;
	
	team.people = malloc(population*sizeof(struct Person));
	int sc = 0;
	for(int k = 0; k < population; k++){
		team.people[k].name = malloc(_strlength(names[k])*sizeof(*names[k]));
		while(names[k][sc] != '\0'){
			team.people[k].name[sc] = names[k][sc];
			sc++;
		}
		team.people[k].name[sc] = '\0';
		sc = 0;
		team.people[k].favorite = &team.people[favorites[k]];
	}
	return(team);	
}

void free_team(struct Team *team){
	int population = team -> population;
	for(int q = 0; q < population; q++){
		free(team -> people[q].name);
	}
	free(team -> people);
}

struct Person* pick_leader(struct Team* team){
	int population = team -> population;
	
	int maxCounter = 0;
	int counter = 0;
	int favPos = 0;
	int j = 0;

	for(j = 0; j < population; j++){
		counter  = 0;
		for(int k = 0; k < population; k++){
			if(team -> people[j].name  == team -> people[k].favorite -> name){
				counter++;
			}
			if(maxCounter < counter){
				maxCounter = counter;
				favPos = j;
			}
		}
	}
	return &team -> people[favPos];
}
