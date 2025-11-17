#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planner.h"

int main()
{
    Plan *p = initPlan();
    if (!p)
    {
        printf("Failed to initialize planner.\n");
        return 1;
    }
    printf("===========================================\n");
    printf("   Welcome to Study Planner System!\n");
    printf("===========================================\n");
    int run = 1;
    char in[100];
    char nm[NAME_MAX];
    int id, hrs, pri, f, t,ch;
    while (run)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Add Subject\n");
        printf("2. Update Hours\n");
        printf("3. Change Priority\n");
        printf("4. Remove Subject\n");
        printf("5. Add Dependency\n");
        printf("6. Remove Dependency\n");
        printf("7. Show All Subjects\n");
        printf("8. Balance Analysis\n");
        printf("9. Study Order\n");
        printf("0. Exit\n");
        printf("==========================\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        getchar();
        switch (ch)
        {
            case 1:
                printf("\nSubject name: ");
                fgets(nm, sizeof(nm), stdin);
                nm[strcspn(nm, "\n")] = '\0';
                
                printf("Hours: ");
                fgets(in, sizeof(in), stdin);
                hrs = atoi(in);
                
                printf("Priority: ");
                fgets(in, sizeof(in), stdin);
                pri = atoi(in);
                
                id = addSub(p, nm, hrs, pri);
                if (id >= 0)
                    printf("Subject added! ID: %d\n", id);
                else
                    printf("Failed to add subject.\n");
                break;
            
            case 2:
                printf("\nSubject ID: ");
                fgets(in, sizeof(in), stdin);
                id = atoi(in);
                
                printf("New hours: ");
                fgets(in, sizeof(in), stdin);
                hrs = atoi(in);
                
                if (updHrs(p, id, hrs) == 0)
                    printf("Hours updated!\n");
                else
                    printf("Failed to update.\n");
                break;
            
            case 3:
                printf("\nSubject ID: ");
                fgets(in, sizeof(in), stdin);
                id = atoi(in);
                
                printf("New priority: ");
                fgets(in, sizeof(in), stdin);
                pri = atoi(in);
                
                if (updPri(p, id, pri) == 0)
                    printf("Priority updated!\n");
                else
                    printf("Failed to update.\n");
                break;
            
            case 4:
                printf("\nSubject ID: ");
                fgets(in, sizeof(in), stdin);
                id = atoi(in);
                
                if (remSub(p, id) == 0)
                    printf("Subject removed!\n");
                else
                    printf("Failed to remove.\n");
                break;
            
            case 5:
                printf("\nPrerequisite ID: ");
                fgets(in, sizeof(in), stdin);
                f = atoi(in);
                
                printf("Dependent ID: ");
                fgets(in, sizeof(in), stdin);
                t = atoi(in);
                
                if (addDep(p, f, t) == 0)
                    printf("Dependency added!\n");
                else
                    printf("Failed to add dependency.\n");
                break;
            
            case 6:
                printf("\nPrerequisite ID: ");
                fgets(in, sizeof(in), stdin);
                f = atoi(in);
                
                printf("Dependent ID: ");
                fgets(in, sizeof(in), stdin);
                t = atoi(in);
                
                if (remDep(p, f, t) == 0)
                    printf("Dependency removed!\n");
                else
                    printf("Dependency not found.\n");
                break;
            
            case 7:
                showPlan(p);
                break;
            
            case 8:
                showBal(p);
                break;
            
            case 9:
                showOrder(p);
                break;
            
            case 0:
                run = 0;
                printf("\nThank you!\n");
                break;
            
            default:
                printf("Invalid choice.\n");
        }
    }
    
    freePlan(p);
    return 0;
}