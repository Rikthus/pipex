/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:14:38 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/27 17:43:00 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	void	choose_process(t_data *data, int *pipeline, int *pipe_tmp)
{
	if (data->current_cmd == 1)
		first_process(data, pipeline, pipe_tmp);
	else if (data->current_cmd == data->last_cmd)
		last_process(data, pipeline, pipe_tmp);
	else
		inter_process(data, pipeline, pipe_tmp);

}

static	int	make_pipe(t_data *data)
{
	pid_t	pid;
	int		pipeline[2];
	int		pipe_tmp[2];

	while (data->list_cmd)
	{
		if (data->current_cmd < data->last_cmd)
		{
			if (pipe(pipe_tmp) == -1)
				return (0);
		}
		pid = fork();
		if (pid == -1)
			return (0);
		if (pid == 0)
		{
			choose_process(data, pipeline, pipe_tmp);
			exit(0);
		}
		if (data->current_cmd > 1)
		{
			close(pipeline[0]);
			close(pipeline[1]);
		}
		pipeline[0] = pipe_tmp[0];
		pipeline[1] = pipe_tmp[1];
		data->current_cmd++;
		data->list_cmd = (data->list_cmd)->next;
	}
	while ((data->current_cmd)-- > 0)
		wait(NULL);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc < 5)
	{
		write(1, "Usage: ./pipex file1 cmd1 ... cmd2 file2\n", 41);
		perror(".pipex");
		return (1);
	}
	data = malloc(sizeof(*data));
	if (!data)
	{
		perror("./pipex");
		return (1);
	}
	if (!init_data(data, argc, argv, envp) || !make_pipe(data))
	{
		write(1, "Error\n", 6);
		free_data(data);
		perror("./pipex");
		return (1);
	}
	free_data(data);
	return (0);
}
