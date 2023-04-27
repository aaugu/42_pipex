/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:43:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/27 14:22:54 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	child_process(t_pipex *pipex, char *cmd, char **envp, int i);
void	get_in_and_out(t_pipex *pipex, int i);
int		wait_for_childs(t_pipex *pipex);

int	process(t_pipex *p, char **av, char **envp)
{
	int	exit_code;
	int	i;

	i = 0;
	p->process.pids = (int *)malloc(sizeof(int) * p->nb_cmds);
	if (!p->process.pids)
		error_exit(p, "malloc", "malloc failed", EXIT_FAILURE);
	while (i < p->nb_cmds)
	{
		p->process.pids[i] = fork();
		if (p->process.pids[i] < 0)
			error_exit(p, "fork failed", "Resource temporarily unavailable", 4);
		else if (p->process.pids[i] == 0)
			child_process(p, av[2 + p->heredoc + i], envp, i);
		i++;
	}
	exit_code = wait_for_childs(p);
	return (exit_code);
}

void	child_process(t_pipex *p, char *cmd, char **envp, int i)
{
	get_in_and_out(p, i);
	if (dup2(p->process.in, STDIN_FILENO) == ERROR || \
		dup2(p->process.out, STDOUT_FILENO) == ERROR)
	{
		error_message("dup2", "Bad file descriptor");
		exit(errno);
	}
	close_pipes(p);
	p->process.cmd_args = get_args(cmd);
	if (!p->process.cmd_args)
	{
		error_message("malloc", "malloc failed");
		exit(EXIT_FAILURE);
	}
	execve(p->cmds_path[i], p->process.cmd_args, envp);
	error_message(cmd, "command not found");
	ft_strs_free(p->process.cmd_args, ft_strs_len(p->process.cmd_args));
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

int	wait_for_childs(t_pipex *p)
{
	int	i;
	int	wpid;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 127;
	while (i < p->nb_cmds)
	{
		wpid = waitpid(p->process.pids[i], &status, 0);
		if (wpid == p->process.pids[p->nb_cmds])
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_code);
}
