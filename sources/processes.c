/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:36:04 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/26 20:12:55 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	find_access(t_data *data)
{
	int		i;
	char	*is_path;

	while (data->list_cmd)
	{
		i = 0;
		if (access((data->list_cmd)->cmd, X_OK))
		{
			(data->list_cmd)->cmd_access = (data->list_cmd)->cmd;
			return ;
		}
		while (data->path[i])
		{
			is_path = ft_cmd_join(data->path[i], (data->list_cmd)->cmd);
			if (access(is_path, X_OK))
			{
				(data->list_cmd)->cmd_access = is_path;
				return ;
			}
			i++;
		}
		data->list_cmd = (data->list_cmd)->next;
	}
}

void	first_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	(void)pipeline;
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipe_tmp[1], STDOUT_FILENO) == -1)
		exit(1);
	execve((data->list_cmd)->cmd_access, (data->list_cmd)->cmd_n_flags,
			data->envp);
}


void	last_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	(void)pipe_tmp;
	if (dup2(pipeline[0], STDIN_FILENO))
		exit(1);
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		exit(1);
	execve((data->list_cmd)->cmd_access, (data->list_cmd)->cmd_n_flags,
			data->envp);
}

void	inter_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	if (dup2(pipeline[0], STDIN_FILENO) == -1)
		exit(1);
	if (dup2(pipe_tmp[1], STDOUT_FILENO) == -1)
		exit(1);
	execve((data->list_cmd)->cmd_access, (data->list_cmd)->cmd_n_flags,
			data->envp);
}
