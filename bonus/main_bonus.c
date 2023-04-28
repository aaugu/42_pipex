/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/28 14:54:54 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	check_args(t_pipex *pipex, int ac, char **av);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	pipex = (t_pipex){0};
	check_args(&pipex, argc, argv);
	init_files(&pipex, argc, argv);
	init(&pipex, argv, envp);
	if (pipe(pipex.pipe) == ERROR)
		error_exit(&pipex, "pipe", "unable to create a pipe", EXIT_FAILURE);
	exit_code = process(&pipex, argv, envp);
	end_pipex(&pipex, exit_code);
	return (0);
}

void	check_args(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_printf("Error\nNot enough arguments");
		exit(EXIT_FAILURE);
	}
	if (!ft_strcmp("here_doc", argv[1]) && argc == 6)
		pipex->heredoc = 1;
	else if (ft_strcmp("here_doc", argv[1]) && argc == 5)
		pipex->heredoc = 0;
	else
	{
		ft_printf("Error\nWrong number of arguments");
		exit(EXIT_FAILURE);
	}
}
