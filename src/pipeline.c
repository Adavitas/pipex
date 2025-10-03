/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:45:46 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/03 20:01:37 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	spawn_intermediate(int fd_in, char *cmd, char **envp, int *fd_out)
{
	pid_t	pid;

	if (pipe(fd_out) == -1)
		ft_error("Error: Failed to create pipe\n", 1);
	pid = fork();
	if (pid == -1)
		ft_error("Error: Failed to fork\n", 1);
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out[1], STDOUT_FILENO);
		close(fd_out[0]);
		close(fd_in);
		ft_execute(cmd, envp);
	}
}

static pid_t	open_and_fork_last(int fd_in, t_last_args *args, int *out_fd)
{
	pid_t	pid;

	*out_fd = open_outfile(args->outfile, args->append);
	if (*out_fd < 0)
		ft_error("Error: Failed to open file\n", 1);
	pid = fork();
	if (pid == -1)
		ft_error("Error: Failed to fork\n", 1);
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(*out_fd, STDOUT_FILENO);
		close(fd_in);
		close(*out_fd);
		ft_execute(args->cmd, args->envp);
	}
	return (pid);
}

static int	collect_last_status(pid_t pid, int fd_in, int out_fd)
{
	int	status;

	close(fd_in);
	close(out_fd);
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	spawn_last_and_wait(int fd_in, t_last_args *args)
{
	pid_t	pid;
	int		out_fd;

	pid = open_and_fork_last(fd_in, args, &out_fd);
	return (collect_last_status(pid, fd_in, out_fd));
}

int	run_pipeline(int argc, char **argv, char **envp)
{
	int			fd_in;
	int			d[2];
	int			index;
	int			append;
	t_last_args	args;

	(void)argc;
	fd_in = open_infile(argv[1]);
	index = 2;
	while (argv[index + 1] && argv[index + 2])
	{
		spawn_intermediate(fd_in, argv[index], envp, d);
		close(d[1]);
		close(fd_in);
		fd_in = d[0];
		index++;
	}
	append = (strcmp(argv[1], ".here_doc_tmp") == 0);
	{
		(void)args;
		args = ft_args(argv, index, append, envp);
		return (spawn_last_and_wait(fd_in, &args));
	}
}
