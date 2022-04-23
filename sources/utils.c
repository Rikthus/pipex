/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:58 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/22 22:55:39 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_data(t_data *data)
{
	t_cmd	*previous;
	int		i;

	i = 0;
	free(data->path);
	while(data->list_cmd)
	{
		previous = data->list_cmd;
		free((data->list_cmd)->cmd);
		while((data->list_cmd)->cmd_n_flags[i])
		{
			free((data->list_cmd)->cmd_n_flags[i]);
			i++;
		}
		free((data->list_cmd)->cmd_n_flags);
		data->list_cmd = (data->list_cmd)->next;
		free(previous);
	}
	if (data->fd_infile != -1)
		close(data->fd_infile);
	if (data->fd_outfile != -1)
		close(data->fd_outfile);
	free(data);
}
