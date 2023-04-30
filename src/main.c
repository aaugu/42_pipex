/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/30 19:26:09 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(t_pipex *pipex, char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	pipex = (t_pipex){0};
	if (argc != 5)
	{
		ft_printf("Error.\nWrong number of arguments");
		exit(EXIT_FAILURE);
	}
	open_files(&pipex, argv);
	init(&pipex, argv, envp);
	if (pipe(pipex.pipe) == ERROR)
		error_exit(&pipex, "pipe", "unable to create a pipe", EXIT_FAILURE);
	exit_code = process(&pipex, argv, envp);
	end_pipex(&pipex, exit_code);
	return (0);
}

void	open_files(t_pipex *pipex, char **argv)
{
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
		error_message(argv[1], "No such file or directory");
	pipex->fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pipex->fd_out < 0)
		error_exit(pipex, argv[4], "No such file or directory", EXIT_FAILURE);
}
