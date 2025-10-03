/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:45:56 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/03 19:51:31 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanup_here_doc(char *line, int fd)
{
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
}

static int	write_here_doc(char *limiter)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		ft_error("Error: Failed to create temp\n", 1);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	cleanup_here_doc(line, fd);
	return (0);
}

static char	**build_here_argv(char **argv, int *new_argc)
{
	char	**new_argv;
	int		count;
	int		i;

	count = 0;
	while (argv[count])
		count++;
	*new_argc = count - 1;
	new_argv = malloc(sizeof(char *) * (*new_argc + 1));
	if (!new_argv)
		ft_error("Error: malloc failed\n", 1);
	new_argv[0] = argv[0];
	new_argv[1] = ".here_doc_tmp";
	i = 3;
	while (argv[i])
	{
		new_argv[i - 1] = argv[i];
		i++;
	}
	new_argv[*new_argc] = NULL;
	return (new_argv);
}

int	run_here_doc(char **argv, char **envp)
{
	char	**new_argv;
	int		new_argc;
	int		rc;

	write_here_doc(argv[2]);
	new_argv = build_here_argv(argv, &new_argc);
	rc = run_pipeline(new_argc, new_argv, envp);
	free(new_argv);
	unlink(".here_doc_tmp");
	return (rc);
}
