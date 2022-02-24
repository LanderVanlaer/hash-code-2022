#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 21
#define FILENAME "../resource/d_dense_schedule.in.txt"
#define FILENAME_OUT "../out/d_dense_schedule.out.txt"

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

typedef struct
{
    Project project;
    Contributor *contributors;
    int disable;
} PlannedProject;

int NContributors; // 1 <= N <= 100000
int NProjects;     // 1 <= N <= 100000

Contributor *contributors;
Project *projects;
PlannedProject *plannedProjects;

void printContributors(Contributor *contribs, int NContributors);
void printProjects(Project *prjts, int NProjects);
int compareProjects(Project *project1, Project *project2);
int getContributors(Contributor returnContributors[], Role role, PlannedProject plannedProject, int plannedProjectSize);
void print2file(PlannedProject *plndPrjcts, FILE *fpwrite);

int main()
{
    FILE *fp;
    fp = fopen(FILENAME, "r");

    if (fp == NULL)
    {
        printf("File could not be read.");
        exit(-1);
    }

    FILE *fpwrite;
    fpwrite = fopen(FILENAME_OUT, "w");

    if (fpwrite == NULL)
    {
        printf("Something wen wring ;)");
        exit(-1);
    }

    //LINE 1
    NContributors; // 1 <= N <= 100000
    NProjects;     // 1 <= N <= 100000
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

//    printContributors(contributors, NContributors);
//    printProjects(projects, NProjects);

    plannedProjects = (PlannedProject *) malloc(sizeof(PlannedProject) * NProjects);

    for (int i = 0; i < NProjects; ++i)
    {
        PlannedProject plannedProject;
        //voor elk project
        plannedProject.project = projects[i];
        plannedProject.contributors = (Contributor *) malloc(sizeof(Contributor) * plannedProject.project.rolesSize);
        plannedProject.disable = 0;

        for (int j = 0; j < plannedProject.project.rolesSize; ++j)
        {
            Role role = plannedProject.project.roles[j];
            //voor elke role

            //zoeken we alle contributors (en zetten deze in een array)
            Contributor *returnContributors = (Contributor *) malloc(sizeof(Contributor) * NContributors);
            int size = getContributors(returnContributors, role, plannedProject, j);

            if (!size)
            {
                free(returnContributors);
                plannedProject.disable = 1;
                continue;
            }

            //nemen we een random persoon
            int random = rand() % size;

            //en voegen we deze toe aan de role
            plannedProject.contributors[j] = returnContributors[random];

            free(returnContributors);
        }

        plannedProjects[i] = plannedProject;
    }

    print2file(plannedProjects, fpwrite);

    fclose(fp);
    fclose(fpwrite);
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

int getContributors(Contributor *returnContributors, Role role, PlannedProject plannedProject, int plannedProjectSize)
{
    int length = 0;

    for (int i = 0; i < NContributors; ++i)
    {
        Contributor contributor = contributors[i];
        for (int j = 0; j < contributor.skillsLen; ++j)
        {
            if (!strcmp(contributor.skills[j].name, role.skillName) &&
                contributor.skills[j].level >= role.requiredLevel)
            {
                char able = 1;
                for (int k = 0; k < plannedProjectSize && able; ++k)
                    if (!strcmp(plannedProject.contributors[k].name, contributor.name))
                        able = 0;

                if (able)
                    returnContributors[length++] = contributor;
            }
        }
    }
    return length;
}

void print2file(PlannedProject *plndPrjcts, FILE *fpwrite)
{
    int counter = 0;
    for (int i = 0; i < NProjects; ++i)
    {
        if (!plndPrjcts[i].disable)
            ++counter;
    }

    fprintf(fpwrite, "%d\n", counter);

    for (int i = 0; i < NProjects; ++i)
    {
        if (plndPrjcts[i].disable == 1) continue;

        fprintf(fpwrite, "%s\n", plndPrjcts[i].project.name);

        for (int j = 0; j < plndPrjcts[i].project.rolesSize; ++j)
        {
            fprintf(fpwrite, "%s ", plndPrjcts[i].contributors[j].name);
        }
        fputs("\n", fpwrite);
    }
}

