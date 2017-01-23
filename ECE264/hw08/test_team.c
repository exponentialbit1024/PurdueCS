#include "team.h"

struct Team create_test_team(){
//	struct Person people[] = {
//		{ .name = "Dhiman", .favorite = &people[1]},
//		{ .name = "Sid", .favorite = &people[0]},
//		{ .name = "Binoy", .favorite = &people[1]},
//		{ .name = "LOLer", .favorite = &people[2]},
//	};

	struct Person people[] = {
		{ .name = "Sid", .favorite = &people[0]},
	};
	return create_team("Peeps", sizeof(people) / sizeof(struct Person), people);
}

int main(int argc, char *argv[]){

	struct Team team0 = create_team("NULL!", 0, NULL);
	fprint_team(&team0, stdout);
	free_team(&team0);

	struct Team team1 = create_test_team();
	fprint_team(&team1, stdout);
	free_team(&team1);

	struct Team team2 = create_test_team();
	add_person(&team2, "Yoda","Sid");
	fprint_team(&team2, stdout);
	free_team(&team2);

	struct Team team = create_test_team();
	struct Person *detachPer = detach_person(&team, "Sid");
	fprint_team(&team, stdout);
	add_person(&team, "Yoda", "Yoda");
	fprint_team(&team, stdout);
	free_person(detachPer);
	free_team(&team);
	
	struct Team team3 = create_test_team();
	struct Person *det4 = detach_person(&team3, "LOLer");
	struct Person *det3 = detach_person(&team3, "Binoy");
	struct Person *det2 = detach_person(&team3, "Sid");
	struct Person *det1 = detach_person(&team3, "Dhiman");
	fprint_team(&team3, stdout);
	free_person(det1);
	free_person(det2);
	free_person(det3);
	free_person(det4);
	free_team(&team3);

	struct Team team4 = create_test_team();
	struct Person *det5 = detach_person(&team4, "Dhiman");
	struct Person *det7 = detach_person(&team4, "Binoy");
	struct Person *det8 = detach_person(&team4, "LOLer");
	fprint_team(&team4, stdout);
	add_person(&team4, "Yoda", "Sid");
	fprint_team(&team4, stdout);
	free_person(det5);
	free_person(det7);
	free_person(det8);
	free_team(&team4);
	
	struct Team team5 = create_test_team();
	struct Person *det9 = detach_person(&team5, "Dhiman");
	struct Person *det10 = detach_person(&team5, "Binoy");
	struct Person *det11 = detach_person(&team5, "LOLer");
	struct Person *det12 = detach_person(&team5, "Sid");
	fprint_team(&team5, stdout);
	add_person(&team5, "Yoda", "Yoda");
	fprint_team(&team5, stdout);
	free_person(det9);
	free_person(det10);
	free_person(det11);
	free_person(det12);
	free_team(&team5);

	struct Team team6 = create_team("NULL!", 0, NULL);
	add_person(&team6, "Sid", "Sid");
	add_person(&team6, "Dhiman", "Sid");
	fprint_team(&team6, stdout);
	struct Person *det13 = detach_person(&team6, "Dhiman");	
	fprint_team(&team6, stdout);
	free_person(det13);
	free_team(&team6);

	struct Team team7 = create_test_team();
	add_person(&team7, "Hello","Sid");
	add_person(&team7, "Hell2", "Hello");
	fprint_team(&team7, stdout);
	free_team(&team7);
	return EXIT_SUCCESS;
}
