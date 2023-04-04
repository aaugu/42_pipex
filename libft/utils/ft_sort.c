/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:46:07 by aaugu             #+#    #+#             */
/*   Updated: 2023/03/19 18:34:43 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_sort(int *list, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = 0;
	while (j < size - 1)
	{
		if (!ft_is_sort(list, size))
		{
			while (i < size - 1)
			{
				if (list[i] > list[i + 1])
				{
					temp = list[i];
					list[i] = list[i + 1];
					list[i + 1] = temp;
				}
				i++;
			}
			i = 0;
		}
		j++;
	}
}

t_bool	ft_is_sort(int *list, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (list[i] > list[i + 1])
			return (0);
		i++;
	}
	return (1);
}

// void	ft_sort_strs(char **list, int size)
// {
// 	int	i;

// 	i = 1;
// 	while (i < size - 1)
// 	{
// 		if (ft_strcmp(list[i], list[i + 1]) > 0)
// 		{
// 			ft_swap_str(&list[i], &list[i + 1]);
// 			i = 0;
// 		}
// 		i++;
// 	}
// }
