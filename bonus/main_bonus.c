/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 14:23:51 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int		check_args(t_pipex *pipex, int ac, char **av);
void	create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);

int	main(int ac, char **av, char **envp)
{
	t_pipex		pipex;
	// int			exit_code;

	pipex = (t_pipex){0};
	pipex.nb_cmds = check_args(&pipex, ac, av);
	init_files(&pipex, ac, av);
	init(&pipex, av, envp);
	create_pipes(&pipex);
	// exit_code = process(&pipex, av, envp);
	// close_pipes(&pipex);
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

void	create_pipes(t_pipex *pipex)
{
	int	nb_pipes;
	int	i;

	nb_pipes = pipex->nb_cmds - 1;
	pipex->pipes = (int *)malloc(sizeof(int) * (2 * nb_pipes));
	if (!pipex->pipes)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
	while (*pipex->pipes)
	{
		if (pipe(*pipex->pipes) == ERROR)
			error_exit(&pipex, "pipe", "unable to create a pipe", EXIT_FAILURE);
		pipex->pipes + 2;
	}
}

void	close_pipes(t_pipex *pipex)
{
	while (*pipex->pipes)
	{
		close(pipex->pipes);
		pipex->pipes++;
	}
	free(pipex->pipes);
}
