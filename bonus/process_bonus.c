/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 14:48:09 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	child_process(t_pipex *pipex, char **argv, char **envp);
void	parent_process(t_pipex *pipex, char **argv, char **envp);
char	**get_args(char *args);
void	close_pipe(int in, int out);

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
	if (WIFEXITED(status) != 0)
	{
		error_message(argv[0], "command not found");
		return (WEXITSTATUS(status));
	}
	close_pipes(pipex->pipes);
	return (0);
}

void	child_process(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->fd_in < 0)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR || \
		dup2(pipex->pipes[1], STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex->pipes[0], pipex->pipes[1]);
	pipex->cmd_args = get_args(argv[2]);
	if (!pipex->cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[0], pipex->cmd_args, envp);
	error_message(argv[2], "command not found");
	ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
	exit(127);
}

void	parent_process(t_pipex *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipes[0], STDIN_FILENO) == ERROR || \
		dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex->pipes[0], pipex->pipes[1]);
	pipex->cmd_args = get_args(argv[3]);
	if (!pipex->cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[1], pipex->cmd_args, envp);
	error_message(argv[3], "command not found");
	ft_strs_free(pipex->cmd_args, ft_strs_len(pipex->cmd_args));
	exit(127);
}

void	close_pipe(int in, int out)
{
	close(in);
	close(out);
}

char	**get_args(char *args)
{
	char	**cmd_args;
	int		size;

	if (ft_strrchr(args, '\"') && ft_strrchr(args, '\''))
	{	
		if (get_pos(args, '\"') < get_pos(args, '\''))
			cmd_args = split_quotes(args, '\"');
		else
			cmd_args = split_quotes(args, '\'');
	}
	else if (ft_strrchr(args, '\"') || ft_strrchr(args, '\''))
	{
		if (ft_strrchr(args, '\"'))
			cmd_args = ft_split(args, '\"');
		else
			cmd_args = ft_split(args, '\'');
		if (!cmd_args)
			return (NULL);
		size = ft_strlen(cmd_args[0]);
		cmd_args[0][size - 1] = '\0';
	}
	else
		cmd_args = ft_split(args, ' ');
	return (cmd_args);
}
