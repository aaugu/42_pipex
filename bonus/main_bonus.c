/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/27 11:02:59 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int		check_args(t_pipex *pipex, int ac, char **av);
void	create_pipes(t_pipex *pipex);

int	main(int ac, char **av, char **envp)
{
	t_pipex		pipex;
	int			exit_code;

	pipex = (t_pipex){0};
	pipex.nb_cmds = check_args(&pipex, ac, av);
	init_files(&pipex, ac, av);
	init(&pipex, av, envp);
	if (pipex.fd_in < 0)
		error_exit(&pipex, NULL, NULL, EXIT_FAILURE);
	create_pipes(&pipex);
	exit_code = process(&pipex, av, envp);
	close_pipes(&pipex);
	end_pipex(&pipex, exit_code);
	return (0);
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

	i = 0;
	nb_pipes = pipex->nb_cmds - 1;
	pipex->process.pipes = (int *)malloc(sizeof(int) * (2 * nb_pipes));
	if (!pipex->process.pipes)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
	while (pipex->process.pipes[i])
	{
		if (pipe(&pipex->process.pipes[i]) == ERROR)
			error_exit(pipex, "pipe", "unable to create a pipe", EXIT_FAILURE);
		i += 2;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->nb_cmds - 1) * 2)
	{
		ft_putstr_fd("ici\n", 2);
		close(pipex->process.pipes[i]);
		i++;
	}
	free(pipex->process.pipes);
}
