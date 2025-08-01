/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:54:03 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 15:28:28 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handling(void)
{
	ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	exit(0);
}

char	*ft_getenv(char *name, char **envp)
{

}

char	*getpath(char *cmd, char **envp)
{

}

void	execution(char *cmd, char **envp)
{

}