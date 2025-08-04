/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:53:53 by nweber            #+#    #+#             */
/*   Updated: 2025/08/04 13:53:01 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	wait_children(pid_t *pids, int num_children)
{
	int	i;
	int	status;
	int	last_exit_code;

	last_exit_code = 0;
	i = 0;
	while (i < num_children)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (i == num_children - 1)
				last_exit_code = status >> 8;
		}
		i++;
	}
	return (last_exit_code);
}

void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}
