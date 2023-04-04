/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/04 14:06:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	***cmds;

	if (argc < 5)
		return (0);
	paths = parse_paths(envp);
	if (!paths)
		return (0);
	cmds = parse_commands(argv, argc);
	if (!cmds)
		return (0);
	// if (are_commands_valid(cmds, argc, paths) == FALSE)
	// {
	// 	ft_printf("Nope\n");
	// 	return (0);
	// }
	return (0);
}

void	free_all_strs(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_strs_free(tab[i], ft_strs_len(tab[i]));
		i++;
	}
}