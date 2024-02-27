/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_route.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:26:04 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/26 15:53:30 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_route(t_data *data, int len, int i, int j)
{
	char	*routetmp;
	char	*routetmp2;

	data->route = ft_calloc(len + 1, sizeof(char *));
	if (!data->route)
		return (EXIT_FAILURE);
	while (data->cmd[++i] != NULL)
	{
		j = -1;
		while (data->path[++j] != NULL)
		{
			routetmp = ft_strjoin(data->path[j], "/");
			routetmp2 = ft_strjoin(routetmp, data->cmd[i][0]);
			free(routetmp);
			if (access(routetmp2, F_OK) == 0 && access(routetmp2, X_OK) == 0)
			{
				data->route[i] = routetmp2;
				routetmp2 = NULL;
				break ;
			}
			free(routetmp2);
		}
	}
	data->route[i] = NULL;
	return (EXIT_SUCCESS);
}
