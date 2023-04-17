/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/17 16:33:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init(&pipex, argc, argv, envp);
	if (pipe(pipex.pipe) == ERROR)
		error_exit(&pipex, "pipe", EXIT_FAILURE);
	process(&pipex, argv, envp);
	close_fds(&pipex);
	end_pipex(&pipex, EXIT_SUCCESS);
	return (0);
}

void	close_fds(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	close(pipex->fd_in);
	close(pipex->fd_out);
}

int	error_exit(t_pipex *pipex, char *message, int code)
{
	if (message)
		perror(message);
	end_pipex(pipex, code);
	return (0);
}

void	end_pipex(t_pipex *pipex, int code)
{
	if (!(pipex->paths != NULL))
		ft_strs_free(pipex->paths, ft_strs_len(pipex->paths));
	if (!(pipex->cmd_path != NULL))
		free(pipex->cmd_path);
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
	exit(code);
}
