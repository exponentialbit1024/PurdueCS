#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct Person{
	char * name;
	struct Person *favorite;
};

struct Team{
	char *name;
	struct PersonNode *head;
	struct PersonNode *tail;
};

struct PersonNode{
	struct Person *value;		//value of the LL Node
	struct PersonNode *next;
	struct PersonNode *prev;
};

struct Team create_team(char *name, int population, struct Person *people);
struct Team create_test_team();
void free_team(struct Team *team);
void free_person(struct Person *person);
struct Person *add_person(struct Team *team, char *name, char *favorite_name);
struct Person *detach_person(struct Team *team, char *name);
struct Person *find_person(struct Team *team, char *name);
void fprint_team(struct Team *team, FILE *stream);

char * _strdup(char *s);

