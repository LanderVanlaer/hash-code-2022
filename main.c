#define _CRT_SECURE_NO_WARNINGS

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
    Role *roles;
} Project;

Contributor *contributors;
Project *projects;

void printContributors(Contributor *contribs, int NContributors);
void printProjects(Project *prjts, int NProjects);
int compareProjects(Project *project1, Project *project2);

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

    contributors = (Contributor *) malloc(sizeof(Contributor) * NContributors);
    projects = (Project *) malloc(sizeof(Project) * NProjects);

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

    for (int i = 0; i < NProjects; ++i)
    {
        Project project;
        fscanf(fp, "%s%d%d%d%d%*c", project.name, &project.numberOfDaysToComplete, &project.score,
               &project.bestBeforeDays,
               &project.rolesSize);

        project.roles = (Role *) malloc(sizeof(Role) * project.rolesSize);

        for (int j = 0; j < project.rolesSize; ++j)
        {
            Role role;
            fscanf(fp, "%s%d%*c", role.skillName, &role.requiredLevel);
            project.roles[j] = role;
        }
        projects[i] = project;
    }

    qsort(projects, NProjects, sizeof(Project), (_CoreCrtNonSecureSearchSortCompareFunction) compareProjects);

    printContributors(contributors, NContributors);
    printProjects(projects, NProjects);


    return 0;
}

void printContributors(Contributor *contribs, int NContributors)
{
    for (int i = 0; i < NContributors; ++i)
    {
        printf("%s\n", contribs[i].name);
        for (int j = 0; j < contribs[i].skillsLen; ++j)
        {
            printf("-> %s %d\n", contribs[i].skills[j].name, contribs[i].skills[j].level);
        }
        printf("\n");
    }
}

void printProjects(Project *prjts, int NProjects)
{
    for (int i = 0; i < NProjects; ++i)
    {
        printf("%s | Best Before: %d | Score: %d\n", prjts[i].name, prjts[i].bestBeforeDays, prjts[i].score);
        for (int j = 0; j < prjts[i].rolesSize; ++j)
        {
            printf("-> %s %d\n", prjts[i].roles[j].skillName, prjts[i].roles[j].requiredLevel);
        }
        printf("\n");
    }
}

int compareProjects(Project *project1, Project *project2)
{
    //<0 The element pointed by p1 goes before the element pointed by p2
    //0  The element pointed by p1 is equivalent to the element pointed by p2
    //>0 The element pointed by p1 goes after the element pointed by p2
    if (project1->score < project2->score)
        return 1;
    if (project1->score > project2->score)
        return -1;
    if (project1->bestBeforeDays > project2->bestBeforeDays)
        return 1;
    if (project1->bestBeforeDays < project2->bestBeforeDays)
        return -1;
    return 0;
}

