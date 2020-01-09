/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_key.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 13:36:17 by tbruinem       #+#    #+#                */
/*   Updated: 2020/01/09 11:07:21 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_mlx_keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!param)
		return (0);
	if (keycode == SPACE)
		mlx_clear_window(data->mlx.data, data->mlx.window);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(data->mlx.data, data->mlx.window);
		ft_data_clear(data);
		mlx_destroy_image(data->mlx.data, data->mlx.image1);
		mlx_destroy_image(data->mlx.data, data->mlx.image2);
		mlx_destroy_window(data->mlx.data, data->mlx.window);
		exit(0);
	}
	return (0);
}
