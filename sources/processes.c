/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:36:04 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/26 22:23:21 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	find_access(t_cmd *elem, char **path)
{
	int		i;
	char	*is_path;

	if (elem->cmd_access)
		return ;
	while (elem)
	{
		i = 0;
		while (path[i])
		{
			is_path = ft_cmd_join(path[i], elem->cmd[0]);
			if (access(is_path, X_OK))
			{
				elem->cmd_access = is_path;
				return ;
			}
			i++;
		}
		elem = elem->next;
	}
	printf("%s\n", elem->cmd_access);
}

void	first_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	(void)pipeline;
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipe_tmp[1], STDOUT_FILENO) == -1)
		exit(1);
		close(pipe_tmp[1]);
	execve((data->list_cmd)->cmd_access, (data->list_cmd)->cmd,
			data->envp);
}


void	last_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	(void)pipe_tmp;
	if (dup2(pipeline[0], STDIN_FILENO))
		exit(1);
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		exit(1);
		close(pipeline[0]);
	execve((data->list_cmd)->cmd_access, (data->list_cmd)->cmd,
			data->envp);
}

void	inter_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	if (dup2(pipeline[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipe_tmp[1], STDOUT_FILENO) == -1)
		exit(1);
		close(pipeline[0]);
		close(pipe_tmp[1]);
	execve((data->list_cmd)->cmd_access, (data->list_cmd)->cmd,
			data->envp);
}
