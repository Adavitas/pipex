/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:40:48 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/03 20:01:09 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipe(int d[2])
{
	close(d[0]);
	close(d[1]);
}

static pid_t	spawn_child(void (*child_fn)(char **, char **, int *),
		char **argv, char **envp, int d[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_pipe(d);
		ft_error("Error: Failed to fork\n", 1);
	}
	if (pid == 0)
		child_fn(argv, envp, d);
	return (pid);
}

static int	wait_children(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	if (WIFSIGNALED(status2))
		return (128 + WTERMSIG(status2));
	return (1);
}

static int	handle_two_cmds(char **argv, char **envp)
{
	int		d[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(d) == -1)
		ft_error("Error: Failed to create pipe\n", 1);
	pid1 = spawn_child(child_in, argv, envp, d);
	pid2 = spawn_child(child_out, argv, envp, d);
	close_pipe(d);
	return (wait_children(pid1, pid2));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		ft_error("Error: Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
	if (strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0
		&& ft_strlen(argv[1]) == ft_strlen("here_doc"))
		return (run_here_doc(argv, envp));
	if (argc == 5)
		return (handle_two_cmds(argv, envp));
	return (run_pipeline(argc, argv, envp));
}
