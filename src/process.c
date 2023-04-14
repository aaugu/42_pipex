/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/14 14:50:13 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_pipex *pipex, char **argv, char **envp);
void	parent_process(t_pipex *pipex, char **argv, char **envp);

void	process(t_pipex *pipex, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit(pipex, "Fork one", 4);
	else if (pid == 0)
		child_process(pipex, argv, envp);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(pipex, argv, envp);
	}
}

void	child_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR)
		error_exit(pipex, "Duplication stdin 1", EXIT_FAILURE);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == ERROR)
		error_exit(pipex, "Duplication stdout 1", EXIT_FAILURE);
	close(pipex->pipe[0]);
	close(pipex->fd_in);
	pipex->cmd_args = ft_split(argv[2], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Command args", EXIT_FAILURE);
	pipex->cmd_path = get_cmd_path(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd_path)
		error_exit(pipex, "Command not found", 127);
	if (execve(pipex->cmd_path, pipex->cmd_args, envp) == ERROR)
	{
		ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
		error_exit(pipex, "Could not execute command", 127);
	}
}

void	parent_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR)
		error_exit(pipex, "Duplication stdin 2", EXIT_FAILURE);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
		error_exit(pipex, "Duplication stdout 2", EXIT_FAILURE);
	close(pipex->pipe[1]);
	close(pipex->fd_out);
	pipex->cmd_args = ft_split(argv[3], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Command args", EXIT_FAILURE);
	pipex->cmd_path = get_cmd_path(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd_path)
		error_exit(pipex, "Command not found", 127);
	if (execve(pipex->cmd_path, pipex->cmd_args, envp) == ERROR)
	{
		ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
		error_exit(pipex, "Could not execute command", 127);
	}
}
