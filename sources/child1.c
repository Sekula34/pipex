/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:54:02 by fseles            #+#    #+#             */
/*   Updated: 2023/10/31 14:54:03 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

//checks if file exist  exit 1 process if not
//then cheks if it can read from file 
//exit 1 if cant 
static void	file_checker(char *input_file)
{
	int	value;

	value = access(input_file, F_OK);
	if (value == -1)
	{
		perror("pipex");
		ft_printf("%s\n", input_file);
		exit(1);
	}
	value = access(input_file, R_OK);
	if (value == -1)
	{
		ft_printf("pipex: ");
		perror(input_file);
		exit(1);
	}
	return ;
}

void	action_1(char *input_file, char *cmd1, char **envp, int *pipe_fd)
{
	char	*cmd;
	char	**cmd_args;
	int		in_file;

	file_checker(input_file);
	in_file = open(input_file, O_RDONLY);
	if (in_file == -1)
		error_handler(4);
	if (dup2(in_file, STDIN_FILENO) == -1)
		error_handler(5);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error_handler(5);
	close(pipe_fd[0]);
	cmd = get_cmd_path(cmd1, get_all_paths(envp));
	if (cmd != NULL)
	{
		cmd_args = ft_split(cmd1, ' ');
		if (cmd_args != NULL)
			execve(cmd, cmd_args, envp);
		free_arr(cmd_args);
		free(cmd);
	}
	exit(0);
}
