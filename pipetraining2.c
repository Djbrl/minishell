#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void    exec_pipe_loop(t_child *child, int nb_pipes)
{
    int    fd_next_read;
    int    pipe_fd[2];
    int    i;

    i = 0;
    //tu recuepres la valeur du fd / heredoc , le fd du open en fait
    // parent donne STDIN - STDOUT -> pipe -> enfant -> IN fermer , OUT -> Close des FD dans le parent
    // et sauvegarde de la valeur du pipe pour donner a l'enfant suivant qui aura IN OUT ET PIPE VALUE!
    fd_next_read = get_first_fd(child->heredoc, child->argv[2]);
    while (i < nb_pipes)
    {
        check_syscall(pipe(pipe_fd), "pipe");
        refresh_child(child, fd_next_read, pipe_fd[WRITEFD]);
        child->cmd = child->argv[i + 2 + child->heredoc];
        if (i == 0 && !child->heredoc)
            child->file = child->argv[1];
        if (i + 1 == nb_pipes)
        {
            child->file = child->argv[child->argc - 1];
            close(child->fd_out);
            child->fd_out = -1;
        }
        exec_child(child, pipe_fd);
        fd_next_read = pipe_fd[READFD];
        i++;
    }
    close(fd_next_read);
}

void    exec_child(t_child *child, int pipe_fd[2])
{
    set_oflags(child);
    if (check_syscall(fork(), "fork") == 0)
    {
        close(pipe_fd[READFD]);
        open_in_out_file(child);
        if (child->fd_in != -1)
        {
            check_syscall(dup2(child->fd_in, STDIN_FILENO), "dup2");
            close(child->fd_in);
        }
        if (child->fd_out != -1)
        {
            check_syscall(dup2(child->fd_out, STDOUT_FILENO), "dup2");
            close(child->fd_out);
        }
        exec_cmd(child, child->env);
    }
    close_child_fd(child);
}

int main(int argc, char **av)
{
    int fd[2];
    int tmp[2];
    int status;

    pipe(fd);
    pipe(tmp);
    
return (0);
}