#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 10
#define MAX_LENGTH 100

typedef struct {
    char description[MAX_LENGTH];
    int completed;
    char shape;
} Task;

void printShape(char shape) {
    switch(shape) {
        case 'S':
            printf("  _____\n /     \\\n|       |\n \\_____/\n"); // Square
            break;
        case 'T':
            printf("   /\\\n  /  \\\n /____\\\n"); // Triangle
            break;
        case 'C':
            printf("   ___\n  /   \\\n |     |\n  \\___/\n"); // Circle
            break;
        case 'D':
            printf("  /\\\n /  \\\n/____\\\n"); // Diamond (simplified)
            break;
        default:
            printf("  ____\n |    |\n |____|\n"); // Default rectangle
    }
}

void displayMenu() {
    printf("\n=== TO-DO LIST WITH SHAPES ===\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Mark Task as Completed\n");
    printf("4. Delete Task\n");
    printf("5. Exit\n");
    printf("==============================\n");
    printf("Enter your choice: ");
}

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("Enter task description: ");
    getchar(); // Clear input buffer
    fgets(tasks[*taskCount].description, MAX_LENGTH, stdin);
    tasks[*taskCount].description[strcspn(tasks[*taskCount].description, "\n")] = '\0'; // Remove newline

    printf("Choose shape for task (S=Square, T=Triangle, C=Circle, D=Diamond): ");
    scanf(" %c", &tasks[*taskCount].shape);

    tasks[*taskCount].completed = 0;
    (*taskCount)++;
    printf("Task added successfully!\n");
}

void viewTasks(Task tasks[], int taskCount) {
    printf("\n=== YOUR TASKS ===\n");
    for (int i = 0; i < taskCount; i++) {
        printf("\nTask %d: %s\n", i+1, tasks[i].description);
        printf("Status: %s\n", tasks[i].completed ? "Completed" : "Pending");
        printf("Shape:\n");
        printShape(tasks[i].shape);
    }
    if (taskCount == 0) {
        printf("No tasks found!\n");
    }
}

void markCompleted(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks to mark as completed!\n");
        return;
    }

    int taskNum;
    viewTasks(tasks, taskCount);
    printf("Enter task number to mark as completed: ");
    scanf("%d", &taskNum);

    if (taskNum < 1 || taskNum > taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    tasks[taskNum-1].completed = 1;
    printf("Task marked as completed!\n");
}

void deleteTask(Task tasks[], int *taskCount) {
    if (*taskCount == 0) {
        printf("No tasks to delete!\n");
        return;
    }

    int taskNum;
    viewTasks(tasks, *taskCount);
    printf("Enter task number to delete: ");
    scanf("%d", &taskNum);

    if (taskNum < 1 || taskNum > *taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    // Shift tasks up to fill the gap
    for (int i = taskNum-1; i < *taskCount-1; i++) {
        tasks[i] = tasks[i+1];
    }

    (*taskCount)--;
    printf("Task deleted successfully!\n");
}

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                markCompleted(tasks, taskCount);
                break;
            case 4:
                deleteTask(tasks, &taskCount);
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
