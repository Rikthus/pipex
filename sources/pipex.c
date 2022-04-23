/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:14:38 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/23 02:48:28 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	make_pipe(t_data *data)
{
	pid_t	pid;
	int		pipe_a[2];
	int		pipe_b[2];

	if (pipe(pipe_a) == -1 || pipe(pipe_b) == -1)
		return (0);
	while (data->list_cmd)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		if (pid == 0)
		{
			
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
	{
		write(1, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		return (1);
	}
	data = malloc(sizeof(*data));
	if (!data)
		exit(0);
	if (!init_data(data, argc, argv, envp) || !make_pipe(data))
	{
		write(1, "Error\n", 6);
		free_data(data);
		return (1);
	}
	return (0);
}