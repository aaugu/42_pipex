/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:25:50 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/20 17:56:32 by aaugu            ###   ########.fr       */
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
