#include "team.h"

struct Team create_test_team(){
	struct Person people[] = {
		{ .name = "Kirk", .favorites=create_favorites(&people[1],&people[2],&people[0],NULL)},
		{ .name = "Spock", .favorites=create_favorites(&people[0],&people[1],&people[1],NULL)},
		{ .name = "Uhura", .favorites=create_favorites(&people[1],&people[2],&people[0],NULL)},
		{ .name = "McCoy", .favorites=create_favorites(&people[2],&people[3],NULL)},
	};
	return create_team("TestTeam", sizeof(people)/sizeof(*people), people);
}

int main(int argc, char *argv[]){
//	struct Team team0 = create_team("NULL!",0,NULL);
//	fprint_team(&team0, stdout);
//	free_team(&team0);
	
	struct Team team1 = create_test_team();
	fprint_team(&team1,stdout);
	free_team(&team1);
	return EXIT_SUCCESS;
}
