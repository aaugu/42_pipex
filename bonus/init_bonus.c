/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:21:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/27 13:53:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	get_paths(t_pipex *pipex, char **envp);
void	get_commands_and_paths(t_pipex *pipex, char **av);
void	commands_error_handling(t_pipex *pipex, char **av);
int		cmds_invalid(t_pipex *pipex);

void	init(t_pipex *pipex, char **av, char **envp)
{
	int	i;

	i = 0;
	get_paths(pipex, envp);
	get_commands_and_paths(pipex, av);
	ft_strs_free(pipex->paths, ft_strs_len(pipex->paths));
	pipex->paths = NULL;
	commands_error_handling(pipex, av);
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
		i++;
		j++;
	}
}

void	commands_error_handling(t_pipex *pipex, char **av)
{
	int	i;

	if (pipex->fd_in < 0 && cmds_invalid(pipex))
		i = 1;
	else if (pipex->fd_in && cmds_invalid(pipex))
		i = 0;
	if (cmds_invalid(pipex))
	{
		while (i < pipex->nb_cmds)
		{
			if (pipex->cmds_path[i] == NULL)
				error_message(av[2 + pipex->heredoc + i], "command not found");
			i++;
		}
		error_exit(pipex, NULL, NULL, 127);
	}
	else if (pipex->fd_in < 0)
		error_exit(pipex, NULL, NULL, EXIT_FAILURE);
}

int	cmds_invalid(t_pipex *pipex)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < pipex->nb_cmds)
	{
		if (!pipex->cmds_path[i])
			count++;
		i++;
	}
	return (count);
}
