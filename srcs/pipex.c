/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:17:01 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 10:13:26 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**setup_environment(char **envp, bool *use_default_env)
{
	char	**default_envp;

	*use_default_env = false;
	if (!envp || !*envp)
	{
		default_envp = default_env();
		if (!default_envp)
			exit(EXIT_FAILURE);
		*use_default_env = true;
		return (default_envp);
	}
	return (envp);
}

static void	cleanup_and_exit(char **envp, bool use_default_env, int exit_code)
{
	if (use_default_env)
		ft_array_free(envp);
	exit(exit_code);
}

static void	create_pipe_and_fork(int *fd, pid_t *pid,
	char **envp, bool use_default_env)
{
	if (pipe(fd) == -1)
		cleanup_and_exit(envp, use_default_env, -1);
	*pid = fork();
	if (*pid == -1)
	{
		perror("Fork failed");
		cleanup_and_exit(envp, use_default_env, EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**final_envp;
	bool	use_default_env;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
		exit(0);
	}
	final_envp = setup_environment(envp, &use_default_env);
	create_pipe_and_fork(fd, &pid, final_envp, use_default_env);
	if (!pid)
		child_prcs(fd, argv, final_envp);
	parent_prcs(fd, argv, final_envp);
	cleanup_and_exit(final_envp, use_default_env, 0);
}
