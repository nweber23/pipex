/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:48:37 by nweber            #+#    #+#             */
/*   Updated: 2025/08/04 13:50:13 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_first(int **pipes, char **argv, char **envp, int num_commands)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY);
	if (in_file < 0)
	{
		close_pipes(pipes, num_commands - 1);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	dup2(in_file, STDIN_FILENO);
	dup2(pipes[0][1], STDOUT_FILENO);
	close_pipes(pipes, num_commands - 1);
	close(in_file);
	execution(argv[2], envp);
}

void	handle_middle(int **pipes, char **argv, char **envp, int cmd_index)
{
	dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	dup2(pipes[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipes, cmd_index + 1);
	execution(argv[cmd_index + 2], envp);
}

void	handle_last(int **pipes, char **argv, char **envp, int cmd_index)
{
	int	i;
	int	num_commands;
	int	out_file;

	i = 0;
	while (argv[i])
		i++;
	num_commands = i - 3;
	out_file = open(argv[num_commands + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_file < 0)
	{
		close_pipes(pipes, num_commands - 1);
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
	close_pipes(pipes, num_commands - 1);
	close(out_file);
	execution(argv[cmd_index + 2], envp);
}

static int	handle_helper(int **pipes, char **argv,
		char **envp, int num_commands)
{
	int		i;
	pid_t	*pids;
	int		exit_code;

	pids = malloc(num_commands * sizeof(pid_t));
	if (!pids)
		return (1);
	i = -1;
	while (++i < num_commands)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i == 0)
				handle_first(pipes, argv, envp, num_commands);
			else if (i == num_commands - 1)
				handle_last(pipes, argv, envp, i);
			else
				handle_middle(pipes, argv, envp, i);
		}
	}
	close_pipes(pipes, num_commands - 1);
	exit_code = wait_children(pids, num_commands);
	free(pids);
	return (exit_code);
}

int	handling(char **argv, char **envp, int num_commands)
{
	int		**pipes;
	int		i;
	int		exit_code;

	pipes = malloc((num_commands - 1) * sizeof(int *));
	if (!pipes)
		return (1);
	i = 0;
	while (i < num_commands - 1)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	exit_code = handle_helper(pipes, argv, envp, num_commands);
	i = 0;
	while (i < num_commands - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	return (exit_code);
}
