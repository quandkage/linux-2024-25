#pragma once
#include <unistd.h>
#include <sys/wait.h>

int do_command(const char * command) {
    pid_t proc = fork();

    if (proc == -1) {
        perror("fork");
        return -1;
    }
    if (proc == 0) {
        char* const args[] = {"/bin/sh", "-c", (char*)command, NULL};
        execvp(args[0], args);

        perror("execvp");
        return -1;
    } else {
        int st;
        waitpid(proc, &st, 0);

        if (WIFEXITED(st)) {
            return WEXITSTATUS(st);
        }
        else {
            return -1;
        }
    }
}