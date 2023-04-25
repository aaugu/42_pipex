/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:50:07 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 11:05:49 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(char *path, char *cmd);

char	*get_cmd(char *full_cmd)
{
	char	**cmd_args;
	char	*cmd;

	cmd_args = ft_split(full_cmd, ' ');
	if (!cmd_args)
		return (NULL);
	cmd = cmd_args[0];
	free(cmd_args);
	return (cmd);
}

char	*get_cmd_path(char **paths, char *cmd_args, char *cmd)
{
	char	**args;
	char	*path;

	while (*paths)
	{
		if (access(cmd, X_OK & F_OK) == 0)
			return (cmd);
		else
		{
			path = get_path(*paths, cmd);
			args = ft_split(cmd_args, ' ');
			if (!path || !args)
				return (NULL);
			if (access(path, X_OK & F_OK) == 0)
			{
				free(args);
				return (path);
			}
			ft_strs_free(args, ft_strs_len(args));
			free(path);
			paths++;
		}
	}
	return (NULL);
}

char	*get_path(char *path, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = NULL;
	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

int	get_pos(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	**split_quotes(char *args, char quote)
{
	char	**cmd_args;
	int		i;
	int		save;

	cmd_args = (char **)malloc(sizeof(char *) * 3);
	if (!cmd_args)
		return (NULL);
	cmd_args[2] = NULL;
	i = 0;
	while (args[i] != ' ')
		i++;
	save = i;
	cmd_args[0] = ft_substr(args, 0, save);
	if (!cmd_args[0])
		ft_strs_free(cmd_args, 2);
	i += 2;
	save = i;
	while (args[i] != quote)
		i++;
	cmd_args[1] = ft_substr(args, save, i - save);
	if (!cmd_args[1])
		ft_strs_free(cmd_args, 2);
	return (cmd_args);
}
