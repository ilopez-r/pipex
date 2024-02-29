/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:22:30 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/28 12:29:30 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	split_path_bonus(char **path, t_data *data)
{
	while (ft_strncmp(*path, "PATH", 4) != 0)
		path++;
	*path = *path + 5;
	data->path = ft_split (*path, ':');
	if (data->path == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
