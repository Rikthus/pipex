/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:10:37 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/26 20:03:47 by maxperei         ###   ########lyon.fr   */
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
	char	*cmd;
	char	*cmd_access;
	char	**cmd_n_flags;
	struct	s_cmd	*next;
}	t_cmd;

typedef	struct s_data
{
	int		i_cmd;
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
void	find_access(t_data *data);
void	first_process(t_data *data, int *pipeline, int *pipe_tmp);
void	last_process(t_data *data, int *pipeline, int *pipe_tmp);
void	inter_process(t_data *data, int *pipeline, int *pipe_tmp);

// UTILS
char	*ft_cmd_join(char *s1, char *s2);
void	free_data(t_data *data);

#endif
