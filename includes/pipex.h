/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:14:33 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/03 20:00:14 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_last_args
{
	char	*cmd;
	char	*outfile;
	int		append;
	char	**envp;
}			t_last_args;

void			child_in(char **argv, char **envp, int *fd);
void			child_out(char **argv, char **envp, int *fd);
void			ft_error(char *err_str, int exit_code);
char			*ft_get_path(char **envp, char *command);
void			ft_execute(char *str, char **envp);
int				open_outfile(char *path, int append);
int				open_infile(char *path);
int				run_pipeline(int argc, char **argv, char **envp);
int				run_here_doc(char **argv, char **envp);
t_last_args		ft_args(char **argv, int idx, int append, char **envp);

#endif
