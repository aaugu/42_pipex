/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:37:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/25 10:55:10 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	char	**paths;
	char	**cmd_args;
	char	*cmds[2];
	char	*cmds_path[2];
	int		fd_in;
	int		fd_out;
	t_bool	infile;
	int		pipe[2];
}			t_pipex;

void	init(t_pipex *pipex, int argc, char **argv, char **envp);
char	*get_cmd(char *full_cmd);
char	*get_cmd_path(char **paths, char *cmd_args, char *cmd);
int		process(t_pipex *pipex, char **argv, char **envp);
int		get_pos(char *s, char c);
char	**split_quotes(char *args, char quote);
void	error_message(char *arg, char *message);
void	error_exit(t_pipex *pipex, char *arg, char *message, int code);
void	end_pipex(t_pipex *pipex, int code);

#endif
