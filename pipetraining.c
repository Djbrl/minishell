#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **av)
{
    int fd[2];
    int tmp[2];
    int tmp2[2];
    int status;

    pipe(fd);
    pipe(tmp);
    pipe(tmp2);

    
    // dup2(fd[0], 0);
    // dup2(fd[1], 1);
    pid_t pid1 = fork();
    if (pid1 < 0)
        return (0);
    if (pid1 == 0)
    {
        close(tmp2[1]);
        close(tmp2[0]);
        close(tmp[1]);
        close(tmp[0]);
        close(fd[0]);
        
        dup2(fd[1], 1);
        close(fd[1]);
        char *expr[] = {"ls", NULL};
        execvp("/bin/ls", expr);
        return 0;
    }

    pid_t pid2 = fork();
    if (pid2 < 0)
        return (0);
    if (pid2 == 0)
    {
        close(tmp[0]);
        close(tmp2[0]);
        close(tmp2[1]);

        dup2(fd[0], 0);
        dup2(tmp[1], 1);

        close(fd[0]);
        close(fd[1]);
        close(tmp[1]);
        char *expr[] = {"wc", NULL};
        execvp("/bin/wc", expr);
    }

    pid_t pid3 = fork();
    if (pid3 < 0)
        return (0);
    if (pid3 == 0)
    {
        close(tmp[0]);
        close(tmp2[0]);
    
        dup2(tmp[0], 0);
        dup2(tmp2[1], 1);

        close(fd[0]);
        close(fd[1]);
        close(tmp[1]);
        char *expr[] = {"wc", NULL};
        execvp("/bin/wc", expr);
    }

    pid_t pid4 = fork();
    if (pid4 < 0)
        return (0);
    if (pid4 == 0)
    {
        close(tmp[0]);
        close(tmp[1]);
        //close(fd[1]);
        close(fd[0]);

        close(tmp2[1]);
        dup2(tmp2[0], 0);
        
        dup2(fd[1], 1);

        //close(tmp2[0]);
        char *expr[] = {"wc", "-w", NULL};
        execvp("/bin/wc", expr);
    }

    close(fd[0]);
    close(fd[1]);
    close(tmp[0]);
    close(tmp[1]);
    close(tmp2[0]);
    close(tmp2[1]);
    waitpid(pid1, &status, WUNTRACED);
    waitpid(pid2, &status, WUNTRACED);
    waitpid(pid3, &status, WUNTRACED);
    waitpid(pid4, &status, WUNTRACED);
    // waitpid(pid3, &status, WUNTRACED);
    return (0);
}
