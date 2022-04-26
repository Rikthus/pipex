/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:58 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/26 22:07:34 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	adder(t_cmd **list_cmd, t_cmd *elem)
{
	t_cmd	*current;

	if (!*list_cmd)
		*list_cmd = elem;
	else
	{
		current = *list_cmd;
		while (current->next)
			current = current->next;
		current->next = elem;
	}
}

int	full_path_input(t_cmd *elem)
{
	char	*one_cmd;
	int		i;

	elem->cmd_access = ft_strdup(elem->cmd[0]);
	if (!(elem->cmd_access))
		return (0);
	i = 0;
	while (elem->cmd[0][i])
	{
		if (elem->cmd[0][i] == '/')
			one_cmd = &(elem->cmd[0][i]);
		i++;
	}
	one_cmd++;
	one_cmd = ft_strdup(one_cmd);
	if (!one_cmd)
		return (0);
	free(elem->cmd[0]);
	elem->cmd[0] = one_cmd;
	return (1);
}

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
	while (s2[j])
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
		free((data->list_cmd)->cmd_access);
		while((data->list_cmd)->cmd[i])
		{
			free((data->list_cmd)->cmd[i]);
			i++;
		}
		free((data->list_cmd)->cmd);
		data->list_cmd = (data->list_cmd)->next;
		free(previous);
	}
	if (data->fd_infile != -1)
		close(data->fd_infile);
	if (data->fd_outfile != -1)
		close(data->fd_outfile);
	free(data);
}
