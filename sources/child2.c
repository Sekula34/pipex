/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:39:52 by fseles            #+#    #+#             */
/*   Updated: 2023/11/01 19:39:54 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	file_handler(char *output_file)
{
	int	access_value;
	int	return_fd;

	access_value = access(output_file, F_OK);
	if (access_value == 0)
	{
		access_value = access(output_file, W_OK);
		if (access_value == -1)
		{
			perror("pipex:");
			exit(1);
		}
		return_fd = open(output_file, O_TRUNC | O_WRONLY);
		return (return_fd);
	}
	return_fd = open(output_file, O_WRONLY | O_CREAT, 0777);
	return (return_fd);
}

void	action_2(char *output_file, char *cmd2, char **envp, int *pipe_fd)
{
	int		output_fd;
	char	*cmd2_path;
	char	**cmd2_args;

	output_fd = file_handler(output_file);
	if (output_fd == -1)
		error_handler(4);
	cmd2_path = get_cmd_path(cmd2, get_all_paths(envp));
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error_handler(5);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		error_handler(5);
	close(pipe_fd[1]);
	if (cmd2_path != NULL)
	{
		cmd2_args = ft_split(cmd2, ' ');
		if (cmd2_args != NULL)
			execve(cmd2_path, cmd2_args, envp);
		free_arr(cmd2_args);
		free(cmd2_path);
	}
	exit(1);
}
