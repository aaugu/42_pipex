/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/30 20:52:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
	parent_process(pipex, argv, envp);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	close_pipe(pipex);
	return (1);
}

void	child_process(t_pipex *pipex, char **argv, char **envp)
{
	char	**cmd_args;

	if (pipex->fd_in < 0)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd_in, STDIN_FILENO) == ERROR || \
		dup2(pipex->pipe[1], STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "Bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex);
	cmd_args = get_args(argv[2 + pipex->heredoc]);
	if (!cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[0], cmd_args, envp);
	ft_strs_free(cmd_args, ft_strs_len(cmd_args));
	exit(127);
}

void	parent_process(t_pipex *pipex, char **argv, char **envp)
{
	char	**cmd_args;

	if (pipex->heredoc)
		unlink(".heredoc.tmp");
	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR || \
		dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "Bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex);
	cmd_args = get_args(argv[3 + pipex->heredoc]);
	if (!cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[1], cmd_args, envp);
	ft_strs_free(cmd_args, ft_strs_len(cmd_args));
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
