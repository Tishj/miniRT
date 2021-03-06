/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_input_key.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 13:36:17 by tbruinem       #+#    #+#                */
/*   Updated: 2020/01/21 18:39:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_mlx_cam_rot(int keycode, t_data *data)
{
	if (keycode == H)
		data->cams->c2w = ft_newrotate(data, ft_quat_new(0, 1, 0, -ROT_SPEED));
	if (keycode == K)
		data->cams->c2w = ft_newrotate(data, ft_quat_new(0, 1, 0, ROT_SPEED));
	if (keycode == U)
		data->cams->c2w = ft_newrotate(data, ft_quat_new(1, 0, 0, ROT_SPEED));
	if (keycode == J)
		data->cams->c2w = ft_newrotate(data, ft_quat_new(1, 0, 0, -ROT_SPEED));
	if (keycode == N)
		data->cams->c2w = ft_newrotate(data, ft_quat_new(0, 0, 1, ROT_SPEED));
	if (keycode == M)
		data->cams->c2w = ft_newrotate(data, ft_quat_new(0, 0, 1, -ROT_SPEED));
	ft_quat_print(data->cams->quat, "after adding a rotation");
	ft_matrix_print(data->cams->c2w, "matrix from quat");
	ft_mlx_render(data);
	return (1);
}

int	ft_mlx_cam_move(int keycode, t_data *data)
{
	t_matrix	dup;
	t_matrix	add;

	if (keycode == Z)
		data->cams->prop.pivot.z -= 0.5;
	if (keycode == X)
		data->cams->prop.pivot.z += 0.5;
	if (keycode == D)
		data->cams->prop.pivot.x += 0.5;
	if (keycode == A)
		data->cams->prop.pivot.x -= 0.5;
	if (keycode == W)
		data->cams->prop.pivot.y += 0.5;
	if (keycode == S)
		data->cams->prop.pivot.y -= 0.5;
	ft_mlx_render(data);
	return (0);
}

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
	if (keycode == Z || keycode == X || keycode == W ||
		keycode == S || keycode == A || keycode == D)
		return (ft_mlx_cam_move(keycode, data));
	if (keycode == U || keycode == H || keycode == J ||
		keycode == K || keycode == N || keycode == M)
		return (ft_mlx_cam_rot(keycode, data));
	return (0);
}
