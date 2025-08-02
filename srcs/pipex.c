/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:17:01 by nweber            #+#    #+#             */
/*   Updated: 2025/08/02 09:35:20 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_prcs(int *fd, char **argv, char **envp)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_file < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(out_file, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	execution(argv[3], envp);
}

void	child_prcs(int *fd, char **argv, char **envp)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY, 0777);
	if (in_file < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(in_file, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	execution(argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		exit(0);
	}
	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (!pid)
		child_prcs(fd, argv, envp);
	parent_prcs(fd, argv, envp);
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