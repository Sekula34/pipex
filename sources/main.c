/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:44:19 by fseles            #+#    #+#             */
/*   Updated: 2023/10/30 18:44:21 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

//wait for child and close read if read write is 0, 
//close write is read write is 1
void	parent_action( int read_write, int *pipe_fd)
{
	wait(NULL);
	close(pipe_fd[read_write]);
}

int	main(int argc, char *argv[], char **envp)
{
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];

	if (argc != 5)
		error_handler(1);
	if (pipe(pipe_fd) < 0)
		error_handler(2);
	pid = fork();
	if (pid < 0)
		error_handler(3);
	if (pid == 0)
		action_1(argv[1], argv[2], envp, pipe_fd);
	else
	{
		parent_action(1, pipe_fd);
		pid2 = fork();
		if (pid2 < 0)
			error_handler(3);
		if (pid2 == 0)
			action_2(argv[4], argv[3], envp, pipe_fd);
		parent_action(0, pipe_fd);
	}
	return (0);
}
