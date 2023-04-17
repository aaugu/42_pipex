/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/17 16:41:04 by aaugu            ###   ########.fr       */
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
		error_exit(pipex, "Fork", 4);
	else if (pid == 0)
		child_process(pipex, argv, envp);
	else
		parent_process(pipex, argv, envp);
	waitpid(pid, &status, 0);
}

void	child_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR)
		error_exit(pipex, NULL, EXIT_FAILURE);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == ERROR)
		error_exit(pipex, "Dup1stdin", EXIT_FAILURE);
	close_fds(pipex);
	pipex->cmd_args = ft_split(argv[2], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Command args", EXIT_FAILURE);
	if (get_cmd_path(pipex, pipex->cmd_args[0]) == ERROR)
		error_exit(pipex, "malloc", 127);
	if (execve(pipex->cmd_path, pipex->cmd_args, envp) == ERROR)
	{
		ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
		error_exit(pipex, "Command was found but could not be executed", 126);
	}
	ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
}

void	parent_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR)
		error_exit(pipex, "Dup2stdin", EXIT_FAILURE);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
		error_exit(pipex, "Dup2stdout", EXIT_FAILURE);
	close_fds(pipex);
	pipex->cmd_args = ft_split(argv[3], ' ');
	if (!pipex->cmd_args)
		error_exit(pipex, "Command args", EXIT_FAILURE);
	if (get_cmd_path(pipex, pipex->cmd_args[0]) == ERROR)
		error_exit(pipex, "malloc", 127);
	if (execve(pipex->cmd_path, pipex->cmd_args, envp) == ERROR)
	{
		ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
		error_exit(pipex, "Command was found but could not be executed", 126);
	}
	ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
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
			return (-1);
		pipex->cmd_path = ft_strjoin(tmp, cmd);
		if (!pipex->cmd_path)
			return (-1);
		free(tmp);
		if (access(pipex->cmd_path, R_OK & W_OK & X_OK & F_OK) == 0)
			return (0);
		free(pipex->cmd_path);
		i++;
	}
	return (error_exit(pipex, "Command not found", 127));
}
