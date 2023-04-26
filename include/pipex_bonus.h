/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:37:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/26 14:57:15 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_process
{
	char	**cmd_args;
	int		*pipes;
	int		*pids;
	int		in;
	int		out;
}			t_process;

typedef struct s_pipex
{
	char		**paths;
	char		**cmds;
	char		**cmds_path;
	int			nb_cmds;
	int			fd_in;
	int			fd_out;
	t_bool		infile;
	t_bool		heredoc;
	t_process	process;
}				t_pipex;

void	init_files(t_pipex *pipex, int ac, char **av);
void	init(t_pipex *pipex, char **av, char **envp);
char	*get_cmd(char *full_cmd);
char	*get_cmd_path(char **paths, char *cmd_args, char *cmd);
char	**get_args(char *args);
int		process(t_pipex *pipex, char **argv, char **envp);
int		wait_for_childs(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	error_exit(t_pipex *pipex, char *arg, char *message, int code);
void	error_message(char *arg, char *message);
void	end_pipex(t_pipex *pipex, int code);

#endif
