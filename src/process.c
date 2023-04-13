/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/12 16:41:23 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child_process(t_pipex *pipex, char **argv, char **envp);
void	last_child_process(t_pipex *pipex, char **argv, char **envp);

void	process(t_pipex *pipex, char **argv, char **envp)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		error_exit(pipex, "Fork one", 1);
	if (pipex->pid[0] == 0)
		first_child_process(pipex, argv, envp);
	pipex->pid[1] = fork();
	if (pipex->pid[1] < 0)
		error_exit(pipex, "Fork two", 1);
	if (pipex->pid[1] == 0)
		last_child_process(pipex, argv, envp);
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
}

void	first_child_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR)
		error_exit(pipex, "Duplication in 1", 1);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == ERROR)
		error_exit(pipex, "Duplication out 1", 1);
	close(pipex->pipe[0]);
	close(pipex->fd_in);
	pipex->cmd_args = ft_split(argv[2], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Command args", 1);
	pipex->cmd_path = get_cmd_path(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd_path)
		error_exit(pipex, "Command not found", 1);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
}

void	last_child_process(t_pipex *pipex, char **argv, char **envp)
{
	waitpid(pipex->pid[0], NULL, 0);
	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR)
		error_exit(pipex, "Duplication in 2", 1);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
		error_exit(pipex, "Duplication out 2", 1);
	close(pipex->pipe[1]);
	close(pipex->fd_out);
	pipex->cmd_args = ft_split(argv[3], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Command args", 1);
	pipex->cmd_path = get_cmd_path(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd_path)
		error_exit(pipex, "Command not found", 1);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
}
