/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:00:21 by nweber            #+#    #+#             */
/*   Updated: 2025/08/03 11:21:48 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

#endif