#include <stdio.h>
#include <stdlib.h>

#define CONTRIBUTOR_NAME_LENGTH 21
#define PROJECT_NAME_LENGTH 21
#define SKILL_LENGTH 21

typedef struct
{
    int id;
    short level;
} Skill;

typedef struct
{
    int id;
    int requiredLevel;
} Role;

typedef struct
{
    char name[CONTRIBUTOR_NAME_LENGTH];
    Skill skills[];
} Contributor;

typedef struct
{
    char name[PROJECT_NAME_LENGTH];
    int numberOfDaysToComplete;
    int score;
    int bestBeforeDays;
    int rolesSize;
    Role roles[];
} Project;

char* skills[SKILL_LENGTH];

Contributor* contributors;
Project* projects;

int main()
{
    printf("Hello, World!\n");
	FILE* fp;
	fp = fopen(FILENAME, "r");

	if(fp == NULL)
	{
		printf("File could not be read.");
		exit(-1);
	}

    //LINE 1
    int NContributors; // 1 <= N <= 100000
    int NProjects;     // 1 <= N <= 100000
    fscanf(fp, "%d%d%c", NContributors, NProjects);

    contributors = (Contributor*) malloc(NContributors);
    projects = (Project*) malloc(NProject);


    return 0;
}
