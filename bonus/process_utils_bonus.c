/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:26:50 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/26 14:57:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	**split_quotes(char *args, char quote);
int		get_pos(char *s, char c);

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

char	**split_quotes(char *args, char quote)
{
	char	**cmd_args;
	int		i;
	int		save;

	cmd_args = (char **)malloc(sizeof(char *) * 3);
	if (!cmd_args)
		return (NULL);
	cmd_args[2] = NULL;
	i = 0;
	while (args[i] != ' ')
		i++;
	save = i;
	cmd_args[0] = ft_substr(args, 0, save);
	if (!cmd_args[0])
		ft_strs_free(cmd_args, 2);
	i += 2;
	save = i;
	while (args[i] != quote)
		i++;
	cmd_args[1] = ft_substr(args, save, i - save);
	if (!cmd_args[1])
		ft_strs_free(cmd_args, 2);
	return (cmd_args);
}

int	get_pos(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	wait_for_childs(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->nb_cmds)
	{
		waitpid(pipex->process.pids[i], &status, 0);
		if (WIFEXITED(status) != 0)
			return (WEXITSTATUS(status));
		i++;
	}
	return (0);
}

// void	close_process_pipes(t_pipex *pipex, int i)
// {
// 	if (pipex->process.in == pipex->fd_in)
// 	{
// 		close(pipex->process.pipes[2 * i - 2]);
// 		close(pipex->process.out);
// 	}
// 	else if (pipex->process.out == pipex->fd_out)
// 	{
// 		close(pipex->process.in);
// 		close(pipex->process.pipes[2 * i + 1]);
// 	}
// 	else
// 	{
// 		close(pipex->process.in);
// 		close(pipex->process.pipes[2 * i - 2 + 1]);
// 		close(pipex->process.out);
// 		close(pipex->process.pipes[2 * i + 1 - 1]);
// 	}
// }
