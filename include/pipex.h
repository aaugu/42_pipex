/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:37:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/14 11:45:46 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**paths;
	char	**cmd_args;
	char	*cmd_path;
	int		fd_in;
	int		fd_out;
	int		pid[2];
	int		pipe[2];
}			t_pipex;

char	**parse_paths(char **envp);
char	*get_cmd_path(char **paths, char *cmd);
void	process(t_pipex *pipex, char **argv, char **envp);
void	error_exit(t_pipex *pipex, char *message, int code);
void	end_pipex(t_pipex *pipex, int code);

#endif
