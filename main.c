#include <stdio.h>
#include <stdlib.h>

#define STRLEN 21
#define FILENAME "../resource/a_an_example.in.txt"

typedef struct
{
    char name[STRLEN];
    short level;
} Skill;

typedef struct
{
    char skillName[STRLEN];
    int requiredLevel;
} Role;

typedef struct
{
    char name[STRLEN];
    int skillsLen;
    Skill *skills;
} Contributor;

typedef struct
{
    char name[STRLEN];
    int numberOfDaysToComplete;
    int score;
    int bestBeforeDays;
    int rolesSize;
    Role roles[];
} Project;

Contributor *contributors;
Project *projects;

int main()
{
    FILE *fp;
    fp = fopen(FILENAME, "r");

    if (fp == NULL)
    {
        printf("File could not be read.");
        exit(-1);
    }

    //LINE 1
    int NContributors; // 1 <= N <= 100000
    int NProjects;     // 1 <= N <= 100000
    fscanf(fp, "%d%d%*c", &NContributors, &NProjects);

    contributors = (Contributor *) malloc(NContributors);
    projects = (Project *) malloc(NProjects);


    for (int i = 0; i < NContributors; ++i)
    {
        Contributor contributor;
        fscanf(fp, "%s%d%*c", contributor.name, &contributor.skillsLen);

        contributor.skills = (Skill *) malloc(sizeof(Skill) * contributor.skillsLen);

        for (int j = 0; j < contributor.skillsLen; ++j)
        {
            Skill skill;
            fscanf(fp, "%s%hd%*c", skill.name, &skill.level);

            contributor.skills[j] = skill;
        }

        contributors[i] = contributor;
    }

    return 0;
}