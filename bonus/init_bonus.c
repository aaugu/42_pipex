/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:21:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 09:31:59 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	get_paths(t_pipex *pipex, char **envp);
void	get_commands_and_paths(t_pipex *pipex, char **av);

void	init(t_pipex *pipex, char **av, char **envp)
{
	get_paths(pipex, envp);
	get_commands_and_paths(pipex, av);
	ft_strs_free(pipex->paths, ft_strs_len(pipex->paths));
	if (!pipex->infile && (!pipex->cmds_path[0] || !pipex->cmds_path[1]))
		error_exit(pipex, av[3], "command not found", 127);
	else if (pipex->infile && !pipex->cmds_path[0] && !pipex->cmds_path[1])
	{
		error_message(av[2], "command not found");
		error_exit(pipex, av[3], "command not found", 127);
	}
}

void	get_commands_and_paths(t_pipex *pipex, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	pipex->cmds = (char **)malloc(sizeof(char *) * (pipex->nb_cmds + 1));
	pipex->cmds_path = (char **)malloc(sizeof(char *) * (pipex->nb_cmds + 1));
	if (!pipex->cmds || !pipex->cmds_path)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
	if (pipex->heredoc == TRUE)
		j++;
	while (i < pipex->nb_cmds)
	{
		pipex->cmds[i] = get_cmd(av[j]);
		if (!pipex->cmds[i])
			error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
		pipex->cmds_path[i] = get_cmd_path(pipex->paths, av[j], pipex->cmds[i]);
		if (!pipex->cmds_path[i])
			error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
		i++;
		j++;
	}
}

void	get_paths(t_pipex *pipex, char **envp)
{
	char	*path_line;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			path_line = *envp + 5;
		envp++;
	}
	if (!path_line)
		error_exit(pipex, "PATH", "environment variable not found", 1);
	pipex->paths = ft_split(path_line, ':');
	if (!pipex->paths)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
}
