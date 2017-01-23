#include<stdio.h>
#include<stdlib.h>
#include "team.h"

int main(int argc, char *argv[]){
	char *names[] = {"Sid"};
	int favorites[] = {0};
	struct Team team = create_team(1, names, favorites);
	struct Person *leader = pick_leader(&team);

	char *names0[] = {"Sid","Dhiman"};
	int favorites0[] = {0,0};
	struct Team team0 = create_team(2, names0, favorites0);
	struct Person *leader0 = pick_leader(&team0);

	char *names1[] = {"Sid","Dhiman"};
	int favorites1[] = {0,1};
	struct Team team1 = create_team(2, names1, favorites1);
	struct Person *leader1 = pick_leader(&team1);

	char *names2[] = {"Sid","Dhiman","John", "Mary","Alice","Halie"};
	int favorites2[] = {0,1,1,1,2,0};
	struct Team team2 = create_team(6, names2, favorites2);
	struct Person *leader2 = pick_leader(&team2);

	char *names3[] = {"yoda", "jedi","vader"};
	int favorites3[] = {0,1,2};
	struct Team team3 = create_team(3, names3, favorites3);
	struct Person *leader3 = pick_leader(&team3);

	printf("Population : %d\n", team.population);
	for(int t = 0; t < team.population; t++){
		printf("Person on team : %s\n", team.people[t].name);
		printf("Person's favorite person: %s\n",team.people[t].favorite -> name);
	}
	printf("Leader : %s",leader -> name);	
	printf("\n");

	printf("Population : %d\n", team0.population);
	for(int q = 0; q < team0.population; q++){
		printf("Person on team : %s\n", team0.people[q].name);
		printf("Person's favorite person : %s\n",team0.people[q].favorite -> name);
	}
	printf("Leader  : %s",leader0 -> name);	
	printf("\n");

	printf("Population : %d\n", team1.population);
	for(int i = 0; i < team1.population; i++){
		printf("Person on team : %s\n",team1.people[i].name);
		printf("Person's favorite person : %s\n",team1.people[i].favorite -> name);
	}
	printf("Leader : %s\n", leader1 -> name);
	
	printf("\nPopulation : %d\n", team2.population);
	for(int y = 0; y < team2.population; y++){
		printf("Person on team : %s\n", team2.people[y].name);
		printf("Person's favorite person : %s\n", team2.people[y].favorite -> name);
	}
	printf("Leader : %s\n", leader2 -> name);

	printf("Population : %d\n", team3.population);
	
	for(int a = 0; a < team3.population; a++){
		printf("Person on team : %s\n", team3.people[a].name);
		printf("Person's favorite person : %s\n", team3.people[a].favorite -> name);
	}
	printf("Leader : %s\n", leader3 -> name);

	free_team(&team);
	free_team(&team0);
	free_team(&team1);
	free_team(&team2);
	free_team(&team3);
	return EXIT_SUCCESS;
}
