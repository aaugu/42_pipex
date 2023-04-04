/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:53:14 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/04 14:25:41 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_command_path(char *path, char *cmd);
t_bool	is_command_valid(char **cmd, char **paths);

char	***parse_commands(char **argv, int argc)
{
	char	***cmds;
	int		nb_cmds;
	int		i;
	int		j;

	nb_cmds = argc - 3;
	cmds = (char ***)malloc(sizeof(char **) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		cmds[j++] = ft_split(argv[i++], ' ');
		if (!cmds)
		{
			free_all_strs(cmds);
			return (NULL);
		}
	}
	cmds[nb_cmds] = NULL;
	return (cmds);
}

t_bool	are_commands_valid(char ***cmds, int nb_cmds, char **paths)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 0;
	nb = 0;
	while (i < nb_cmds)
	{
		if (is_command_valid(cmds[i], paths) == TRUE)
			nb++;
		j = 0;
		i++;
	}
	if (nb == nb_cmds)
		return (1);
	return (0);
}

t_bool	is_command_valid(char **cmd, char **paths)
{
	char	*path;
	int		i;

	i = 0;
	while (i < ft_strs_len(paths))
	{
		path = get_command_path(paths[i], cmd[0]);
		if (!path)
			return (0);
		if (access(path, X_OK) == 0)
		{
			free(path);
			return (1);
		}
		free(path);
	}
	return (0);
}

char	*get_command_path(char *path, char *cmd)
{
	char	*path_to_cmd;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(path) + 1 + ft_strlen(cmd);
	path_to_cmd = (char *)malloc(sizeof(char) * (size + 1));
	if (!path_to_cmd)
		return (NULL);
	path_to_cmd[size] = '\0';
	i = 0;
	j = 0;
	while (j < ft_strlen(path))
		path_to_cmd[i++] = path[j++];
	j = 0;
	path_to_cmd[i++] = '/';
	while (j < ft_strlen(cmd))
		path_to_cmd[i++] = cmd[j++];
	return (path_to_cmd);
}
