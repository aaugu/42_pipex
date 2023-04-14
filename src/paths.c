/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:00:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/14 13:34:59 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path_line(char **envp);

char	**parse_paths(char **envp)
{
	char	**paths;
	char	*path_line;

	path_line = get_path_line(envp);
	if (!path_line)
		return (NULL);
	paths = ft_split(path_line, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_path_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (NULL);
		free(tmp);
		if (access(cmd_path, R_OK & W_OK & X_OK & F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}
