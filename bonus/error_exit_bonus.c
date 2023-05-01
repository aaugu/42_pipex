/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:06:54 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/01 15:35:56 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	error_message(char *arg, char *message)
{
	write(2, "pipex: ", 7);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	error_exit(t_pipex *pipex, char *arg, char *message, int code)
{
	error_message(arg, message);
	end_pipex(pipex, code);
}

void	end_pipex(t_pipex *pipex, int code)
{
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
	if (pipex->cmds_path[0])
		free(pipex->cmds_path[0]);
	if (pipex->cmds_path[1])
		free(pipex->cmds_path[1]);
	if (pipex->heredoc)
		unlink(".heredoc.tmp");
	exit(code);
}
