/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:21:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/18 13:37:14 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path_line(char **envp);

void	init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	char	*path_line;

	if (argc != 5)
	{
		ft_printf("Error.\nWrong number of arguments");
		exit(EXIT_FAILURE);
	}
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
		error_message(argv[1], "No such file or directory");
	pipex->fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pipex->fd_out < 0)
		error_exit(pipex, argv[4], "No such file or directory", EXIT_FAILURE);
	path_line = get_path_line(envp);
	if (!path_line)
		error_exit(pipex, "PATH", "environment variable not found", errno);
	pipex->paths = ft_split(path_line, ':');
	if (!pipex->paths)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
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
