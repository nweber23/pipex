/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:56:05 by nweber            #+#    #+#             */
/*   Updated: 2025/08/04 12:09:01 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

// Utils
void	execution(char *cmd, char **envp);
char	*getpath(char *cmd, char **envp);
char	*ft_getenv(char *name, char **envp);
void	child_prcs(int *fd, char **argv, char **envp);
void	parent_prcs(int *fd, char **argv, char **envp);
char	**default_env(void);
int		is_shell_script(char *cmd);
void	wait_children(pid_t *pids, int num_children);

// Pipes
void	close_pipes(int **pipes, int num_pipes);
void	handle_first(int **pipes, char **argv, char **envp, int num_commands);
void	handle_middle(int **pipes, char **argv, char **envp, int cmd_index);
void	handle_last(int **pipes, char **argv, char **envp, int cmd_index);
void	handling(char **argv, char **envp, int num_commands);

#endif