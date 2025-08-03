/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:06:23 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 11:08:02 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_shell_script(char *cmd)
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

static void	execute_script(char *cmd, char **envp)
{
	char	**all_cmds;

	all_cmds = ft_split(cmd, ' ');
	if (all_cmds && all_cmds[0])
	{
		if (execve(all_cmds[0], all_cmds, envp) == -1)
		{
			perror("Error executing script");
			ft_array_free(all_cmds);
			exit(EXIT_FAILURE);
		}
	}
	ft_array_free(all_cmds);
	exit(EXIT_FAILURE);
}

static void	execute_command(char *cmd, char **envp)
{
	char	**all_cmds;
	char	*path;

	all_cmds = malloc(4 * sizeof(char *));
	if (!all_cmds)
		exit(EXIT_FAILURE);
	all_cmds[0] = ft_strdup("sh");
	all_cmds[1] = ft_strdup("-c");
	all_cmds[2] = ft_strdup(cmd);
	all_cmds[3] = NULL;
	path = getpath("sh", envp);
	if (!path)
	{
		ft_putstr_fd("pipex: sh: command not found\n", STDERR_FILENO);
		ft_array_free(all_cmds);
		exit(127);
	}
	if (execve(path, all_cmds, envp) == -1)
	{
		perror("Error executing command");
		ft_array_free(all_cmds);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	execution(char *cmd, char **envp)
{
	if (is_shell_script(cmd))
		execute_script(cmd, envp);
	else
		execute_command(cmd, envp);
}
