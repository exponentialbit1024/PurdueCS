#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

typedef struct PersonNode *Favorites;

struct voteMap{
	Favorites fav;
	int votes;
};

struct PersonNode{
	struct Person *value;		//value of the LL Node
	struct PersonNode *next;
	struct PersonNode *prev;
};

struct Person{
	char * name;
	Favorites favorites;
};

struct Team{
	char *name;
	struct PersonNode *head;
	struct PersonNode *tail;
};

struct Team create_team(char *name, int population, struct Person *people);
struct Team copy_team(struct Team *original);
struct Team create_test_team();
void free_team(struct Team *team);
void free_person(struct Person *person);
struct Person *add_person(struct Team *team, char *name, Favorites favorites);
struct Person *detach_person(struct Team *team, char *name);
struct Person *find_person(struct Team *team, char *name);
Favorites create_favorites(struct Person* first_choice, ...);
void add_favorite(struct Person *fan, struct Person *favorite, int rank);
struct Person *pick_leader(struct Team *team);
void fprint_team(struct Team *team, FILE *stream);

char * _strdup(char *s);

