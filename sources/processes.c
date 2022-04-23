/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:36:04 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/23 19:37:54 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_access(t_data *data)
{
	int		i;
	char	*is_path;

	i = 0;
	if (ft_strchr((data->list_cmd)->cmd, 47)
		&& access((data->list_cmd)->cmd, X_OK))
	{
		(data->list_cmd)->cmd_access = (data->list_cmd)->cmd;
		if (!((data->list_cmd)->cmd_access))
			return (0);
		return (1);
	}
	while (data->path[i])
	{
		is_path = ft_cmd_join(data->path[i], (data->list_cmd)->cmd);
		if (access(is_path, X_OK))
		{
			(data->list_cmd)->cmd_access = is_path;
			if (!((data->list_cmd)->cmd_access))
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	first_process(t_data *data, int *pipe_line, int *pipe_tmp)
{
	if(dup2() == -1)
		exit(1);

}

void	last_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	if (dup2() == -1)
		exit(1);
}

void	inter_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	if (dup2() == -1)
		exit(1);
}
