/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/18 13:36:08 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_pipex *pipex, char **argv, char **envp);
void	parent_process(t_pipex *pipex, char **argv, char **envp);
int		get_cmd_path(t_pipex *pipex, char *cmd);

void	process(t_pipex *pipex, char **argv, char **envp)
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
	close_pipe(pipex);
}

void	child_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR)
		error_exit(pipex, "dup2", "bad file descriptor", errno);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == ERROR)
		error_exit(pipex, "dup2", "bad file descriptor", errno);
	close_pipe(pipex);
	pipex->cmd_args = ft_split(argv[2], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
	if (get_cmd_path(pipex, pipex->cmd_args[0]) == ERROR)
		error_exit(pipex, argv[3], "command not found", 127);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit(127);
}

void	parent_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR)
		error_exit(pipex, "dup2", "bad file descriptor", errno);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
		error_exit(pipex, "dup2", "bad file descriptor", errno);
	close_pipe(pipex);
	pipex->cmd_args = ft_split(argv[3], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "malloc", "malloc failed", EXIT_FAILURE);
	if (get_cmd_path(pipex, pipex->cmd_args[0]) == ERROR)
		error_exit(pipex, argv[3], "command not found", 127);
	execve(pipex->cmd_path, pipex->cmd_args, envp);
	exit(127);
}

int	get_cmd_path(t_pipex *pipex, char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		if (!tmp)
			return (ERROR);
		pipex->cmd_path = ft_strjoin(tmp, cmd);
		if (!pipex->cmd_path)
			return (ERROR);
		free(tmp);
		if (access(pipex->cmd_path, X_OK & F_OK) == 0)
			return (0);
		free(pipex->cmd_path);
		i++;
	}
	return (ERROR);
}
