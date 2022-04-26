/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:10:37 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/26 21:53:35 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include "../libft_me/libft.h"

typedef	struct	s_cmd
{
	char	*cmd_access;
	char	**cmd;
	struct	s_cmd	*next;
}	t_cmd;

typedef	struct s_data
{
	int		current_cmd;
	int		last_cmd;
	int		fd_infile;
	int		fd_outfile;
	char	**envp;
	char	**path;
	t_cmd	*list_cmd;
}	t_data;

// INIT_DATA
int		init_data(t_data *data, int argc, char **argv, char **envp);

// PROCESSES
void	find_access(t_cmd *elem, char **path);
void	first_process(t_data *data, int *pipeline, int *pipe_tmp);
void	last_process(t_data *data, int *pipeline, int *pipe_tmp);
void	inter_process(t_data *data, int *pipeline, int *pipe_tmp);

// UTILS
void	adder(t_cmd **list_cmd, t_cmd *elem);
int		full_path_input(t_cmd *elem);
char	*ft_cmd_join(char *s1, char *s2);
void	free_data(t_data *data);

#endif
