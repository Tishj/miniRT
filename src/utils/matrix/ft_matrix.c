/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_matrix.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 12:39:43 by tbruinem       #+#    #+#                */
/*   Updated: 2020/01/21 21:00:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_matrix_print(t_matrix mat, char *name)
{
	int i;
	int j;

	printf("matrix: %10s\n", name);
	printf("row1: %6f, %6f, %6f\n", mat.r1.x, mat.r1.y, mat.r1.z);
	printf("row2: %6f, %6f, %6f\n", mat.r2.x, mat.r2.y, mat.r2.z);
	printf("row3: %6f, %6f, %6f\n", mat.r3.x, mat.r3.y, mat.r3.z);
	printf("\n");
}

t_vec		ft_matrix_apply(t_matrix mat, t_vec old)
{
	t_vec	new;

	new.x = old.x * mat.r1.x + old.y * mat.r2.x + old.z * mat.r3.x;
	new.y = old.x * mat.r1.y + old.y * mat.r2.y + old.z * mat.r3.y;
	new.z = old.x * mat.r1.z + old.y * mat.r2.z + old.z * mat.r3.z;
	return (new);
}

t_matrix	ft_matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix	new;

	ft_matrix_print(a, "old c2w");
	ft_matrix_print(b, "rotation mat");

	new.r1.x = a.r1.x * b.r1.x + a.r2.x * b.r1.y + a.r3.x * b.r1.z;
	new.r1.y = a.r1.y * b.r1.x + a.r2.y * b.r1.y + a.r3.y * b.r1.z;
	new.r1.z = a.r1.z * b.r1.x + a.r2.z * b.r1.y + a.r3.z * b.r1.z;
	new.r2.x = a.r1.x * b.r2.x + a.r2.x * b.r2.y + a.r3.x * b.r2.z;
	new.r2.y = a.r1.y * b.r2.x + a.r2.y * b.r2.y + a.r3.y * b.r2.z;
	new.r2.z = a.r1.z * b.r2.x + a.r2.z * b.r2.y + a.r3.z * b.r2.z;
	new.r3.x = a.r1.x * b.r3.x + a.r2.x * b.r3.y + a.r3.x * b.r3.z;
	new.r3.y = a.r1.y * b.r3.x + a.r2.x * b.r3.y + a.r3.y * b.r3.z;
	new.r3.z = a.r1.y * b.r3.x + a.r2.x * b.r3.y + a.r3.z * b.r3.z;
	new.r1 = ft_vec_normalize(new.r1);
	new.r2 = ft_vec_normalize(new.r2);
	new.r3 = ft_vec_normalize(new.r3);
	ft_matrix_print(new, "new c2w");
	return (new);
}

t_matrix	ft_lookat(t_cam *cam)
{
	t_matrix	new;
	t_vec		cam_f;
	t_vec		cam_r;
	t_vec		cam_u;

	ft_vec_print(cam->prop.dir, "direction");
	cam_f = ft_vec_normalize(ft_vec_sub(cam->prop.pivot,
			ft_vec_add(cam->prop.pivot, cam->prop.dir)));
	ft_vec_print(cam_f, "camera forward");
	cam_r = ft_crossp(ft_vec_init(0, 1, 0), cam_f);
	cam_u = ft_crossp(cam_f, cam_r);
	ft_vec_print(cam_u, "lookat up vector");
	new.r1.x = cam_r.x;
	new.r1.y = cam_u.x;
	new.r1.z = cam_f.x;
	new.r2.x = cam_r.y;
	new.r2.y = cam_u.y;
	new.r2.z = cam_f.y;
	new.r3.x = cam_r.z;
	new.r3.y = cam_u.z;
	new.r3.z = cam_f.z;
	ft_matrix_print(new, "lookat matrix\n");
	return (new);
}

/* void		ft_matrix_mult(t_matrix a, t_matrix b, t_matrix new)
{
	int			index;
	int			row;
	int			col;

	row = 0;
	index = 0;
	ft_matrix_init(new);
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			while (index < 4)
			{
				new[row][col] += a[row][index] * b[index][col];
				index++;
			}
			col++;
			index = 0;
		}
		row++;
	}
}
*/