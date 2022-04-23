/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:45:15 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/23 17:56:28 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	open_files(t_data *data, int argc, char **argv)
{
	data->fd_infile = open(argv[1], O_CREAT | O_RDONLY | O_TRUNC, 0644);
	if (data->fd_infile == -1)
		return (0);
	data->fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		return (0);
	return (1);
}

static	int	find_path(t_data *data, char **envp)
{
	int		i;
	char	*full_paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (ft_strlen(envp[i]) < 6)
				return (0);
			full_paths = envp[i];
			break ;
		}
		i++;
	}
	data->path = ft_split(full_paths, ':');
	if (!data->path)
		return (0);
	return (1);
}

static	void	basic_init(t_data *data, char **envp)
{
	data->envp = envp;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->path = NULL;
	data->list_cmd = NULL;
}

static	int	add_elem(t_cmd **list_cmd, char **argv, int i)
{
	t_cmd	*elem;
	t_cmd	*current;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (0);
	elem->cmd_n_flags = ft_split(argv[i], ' ');
	if (!elem->cmd_n_flags)
		return (0);
	elem->cmd = ft_strdup(elem->cmd_n_flags[0]);
	if (!elem->cmd)
		return (0);
	elem->next = NULL;
	if (!*list_cmd)
		*list_cmd = elem;
	else
	{
		current = *list_cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = elem;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv, char **envp)
{
	int	i;

	i = 2;
	basic_init(data, envp);
	if (!open_files(data, argc, argv) || !find_path(data, envp))
		return (0);
	while (i < (argc - 1))
	{
		if (!add_elem(&(data->list_cmd), argv, i))
			return (0);
		i++;
	}
	return (1);
}
