/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:33:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/04/11 12:54:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		open_files(t_pipex *pipex, char *file1, char *file2);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (0);
	if (open_files(&pipex, argv[1], argv[4]) == ERROR)
		error_exit(&pipex, "Error\nCan't open files");
	pipex.paths = parse_paths(envp);
	if (!pipex.paths)
		return (0);
	pipex.cmds = parse_commands(argv, argc);
	if (!pipex.cmds)
		return (0);
	return (0);
}

int	open_files(t_pipex *pipex, char *file1, char *file2)
{
	pipex->infile_fd = open(file1, O_RDONLY);
	pipex->outfile_fd = open(file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->infile_fd < 0 || pipex->outfile_fd > 0)
		return (-1);
	return (1);
}

void	error_exit(t_pipex *pipex, char *message)
{
	ft_printf("%s\n", message);
	end_pipex(pipex);
}

void	end_pipex(t_pipex *pipex)
{
	if (pipex->paths)
		ft_strs_free(pipex->paths, ft_strs_len(pipex->paths));
	if (pipex->cmds)
		ft_strs_free(pipex->cmds, 2);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	exit(0);
}
