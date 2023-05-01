/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:21:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/01 15:10:44 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	get_commands(t_pipex *pipex, char **argv);
char	**get_paths(char **envp);
void	get_commands_path(t_pipex *p, char **paths);
void	commands_error_handling(t_pipex *p, char **av);

void	init(t_pipex *pipex, char **argv, char **envp)
{
	char	**paths;

	get_commands(pipex, argv);
	paths = get_paths(envp);
	if (!paths)
		error_exit(pipex, "PATH", "environment variable not found", 1);
	get_commands_path(pipex, paths);
	ft_strs_free(paths, ft_strs_len(paths));
	commands_error_handling(pipex, argv);
}

char	**get_paths(char **envp)
{
	char	*path_line;
	char	**paths;

	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			path_line = *envp + 5;
		envp++;
	}
	if (!path_line)
		return (NULL);
	paths = ft_split(path_line, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

void	get_commands(t_pipex *pipex, char **argv)
{
	pipex->cmds[0] = get_cmd(argv[2]);
	pipex->cmds[1] = get_cmd(argv[3]);
	if (!pipex->cmds[0] || !pipex->cmds[1])
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
}

void	get_commands_path(t_pipex *p, char **paths)
{
	p->cmds_path[0] = get_cmd_path(paths, p->cmds[0]);
	p->cmds_path[1] = get_cmd_path(paths, p->cmds[1]);
}

void	commands_error_handling(t_pipex *p, char **av)
{
	int	i;

	if (p->fd_in < 0 && (!p->cmds_path[0] || !p->cmds_path[1]))
		i = 1;
	else if (p->fd_in && (!p->cmds_path[0] || !p->cmds_path[1]))
		i = 0;
	if (!p->cmds_path[0] || !p->cmds_path[1])
	{
		while (i < 2)
		{
			if (p->cmds_path[i] == NULL)
				error_message(av[2 + i], "command not found");
			i++;
		}
	}
}
