/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:55:57 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 14:58:02 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_script(char *cmd, char **envp)
{
	char	**all_cmds;

	all_cmds = ft_split(cmd, ' ');
	if (all_cmds && all_cmds[0])
	{
		if (execve(all_cmds[0], all_cmds, envp) == -1)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(all_cmds[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			ft_array_free(all_cmds);
			exit(127);
		}
	}
	ft_array_free(all_cmds);
}

static char	**prepare_shell_command(char *cmd)
{
	char	**all_cmds;

	all_cmds = malloc(4 * sizeof(char *));
	if (!all_cmds)
		exit(EXIT_FAILURE);
	all_cmds[0] = ft_strdup("sh");
	if (!all_cmds[0])
	{
		ft_array_free(all_cmds);
		exit(EXIT_FAILURE);
	}
	all_cmds[1] = ft_strdup("-c");
	if (!all_cmds[1])
	{
		ft_array_free(all_cmds);
		exit(EXIT_FAILURE);
	}
	all_cmds[2] = ft_strdup(cmd);
	if (!all_cmds[2])
	{
		ft_array_free(all_cmds);
		exit(EXIT_FAILURE);
	}
	all_cmds[3] = NULL;
	return (all_cmds);
}

static void	check_command_exists(char *cmd, char **envp)
{
	char	**cmd_parts;
	char	*cmd_name;

	cmd_parts = ft_split(cmd, ' ');
	if (!cmd_parts || !cmd_parts[0])
	{
		if (cmd_parts)
			ft_array_free(cmd_parts);
		return ;
	}
	cmd_name = cmd_parts[0];
	if (!getpath(cmd_name, envp) && !ft_strchr(cmd_name, '/'))
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_array_free(cmd_parts);
		exit(127);
	}
	ft_array_free(cmd_parts);
}

static void	execute_command(char *cmd, char **envp)
{
	char	**all_cmds;
	char	*path;

	check_command_exists(cmd, envp);
	all_cmds = prepare_shell_command(cmd);
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
