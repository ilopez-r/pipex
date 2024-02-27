/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:02:17 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/27 15:43:07 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libftc/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_data
{
	int		file1;
	int		file2;
	char	**path;
	char	***cmd;
	char	**route;
}	t_data;

int		split_commands(int argc, char**argv, t_data *data);
int		split_path(char **path, t_data *data);
int		get_route(t_data *d, int len, int i, int j);
void	exec_route(t_data *data);

#endif