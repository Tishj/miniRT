/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:10:56 by tbruinem       #+#    #+#                */
/*   Updated: 2020/01/01 22:56:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_plane_clear(t_plane **list)
{
	t_plane	*iter;
	t_plane	*del;

	iter = *list;
	while (iter)
	{
		del = iter;
		iter = iter->next;
		free(del);
	}
}

void		ft_plane_addback(t_plane **list, t_plane *new)
{
	t_plane	*iter;

	iter = *list;
	if (!iter)
	{
		*list = new;
		return ;
	}
	while (iter->next)
		iter = iter->next;
	iter->next = new;
}

t_plane		*ft_plane_new(void)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		return (new);
	new->color = ft_color_init();
	new->prop = ft_prop_init();
	new->next = NULL;
	return (new);
}

static void	**ft_plane_properties(t_plane *plane)
{
	void	**properties;

	properties = malloc(sizeof(void *) * (9 + 1));
	if (!properties)
		return (properties);
	properties[0] = &plane->prop.pivot.x;
	properties[1] = &plane->prop.pivot.y;
	properties[2] = &plane->prop.pivot.z;
	properties[3] = &plane->prop.dir.x;
	properties[4] = &plane->prop.dir.y;
	properties[5] = &plane->prop.dir.z;
	properties[6] = &plane->color.red;
	properties[7] = &plane->color.green;
	properties[8] = &plane->color.blue;
	properties[9] = 0;
	return ((void **)properties);
}

int			ft_plane_init(char *str, t_data *data, int i)
{
	t_plane		*new;
	void		**ppty;

	new = ft_plane_new();
	if (!new)
		return (ERR_MEM);
	ppty = ft_plane_properties(new);
	if (!ppty)
	{
		free(new);
		return (ERR_MEM);
	}
	ft_ato_i_or_f(str + i, ppty, 5);
	ft_plane_addback(&data->pln, new);
	if (ft_isinrange_double(0.0, 1.0, ppty[3], 3) == 0)
		return (ERR_RANGE);
	if (ft_isinrange_int(0, 255, ppty[6], 3) == 0)
		return (ERR_RANGE);
	free(ppty);
	return (0);
}
