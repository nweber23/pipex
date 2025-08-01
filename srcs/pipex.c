/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:17:01 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:21:23 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_prcs(int *fd, char **argv, char **envp)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

void	child_prcs(int *fd, char **argv, char **envp)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY, 0777);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		exit_handling();
	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
}

	// open file1
	// open or create file 2
	// create pipe
	// fork cmd1
	// fork cmd2
	// fork n cmds
	// execute up to n cmds
	// close pipe/waits
	// cleanup/exit