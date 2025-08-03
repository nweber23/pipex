/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:56:05 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 14:59:09 by nweber           ###   ########.fr       */
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

// Execution
void	execution(char *cmd, char **envp);

// Utils
char	*getpath(char *cmd, char **envp);
char	*ft_getenv(char *name, char **envp);
char	**default_env(void);
int		is_shell_script(char *cmd);

// Processing
void	child_prcs(int *fd, char **argv, char **envp);
void	parent_prcs(int *fd, char **argv, char **envp);

#endif