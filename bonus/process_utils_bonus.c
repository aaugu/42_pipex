/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:26:50 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/27 13:59:17 by aaugu            ###   ########.fr       */
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
