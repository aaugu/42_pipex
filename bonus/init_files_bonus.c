/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:52:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/30 19:23:18 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	get_infile(t_pipex *pipex, char *limiter);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile);

void	init_files(t_pipex *pipex, int ac, char **av)
{
	char	*limiter;

	if (pipex->heredoc == TRUE)
	{
		limiter = ft_strjoin(av[2], "\n");
		if (!limiter)
			error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
		get_infile(pipex, limiter);
		free(limiter);
	}
	else
		pipex->fd_in = open(av[1], O_RDONLY);
	if (pipex->fd_in < 0)
		error_message(av[1], "No such file or directory");
	open_outfile(pipex, av[ac - 1]);
}

void	get_infile(t_pipex *pipex, char *limiter)
{
	char	*line;

	pipex->fd_in = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (pipex->fd_in < 0)
		error_exit(pipex, ".heredoc.tmp", "No such file or directory", 1);
	while (TRUE)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(1, "\n", 1);
			error_exit(pipex, ".heredoc.tmp", "Couldn't collect input", 1);
		}
		if (ft_strcmp(line, limiter) == 0)
			break ;
		write(pipex->fd_in, line, ft_strlen(line));
		free(line);
	}
	close(pipex->fd_in);
	pipex->fd_in = open(".heredoc.tmp", O_RDONLY);
	if (pipex->fd_in < 0)
		error_message(".heredoc.tmp", "No such file or directory");
}

void	open_outfile(t_pipex *pipex, char *outfile)
{
	if (pipex->heredoc == TRUE)
	{
		pipex->fd_out = open(outfile, O_CREAT | O_RDWR | O_APPEND, 00644);
		if (pipex->fd_out < 0)
			error_exit(pipex, outfile, "No such file or directory", 1);
	}
	else
	{
		pipex->fd_out = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 00644);
		if (pipex->fd_out < 0)
			error_exit(pipex, outfile, "No such file or directory", 1);
	}
}
