/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:14:55 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/01 19:15:52 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *err_str, int exit_code)
{
	ft_putstr_fd(err_str, 2);
	exit(exit_code);
}

int	open_outfile(char *path, int append)
{
	if (append)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Failed to open file\n", 1);
	return (fd);
}

t_last_args	ft_args(char **argv, int idx, int append, char **envp)
{
	t_last_args	args;

	args.cmd = argv[idx];
	args.outfile = argv[idx + 1];
	args.append = append;
	args.envp = envp;
	return (args);
}
