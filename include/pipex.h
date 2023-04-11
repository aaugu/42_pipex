/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:37:57 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/06 22:40:17 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"

typedef struct s_pipex
{
	char	**paths;
	char	**cmds;
	int		infile_fd;
	int		outfile_fd;
} 			t_pipex;

char	**parse_paths(char **envp);
char	**parse_commands(char **argv, int argc);

#endif
