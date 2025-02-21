#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void err(char *str) {
    while (*str)
        write(2, str++, 1);
}

int cd(int argc, char **argv) {
    if (argc != 2)
        return err("error: cd: bad arguments\n"), 1;
    if (chdir(argv[1]) == -1)
        return err("error: cd: cannot change directory to "), err(argv[1]), err("\n"), 1;
    return 0;
}

void set_pipe(int has_pipe, int *fd, int dir) {
    if (has_pipe && (dup2(fd[dir], dir) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        err("error: fatal\n"), exit(1);
}

int exec(int argc, char **argv, char **envp) {
    int has_pipe, fd[2], pid, status;

    has_pipe = argv[argc] && !strcmp(argv[argc], "|");

    if (!has_pipe && !strcmp(argv[0], "cd"))
        return cd(argc, argv);

    if (has_pipe && pipe(fd) == -1)
        err("error: fatal\n"), exit(1);

    if ((pid = fork()) == -1)
        err("error: fatal\n"), exit(1);

    if (!pid) {
        argv[argc] = 0;
        set_pipe(has_pipe, fd, 1);
        if (!strcmp(argv[0], "cd"))
            exit(cd(argc, argv));
        execve(*argv, argv, envp);
        err("error: cannot execute "), err(argv[0]), err("\n"), exit(1);
    }
    waitpid(pid, &status, 0);
    set_pipe(has_pipe, fd, 0);
    return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    int i = 0, status = 0;

    while (argv[i])
    {
        argv += i + 1;
        i = 0;
        while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
            i++;
        if (i)
            status = exec(i, argv, envp);
    }
    return status;
}
