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
        char shell[] = "/bin/sh";
        char flag[] = "-c";
        char* args[] = {shell, flag, (char*)command, nullptr};
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