#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        volatile int *bad = (volatile int *)1;
        *bad = 42;
        _exit(2);
    }
    int status;
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFSIGNALED(status))
        printf("Child received signal %d\n", WTERMSIG(status));
    else
        printf("Child exited normally with status %d\n", WEXITSTATUS(status));
    return 0;
}
