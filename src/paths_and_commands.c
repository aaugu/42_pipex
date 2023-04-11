/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_and_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:00:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/06 22:41:08 by aaugu            ###   ########.fr       */
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
