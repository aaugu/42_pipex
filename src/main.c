/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/14 14:12:24 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		open_files(t_pipex *pipex, char *file1, char *file2);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("Error.\nWrong number of arguments");
		exit(1);
	}
	if (open_files(&pipex, argv[1], argv[4]) == ERROR)
		error_exit(&pipex, "Problem while opening files", EXIT_FAILURE);
	pipex.paths = parse_paths(envp);
	if (!pipex.paths)
		error_exit(&pipex, "Problem while parsing PATH", EXIT_FAILURE);
	if (pipe(pipex.pipe) == ERROR)
		error_exit(&pipex, "Problem while creating pipe.", EXIT_FAILURE);
	process(&pipex, argv, envp);
	end_pipex(&pipex, EXIT_SUCCESS);
	return (0);
}

int	open_files(t_pipex *pipex, char *file1, char *file2)
{
	pipex->fd_in = open(file1, O_RDONLY);
	if (pipex->fd_in < 0)
		return (-1);
	pipex->fd_out = open(file2, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pipex->fd_in < 0)
		return (-1);
	return (0);
}

void	error_exit(t_pipex *pipex, char *message, int code)
{
	perror(message);
	end_pipex(pipex, code);
}

void	end_pipex(t_pipex *pipex, int code)
{
	if (pipex->paths)
		ft_strs_free(pipex->paths, ft_strs_len(pipex->paths));
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
	exit(code);
}
