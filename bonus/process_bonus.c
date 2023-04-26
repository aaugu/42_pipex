/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/26 14:53:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	child_process(t_pipex *pipex, char *cmd, char **envp, int i);
void	get_in_and_out(t_pipex *pipex, int i);

int	process(t_pipex *pipex, char **argv, char **envp)
{
	int	exit_code;
	int	i;

	i = 0;
	while (i < pipex->nb_cmds)
	{
		pipex->process.pids[i] = fork();
		if (pipex->process.pids[i] < 0)
			error_exit(pipex, "fork failed", "Resource temporarily unavailable"\
			, 4);
		else if (pipex->process.pids[i] == 0)
			child_process(pipex, argv[2 + pipex->heredoc + i], envp, i);
		i++;
	}
	exit_code = wait_for_childs(pipex);
	close_pipes(pipex);
	return (exit_code);
}

void	child_process(t_pipex *pipex, char *cmd, char **envp, int i)
{
	get_in_and_out(pipex, i);
	if (dup2(pipex->process.in, STDIN_FILENO) == ERROR || \
		dup2(pipex->process.out, STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "bad file descriptor");
		exit(errno);
	}
	close_pipes(pipex);
	pipex->process.cmd_args = get_args(cmd);
	if (!pipex->process.cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(pipex->cmds_path[i], pipex->process.cmd_args, envp);
	error_message(cmd, "command not found");
	ft_strs_free(pipex->process.cmd_args, ft_strs_len(pipex->process.cmd_args));
	exit(127);
}

void	get_in_and_out(t_pipex *pipex, int i)
{
	pipex->process.in = pipex->process.pipes[2 * i - 2];
	pipex->process.out = pipex->process.pipes[2 * i + 1];
	if (i == 0)
		pipex->process.in = pipex->fd_in;
	else if (i == pipex->nb_cmds - 1)
		pipex->process.out = pipex->fd_out;
}
