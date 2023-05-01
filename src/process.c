/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/01 11:16:40 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child_process(t_pipex *pipex, char **argv, char **envp);
void	second_child_process(t_pipex *pipex, char **argv, char **envp);
char	**get_args(char *args);
void	close_pipe(t_pipex *pipex);

int	process(t_pipex *pipex, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = fork();
	if (pid1 < 0)
		error_exit(pipex, "fork failed", "Resource temporarily unavailable", 4);
	else if (pid1 == 0)
		first_child_process(pipex, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		error_exit(pipex, "fork failed", "Resource temporarily unavailable", 4);
	else if (pid2 == 0)
		second_child_process(pipex, argv, envp);
	close_pipe(pipex);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	first_child_process(t_pipex *pipex, char **argv, char **envp)
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
	cmd_args = get_args(argv[2]);
	if (!cmd_args)
	{
		ft_strs_free(cmd_args, ft_strs_len(cmd_args));
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[0], cmd_args, envp);
	ft_strs_free(cmd_args, ft_strs_len(cmd_args));
	exit(127);
}

void	second_child_process(t_pipex *pipex, char **argv, char **envp)
{
	char	**cmd_args;

	if (dup2(pipex->pipe[0], STDIN_FILENO) == ERROR || \
		dup2(pipex->fd_out, STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "Bad file descriptor");
		exit(errno);
	}
	close_pipe(pipex);
	cmd_args = get_args(argv[3]);
	if (!cmd_args)
	{
		ft_strs_free(cmd_args, ft_strs_len(cmd_args));
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

	cmd_args = NULL;
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
		size = ft_strlen(cmd_args[0]);
		cmd_args[0][size - 1] = '\0';
	}
	else
		cmd_args = ft_split(args, ' ');
	return (cmd_args);
}
