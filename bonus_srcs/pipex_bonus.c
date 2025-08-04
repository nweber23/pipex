/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:53:53 by nweber            #+#    #+#             */
/*   Updated: 2025/08/04 12:09:13 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	main(int argc, char **argv, char **envp)
{
	char	**final_envp;
	bool	use_default_env;
	int		num_commands;

	if (argc < 5)
	{
		ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> ... <cmdN> <file2>\n");
		exit(0);
	}
	num_commands = argc - 3;
	final_envp = setup_environment(envp, &use_default_env);
	handling(argv, final_envp, num_commands);
	cleanup_and_exit(final_envp, use_default_env, 0);
}
