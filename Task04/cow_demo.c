#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    size_t n = 8 * 1024 * 1024;
    unsigned char *p = malloc(n);
    if (!p) { perror("malloc"); return 1; }
    for (size_t i = 0; i < n; i += 4096) p[i] = 1;
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); free(p); return 1; }
    if (pid == 0) { _exit(0); }
    for (size_t i = 0; i < n; i += 4096) p[i] ^= 0xff;
    int status;
    waitpid(pid, &status, 0);
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("COW demo: parent maxrss=%ld KiB; child exit_status=%d\n",
           usage.ru_maxrss, WEXITSTATUS(status));
    puts("This measurement does not prove savings; it reports availability only.");
    free(p);
    return 0;
}
