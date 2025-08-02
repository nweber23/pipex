/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:54:03 by nweber            #+#    #+#             */
/*   Updated: 2025/08/02 09:39:02 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		env = ft_substr(envp[i], 0, j);
		if (ft_strcmp(env, name) == 0)
			return (free(env), envp[i] + j + 1);
		free(env);
		i++;
	}
	return (NULL);
}

char	*getpath(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*execution;
	char	**all_cmds;

	i = -1;
	all_paths = ft_split(ft_getenv("PATH", envp), ':');
	all_cmds = ft_split(cmd, ' ');
	while (all_paths[++i])
	{
		path = ft_strjoin(all_paths[i], "/");
		execution = ft_strjoin(path, all_cmds[0]);
		free(path);
		if (access(execution, F_OK | X_OK) == 0)
			return (ft_array_free(all_paths), execution);
		free(execution);
	}
	ft_array_free(all_paths);
	ft_array_free(all_cmds);
	return (ft_strdup(cmd));
}

void	execution(char *cmd, char **envp)
{
	char	**all_cmds;
	char	*path;

	all_cmds = ft_split(cmd, ' ');
	path = getpath(all_cmds[0], envp);
	if (execve(path, all_cmds, envp) == -1)
	{
		perror("Error executing command");
		ft_array_free(all_cmds);
		free(path);
		exit(EXIT_FAILURE);
	}
}
