/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:50:48 by fseles            #+#    #+#             */
/*   Updated: 2023/10/31 11:50:50 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

//search every line in env and return one that begins with "PATH=
//return will be somthing like /nfs/home/bin:/local/blabla/bin...
//return NULL if that line does not exist.
//this function does not allocate
char	*get_all_paths(char **envp)
{
	int			i;
	const char	key[6] = "PATH=";
	char		*env_start;

	i = 0;
	while (envp[i] != NULL)
	{
		env_start = ft_substr(envp[i], 0, 5);
		if (env_start == NULL)
			return (NULL);
		if (ft_strncmp(env_start, key, 5) == 0)
		{
			free(env_start);
			return (envp[i] + 5);
		}
		i++;
		free(env_start);
		env_start = NULL;
	}
	return (NULL);
}

//allocates and return correct path if path exist and have access to it
// example /usr/bin/ls
// Return null if path is not found;
char	*correct_path(char *plain_cmd, char *one_path)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(one_path, plain_cmd);
	if (cmd_path == NULL)
		return (NULL);
	if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
	{
		return (cmd_path);
	}
	free(cmd_path);
	return (NULL);
}

//allocates and return cmd path
//example for ls returns /usr/bin/ls
//return NULL if cant find or dont have access to execute
char	*get_cmd_path(char *cmd, char *all_paths)
{
	char	*plain_cmd;
	char	**one_by_one_path;
	int		i;
	char	*cmd_path;

	i = 1;
	if (cmd == NULL || all_paths == NULL)
		return (NULL);
	plain_cmd = get_plain_cmd(cmd);
	if (plain_cmd == NULL)
		return (NULL);
	one_by_one_path = ft_split(all_paths, ':');
	if (one_by_one_path == NULL)
		return (free(plain_cmd), NULL);
	cmd_path = correct_path(plain_cmd, one_by_one_path[0]);
	while (cmd_path == NULL && (one_by_one_path[i] != NULL))
	{
		cmd_path = correct_path(plain_cmd, one_by_one_path[i]);
		i++;
	}
	free(plain_cmd);
	free_arr(one_by_one_path);
	return (cmd_path);
}
