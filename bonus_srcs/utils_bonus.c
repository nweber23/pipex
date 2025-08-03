/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:56:03 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 14:57:01 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**default_env(void)
{
	char	**envp;

	envp = malloc(2 * sizeof(char *));
	if (!envp)
		return (NULL);
	envp[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/\
		bin:/usr/sbin:/usr/bin:/sbin:/bin");
	if (!envp[0])
		return (free(envp), NULL);
	envp[1] = NULL;
	return (envp);
}

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
			return (ft_array_free(all_paths),
				ft_array_free(all_cmds), execution);
		free(execution);
	}
	ft_array_free(all_paths);
	ft_array_free(all_cmds);
	return (NULL);
}

int	is_shell_script(char *cmd)
{
	int		fd;
	char	buffer[3];
	int		bytes_read;

	if (ft_strchr(cmd, '/') || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			fd = open(cmd, O_RDONLY);
			if (fd != -1)
			{
				bytes_read = read(fd, buffer, 2);
				close(fd);
				if (bytes_read == 2 && buffer[0] == '#' && buffer[1] == '!')
					return (1);
			}
			return (1);
		}
	}
	return (0);
}
