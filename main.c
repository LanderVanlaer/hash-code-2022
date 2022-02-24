#include <stdio.h>

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

char *skills[SKILL_LENGTH];

Contributor *contributors;
Project *projects;

int main()
{
    printf("Hello, World!\n");
    return 0;
}
