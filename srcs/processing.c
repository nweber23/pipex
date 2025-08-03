/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:12:54 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 14:32:33 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_prcs(int *fd, char **argv, char **envp)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (out_file < 0)
	{
		close(fd[1]);
		close(fd[0]);
		close(out_file);
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(out_file, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	close(out_file);
	execution(argv[3], envp);
}

void	child_prcs(int *fd, char **argv, char **envp)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY);
	if (in_file < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(in_file);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	dup2(in_file, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(in_file);
	execution(argv[2], envp);
}
