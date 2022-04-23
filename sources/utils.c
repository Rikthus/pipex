/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:58 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/23 19:38:47 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_cmd_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(*join));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '/';
	i++;
	j = 0;
	while (s2[i])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

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
		free((data->list_cmd)->cmd_access);
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
