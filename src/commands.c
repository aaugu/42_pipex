/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:53:14 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/11 11:28:46 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**parse_commands(char **argv, int argc)
{
	char	**cmds;
	int		nb_cmds;
	int		i;
	int		j;

	nb_cmds = argc - 3;
	cmds = (char **)malloc(sizeof(char *) * (nb_cmds + 1));
	if (!cmds)
		return (NULL);
	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		cmds[j] = ft_strdup(argv[i++]);
		if (!cmds[j])
		{
			ft_strs_free(cmds, nb_cmds);
			return (NULL);
		}
		j++;
	}
	cmds[nb_cmds] = NULL;
	return (cmds);
}
