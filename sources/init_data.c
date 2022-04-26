/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:45:15 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/26 22:18:25 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	open_files(t_data *data, int argc, char **argv)
{
	data->fd_infile = open(argv[1], O_RDONLY);
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
	full_paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			full_paths = &(envp[i][5]);
		i++;
	}
	if (!full_paths)
	{
		data->path = ft_split("none", ' ');
		return (1);
	}
	data->path = ft_split(full_paths, ':');
	if (!data->path)
		return (0);
	return (1);
}

static	void	basic_init(t_data *data, char **envp, int argc)
{
	data->envp = envp;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->path = NULL;
	data->list_cmd = NULL;
	data->current_cmd = 1;
	data->last_cmd = argc - 3;
}

static	int	add_elem(t_cmd **list_cmd, char *command, char **path)
{
	t_cmd	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (0);
	elem->cmd_access = NULL;
	elem->cmd = ft_split(command, ' ');
	if (!elem->cmd)
		return (0);
	if (ft_strchr(elem->cmd[0], '/'))
	{
		if (!full_path_input(elem))
			return (0);
	}
	elem->next = NULL;
	adder(list_cmd, elem);
	find_access(elem, path);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv, char **envp)
{
	int	i;

	i = 2;
	basic_init(data, envp, argc);
	if (!open_files(data, argc, argv) || !find_path(data, envp))
		return (0);
	while (i < (argc - 1))
	{
		if (!add_elem(&(data->list_cmd), argv[i], data->path))
			return (0);
		i++;
	}
	return (1);
}
