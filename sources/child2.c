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

//check if file exist 
//if exist check if have write permision if not, exit
//if file does not exist create it and set variable craate to 1;
//return file descriptor to outputfile
int	file_handler(char *output_file, int *is_created)
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
	*is_created = 1;
	return (return_fd);
}

//execute command located at cmd2_path, with cmd2 arguments and envp
//if execve fails free splited cmd2_args
void	command_executer(char *cmd2_path, char *cmd2, char **envp)
{
	char	**cmd2_args;

	cmd2_args = ft_split(cmd2, ' ');
	if (cmd2_args != NULL)
		execve(cmd2_path, cmd2_args, envp);
	free_arr(cmd2_args);
}

void	action_2(char *output_file, char *cmd2, char **envp, int *pipe_fd)
{
	int		output_fd;
	char	*cmd2_path;
	char	**cmd2_args;
	int		is_created;

	is_created = 0;
	output_fd = file_handler(output_file, &is_created);
	if (output_fd == -1)
		error_handler(4);
	cmd2_path = get_cmd_path(cmd2, get_all_paths(envp));
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error_handler(5);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		error_handler(5);
	close(pipe_fd[1]);
	if (cmd2_path != NULL)
		command_executer(cmd2_path, cmd2, envp);
	if (is_created == 1)
		unlink(output_file);
	free(cmd2_path);
	error_handler(6);
	exit(1);
}
