struct Person{
	char *name;
	struct Person *favorite;
};

struct Team{
	int population;
	struct Person *people;
};

struct Team create_team(int population, char *names[], int *favorites);
void free_team(struct Team *team);
struct Person* pick_leader(struct Team* team);
