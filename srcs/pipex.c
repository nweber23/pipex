/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweber <nweber@student.42Heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:17:01 by nweber            #+#    #+#             */
/*   Updated: 2025/08/01 13:40:32 by nweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handling(void)
{
	ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	int	fd[2];

	if (argc != 5)
		exit_handling();
	// open file1
	// open or create file 2
	// create pipe
	// fork cmd1
	// fork cmd2
	// fork n cmds
	// execute up to n cmds
	// close pipe/waits
	// cleanup/exit
}
