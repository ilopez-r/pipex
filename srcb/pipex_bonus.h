/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:22:36 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/28 16:12:10 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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

int		split_commands_bonus(int argc, char**argv, t_data *data, int flag_arg);
int		split_path_bonus(char **path, t_data *data);
int		get_route_bonus(t_data *d, int len, int i, int j);
void	exec_route_bonus(t_data *data, char **argv, int argc, int flag_doc);

#endif