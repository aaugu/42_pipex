/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 09:36:13 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	check_args(t_pipex *pipex, int ac, char **av);

int	main(int ac, char **av, char **envp)
{
	t_pipex		pipex;
	// int			exit_code;

	pipex = (t_pipex){0};
	pipex.nb_cmds = check_args(&pipex, ac, av);
	init_files(&pipex, ac, av);
	init(&pipex, av, envp);
	// if (pipe(pipex.pipe) == ERROR)
	// 	error_exit(&pipex, "pipe", "unable to create a pipe", EXIT_FAILURE);
	// exit_code = process(&pipex, av, envp);
	// end_pipex(&pipex, exit_code);
	// return (0);
}

int	check_args(t_pipex *pipex, int ac, char **av)
{
	if (ac < 5)
	{
		ft_printf("Error.\nNot enough arguments");
		exit(EXIT_FAILURE);
	}
	if (!ft_strcmp("here_doc", av[1]))
	{
		pipex->heredoc = 1;
		return (ac - 4);
	}
	else
	{
		pipex->heredoc = 0;
		return (ac - 3);
	}
}
