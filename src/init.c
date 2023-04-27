/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:21:55 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/27 13:32:11 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(t_pipex *pipex, char **argv);
void	get_commands(t_pipex *pipex, char **argv);
void	get_paths(t_pipex *pipex, char **envp);
void	get_commands_path(t_pipex *pipex, char **argv);

// Check args, open fds, get command paths for execve
void	init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_printf("Error.\nWrong number of arguments");
		exit(EXIT_FAILURE);
	}
	open_files(pipex, argv);
	get_commands(pipex, argv);
	get_paths(pipex, envp);
	if (!pipex->paths)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
	get_commands_path(pipex, argv);
	if (!pipex->infile && (!pipex->cmds_path[0] || !pipex->cmds_path[1]))
		error_exit(pipex, argv[3], "command not found", 127);
	else if (pipex->infile && !pipex->cmds_path[0] && !pipex->cmds_path[1])
	{
		error_message(argv[2], "command not found");
		error_exit(pipex, argv[3], "command not found", 127);
	}
}

void	open_files(t_pipex *pipex, char **argv)
{
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
	{
		error_message(argv[1], "No such file or directory");
		pipex->infile = FALSE;
	}
	else
		pipex->infile = TRUE;
	pipex->fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (pipex->fd_out < 0)
	{
		error_exit(pipex, argv[4], "No such file or directory", EXIT_FAILURE);
	}
}

void	get_commands(t_pipex *pipex, char **argv)
{
	pipex->cmds[0] = get_cmd(argv[2]);
	pipex->cmds[1] = get_cmd(argv[3]);
	if (!pipex->cmds[0] || !pipex->cmds[1])
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
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
}

void	get_commands_path(t_pipex *pipex, char **argv)
{
	pipex->cmds_path[0] = get_cmd_path(pipex->paths, argv[2], pipex->cmds[0]);
	pipex->cmds_path[1] = get_cmd_path(pipex->paths, argv[3], pipex->cmds[1]);
}
