/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/06 22:57:23 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (0);
	pipex.paths = parse_paths(envp);
	if (!pipex.paths)
		return (0);
	pipex.cmds = parse_commands(argv, argc);
	if (!pipex.cmds)
		return (0);
	return (0);
}

void	error_exit(t_pipex *pipex, char *message)
{
	ft_printf("%s\n", message);
	end_pipex(pipex);
}

void	end_pipex(t_pipex *pipex)
{
	if (pipex->paths)
		ft_strs_free(pipex->paths, ft_strs_len(pipex->paths));
	if (pipex->cmds)
		ft_strs_free(pipex->cmds, 2);
}
