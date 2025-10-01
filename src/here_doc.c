/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobu <nobu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 07:45:00 by nobu              #+#    #+#             */
/*   Updated: 2025/10/01 20:03:35 by nobu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	write_here_doc(char *limiter)
{
    int	fd;
    char	*line;
    size_t	len;
    ssize_t	nread;

    fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
        ft_error("Error: Failed to create temp\n", 1);
    line = NULL;
    len = 0;
    while ((nread = getline(&line, &len, stdin)) > 0)
    {
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';
        if (strcmp(line, limiter) == 0)
            break ;
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
    }
    if (line)
        free(line);
    close(fd);
    return (0);
}

static char	**build_here_argv(char **argv, int *new_argc)
{
    char	**new_argv;
    int	count;
    int	i;

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

int		run_here_doc(char **argv, char **envp)
{
    char	**new_argv;
    int	new_argc;
    int	rc;

    write_here_doc(argv[2]);
    new_argv = build_here_argv(argv, &new_argc);
    rc = run_pipeline(new_argc, new_argv, envp);
    free(new_argv);
    unlink(".here_doc_tmp");
    return (rc);
}
