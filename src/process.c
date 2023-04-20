/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/21 01:27:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_pipex *pipex, char **argv, char **envp);
void	parent_process(t_pipex *pipex, char **argv, char **envp);
char	**get_args(char *args);
void	close_pipe(t_pipex *pipex);

int	process(t_pipex *pipex, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit(pipex, "fork failed", "Resource temporarily unavailable", 4);
	else if (pid == 0)
		child_process(pipex, argv, envp);
	else
		parent_process(pipex, argv, envp);
	waitpid(pid, &status, 0);
	if (waitpid(pid, &status, 0) == -1)
	{
		if (WIFEXITED(status) != 0)
		{
			error_message(argv[0], "command not found");
			return (WEXITSTATUS(status));
		}
	}
	close_pipe(pipex);
	return (0);
}

void	child_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR || \
		dup2(pipex->pipe[1], STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex);
	pipex->cmd_args = get_args(argv[2]);
	if (!pipex->cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[0], pipex->cmd_args, envp);
	error_message(argv[2], "command not found");
	exit(127);
}

void	parent_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR || \
		dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex);
	pipex->cmd_args = get_args(argv[3]);
	if (!pipex->cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[1], pipex->cmd_args, envp);
	error_message(argv[3], "command not found");
	exit(127);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

char	**get_args(char *args)
{
	char	**cmd_args;
	int		size;

	if (ft_strrchr(args, '\''))
	{
		cmd_args = ft_split(args, '\'');
		if (!cmd_args)
			return (NULL);
		free(cmd_args[0]);
		size = 0;
		while (*args != ' ')
		{
			size++;
			args++;
		}
		cmd_args[0] = (char *)malloc(sizeof(char) * (size + 1));
		if (!cmd_args[0])
			return (NULL);
		cmd_args[size] = NULL;
		size = 0;
		while (cmd_args[0][size])
		{
			cmd_args[0][size] = args[size];
			size++;
		}
	}
	else
		cmd_args = ft_split(args, ' ');
	return (cmd_args);
}
