#include "pipex.h"

static void ft_free_strs(char **arr)
{
    int index;

	index = 0;
    if (!arr) 
		return;
    while (arr[index])
    {
        free(arr[index]);
        index++;
    }
    free(arr);
}

void	ft_child(char **argv, char **envp, int *fd)
{
	int		input;

    input = open(argv[1], O_RDONLY);
    if (input == -1)
    {
        ft_error("Error: Failed to open file\n", 1);
    }
    dup2(fd[1], STDOUT_FILENO);
	dup2(input, STDIN_FILENO);
	close(fd[0]);
	ft_execute(argv[2], envp);
}

void	ft_parent(char **argv, char **envp, int *fd)
{
	int		output;

    output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output == -1)
    {
        ft_error("Error: Failed to open file\n", 1);
    }
    dup2(fd[0], STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(fd[1]);
	ft_execute(argv[3], envp);
}

char    *ft_get_path(char **envp, char *command)
{
    char    **paths;
    char    *part_path;
    char    *path;
    int        index;

    index = 0;
    while (envp[index] && ft_strnstr(envp[index], "PATH", 4) == 0)
        index++;
    paths = ft_split(envp[index] + 5, ':');
    index = -1;
    while (paths[++index])
    {
        part_path = ft_strjoin(paths[index], "/");
        path = ft_strjoin(part_path, command);
        free(part_path);
        if (access(path, F_OK) == 0)
        {
            ft_free_strs(paths);
            return (path);
        }
        free(path);
    }
    ft_free_strs(paths);
    return (0);
}

void ft_execute(char *str, char **envp)
{
    char    **command;
    char    *path;
    if (!str || *str == '\0')
        ft_error("Error: Empty command\n", 1);
    command = ft_split(str, ' ');
	if (!envp)
        return ;
    path = ft_get_path(envp, command[0]);
    if (!path)    
    {
        ft_free_strs(command);
        ft_error("Error: Command not found\n", 127);
    }
    if (execve(path, command, envp) == -1)
        ft_error("Error: Execution failed\n", 1);
}