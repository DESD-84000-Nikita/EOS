#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pids[4]; // Array to store child process IDs
    int status;
    
    char *source_files[] = {"circle.c", "square.c", "rectangle.c", "main.c"};

    // Fork child processes to compile each source file
    for (int i = 0; i < 4; i++) {
        child_pids[i] = fork();
        if (child_pids[i] == 0) {
            char *command = "gcc";
            char *args[] = {command, "-c", source_files[i], NULL};
            execvp(command, args);
            exit(EXIT_FAILURE); // If execvp fails
        }
    }

    // Wait for all compilation child processes to finish
    for (int i = 0; i < 4; i++) {
        waitpid(child_pids[i], &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            printf("Compilation of %s failed\n", source_files[i]);
            exit(EXIT_FAILURE);
        }
    }

    // Link object files
    pid_t link_pid = fork();
    if (link_pid == 0) {
        char *args[] = {"gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL};
        execvp(args[0], args);
        exit(EXIT_FAILURE); // If execvp fails
    }

    // Wait for the linking process to finish
    waitpid(link_pid, &status, 0);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        printf("Linking failed\n");
        exit(EXIT_FAILURE);
    }

    // Run the executable
    pid_t run_pid = fork();
    if (run_pid == 0) {
        execl("./program.out", "program.out", NULL);
        exit(EXIT_FAILURE); // If execl fails
    }

    // Wait for the executable to finish
    waitpid(run_pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    } else {
        printf("Child terminated abnormally\n");
    }

    return 0;
}
