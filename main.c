#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *task;
    int completed; // representing 1 or 0 aka true or false 
}Task;

Task *tasks = NULL;
int length = 0;

void addTask(const char *task) {
    tasks = (Task*)realloc(tasks, (length + 1) * sizeof(Task));
    tasks[length].task = (char*)malloc(strlen(task) + 1);
    tasks[length].completed = 0;
    
    strcpy(tasks[length].task, task);

    length++;
    printf("Task added");
}

void listTask() {
    char status;

    for (int i = 0; i < length; i++) {
        if (tasks[i].completed == 1) {
            status = 'd';
        } else {
            status = 'n';
        }
        printf("%d. %s [%c]\n", i + 1, tasks[i].task, status);
    }
}

void markCompleted(int index) {
    if (index <= length && index > 0) {
        tasks[index - 1].completed = 1;
        printf("Task marked as completed.\n");   
    } else {
        printf("Invalid index\n");
    }
}

void editTask(int index, const char* task) {
    if (index <= length && index >0) {
        index = index -1;

        char* editedTask = (char*)realloc(tasks[index].task, strlen(task) + 1);

        if (editedTask != NULL) {
            tasks[index].task = editedTask;
            strcpy(tasks[index].task, task);
            printf("Task updated success!");
        } else {
            printf("Memory Allocation failed");
        }

    } else {
        printf("Invalid index\n");
    }
}

void deleteTask(int index) {
    if (index <= length && index >0) {
        index = index - 1;

        free(tasks[index].task);
        
        for (int i = index; i < length - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        length--;

        tasks = (Task*)realloc(tasks, (length * sizeof(Task)));

    } else {
        printf("Invalid index\n");
    }
}

int main() {
    int running = 1;
    int choice;
    char taskInput[100];
    int indexInput;

    printf("To-Do Options\n");
    printf("1. Add Task\n");
    printf("2. List Tasks\n");
    printf("3. Mark as Complete\n");
    printf("4. Edit Tasks\n");
    printf("5. Delete Tasks\n");
    printf("6. Exit\n");
    
    while (running) {
        printf("Select an option?\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter task: \n");
                getchar();
                fgets(taskInput, sizeof(taskInput), stdin);
                taskInput[strcspn(taskInput, "\n")] = '0';
                addTask(taskInput);
                break;

            case 2:
                listTask();
                break;

            case 3:
                printf("Provide an index: \n");
                scanf("%d", &indexInput);
                markCompleted(indexInput);
                break;

            case 4:
                printf("Enter Index: \n");
                scanf("%d", &indexInput);
                printf("Provide Edits: \n");
                getchar();
                fgets(taskInput, sizeof(taskInput), stdin);
                taskInput[strcspn(taskInput, "\n")] = '\0';
                editTask(indexInput, taskInput);
                break;

            case 5:
                printf("Enter Index: \n");
                scanf("%d", &indexInput);

                deleteTask(indexInput);
                break;

            case 6:
                running = 0;
                break;

            default:
                printf("Invalid");
                break; //unneeded
        }
    }
    free(tasks);
    
    return 0;
}

