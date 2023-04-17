/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:21:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/17 16:35:40 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		open_infile(t_pipex *pipex, char *infile);
int		open_outfile(t_pipex *pipex, char *outfile);
char	**parse_paths(t_pipex *pipex, char **envp);
char	*get_path_line(char **envp);

void	init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_printf("Error.\nWrong number of arguments");
		exit(EXIT_FAILURE);
	}
	if (open_infile(pipex, argv[1]) == ERROR)
		perror(argv[1]);
	if (open_outfile(pipex, argv[4]) == ERROR)
		error_exit(pipex, argv[4], errno);
	pipex->paths = parse_paths(pipex, envp);
	if (!pipex->paths)
		error_exit(pipex, "PATH", EXIT_FAILURE);
}

int	open_infile(t_pipex *pipex, char *infile)
{
	pipex->fd_in = open(infile, O_RDONLY);
	if (pipex->fd_in < 0)
	{
		return (-1);
	}
	return (0);
}

int	open_outfile(t_pipex *pipex, char *outfile)
{
	pipex->fd_out = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pipex->fd_out < 0)
		return (-1);
	return (0);
}

char	**parse_paths(t_pipex *pipex, char **envp)
{
	char	**paths;
	char	*path_line;

	path_line = get_path_line(envp);
	if (!path_line)
		error_exit(pipex, "PATH", EXIT_FAILURE);
	paths = ft_split(path_line, ':');
	if (!paths)
		error_exit(pipex, "malloc", EXIT_FAILURE);
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
