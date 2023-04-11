/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:37:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/11 13:00:35 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"

typedef struct s_pipex
{
	char	**paths;
	char	**cmds;
	char	*cmd_args;
	int		infile_fd;
	int		outfile_fd;
	int		*pipe[2];
} 			t_pipex;

char	**parse_paths(char **envp);
char	**parse_commands(char **argv, int argc);
char	*get_cmd_path(char **paths, char *cmd);
void	error_exit(t_pipex *pipex, char *message);
void	end_pipex(t_pipex *pipex);

#endif
