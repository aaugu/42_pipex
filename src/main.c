/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 10:35:45 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_code;

	pipex = (t_pipex){0};
	init(&pipex, argc, argv, envp);
	if (pipe(pipex.pipe) == ERROR)
		error_exit(&pipex, "pipe", "unable to create a pipe", EXIT_FAILURE);
	exit_code = process(&pipex, argv, envp);
	end_pipex(&pipex, exit_code);
	return (0);
}
