/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fseles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:54:45 by fseles            #+#    #+#             */
/*   Updated: 2023/10/31 16:54:46 by fseles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

//allocate new char * that have only plain cmd and /before it
//example "ls -la" retunr only /ls
//same is for "    ls     -la" /ls
//return NULL if allocation fails
char	*get_plain_cmd(char *cmd)
{
	char	*plain_cmd;
	int		i;
	int		j;
	int		len;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	i = 0;
	j = 1;
	len = ft_strlen(cmd);
	plain_cmd = ft_calloc(len + 2, sizeof(char));
	if (plain_cmd == NULL)
		return (NULL);
	plain_cmd[0] = '/';
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] != '\0' && cmd[i] != ' ')
	{
		plain_cmd[j] = cmd[i];
		i++;
		j++;
	}
	return (plain_cmd);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

//takes error_num and depending on error write message and exit process
//error_num 1 wrong number of parameters
//2 pipe failed
//3 fork failed
//4 open failed
//5 dup2 failed
void	error_handler(int error_num)
{
	if (error_num == 1)
		ft_putstr_fd("Program takes 4 arguments only\n", 2);
	if (error_num == 2)
		ft_putstr_fd("Pipe failed\n", 2);
	if (error_num == 3)
		ft_putstr_fd("Fork failed\n", 2);
	if (error_num == 4)
		ft_putstr_fd("Open failed\n", 2);
	if (error_num == 5)
		ft_putstr_fd("Dup2 failed\n", 2);
	exit (1);
}
