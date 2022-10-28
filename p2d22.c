typedef struct {

	char name[31];

	int team_id;

	unsigned time;

	char country_code[4];

} runner_t;



typedef struct runner_node {

	runner_t* runner;

	struct runner_node* next;

} runner_node_t;



typedef struct {

	int team_id;

	unsigned time;

	char country_code[4];

} team_t;



typedef struct team_node {

	team_t* team;

	struct team_node* next;

} team_node_t

#include <stdio.h>
#include "type.h"
#include <stdlib.h>

runner_node_t* read_node(FILE* input) {
	runner_node_t* glava = NULL, * stari;
	char buffer[256];
	while (fgets(buffer, 256, input)) {
		runner_node_t* novi = (runner_node_t*)malloc(sizeof(runner_node_t));
		// sscanf(buffer, "%[^d]|%d %d %s", novi->runner->name, &novi->runner->team_id, &novi->runner->time, novi->runner->country_code);
		// novi->next=NULL;
		if (glava == NULL)
			glava = novi;
		// else
		//     stari->next=novi;
		// stari=novi;
	}
	return glava;
}