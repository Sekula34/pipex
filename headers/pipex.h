/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:43:59 by fseles            #+#    #+#             */
/*   Updated: 2023/10/30 18:44:02 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	action_1(char *input_file, char *cmd1, char **envp, int *pipe_fd);
void	action_2(char *output_file, char *cmd2, char **envp, int *pipe_fd);
void	error_handler(int error_num);
void	free_arr(char **arr);
char	*get_all_paths(char **envp);
char	*get_cmd_path(char *cmd, char *all_paths);
char	*get_plain_cmd(char *cmd);

#endif