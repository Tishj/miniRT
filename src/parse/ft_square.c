/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_square.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:09:10 by tbruinem       #+#    #+#                */
/*   Updated: 2020/01/02 19:13:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_square_clear(t_square **list)
{
	t_square	*iter;
	t_square	*del;

	iter = *list;
	while (iter)
	{
		del = iter;
		iter = iter->next;
		free(del);
	}
}

void		ft_square_addback(t_square **list, t_square *new)
{
	t_square	*iter;

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

t_square	*ft_square_new(void)
{
	t_square	*new;

	new = malloc(sizeof(t_square));
	if (!new)
		return (new);
	new->color = ft_color_init();
	new->prop = ft_prop_init();
	new->next = NULL;
	new->size = 0;
	return (new);
}

static void	**ft_square_properties(t_square *square)
{
	void	**properties;

	properties = malloc(sizeof(void *) * (10 + 1));
	if (!properties)
		return (properties);
	properties[0] = &square->prop.pivot.x;
	properties[1] = &square->prop.pivot.y;
	properties[2] = &square->prop.pivot.z;
	properties[3] = &square->prop.dir.x;
	properties[4] = &square->prop.dir.y;
	properties[5] = &square->prop.dir.z;
	properties[6] = &square->size;
	properties[7] = &square->color.red;
	properties[8] = &square->color.green;
	properties[9] = &square->color.blue;
	properties[10] = 0;
	return ((void **)properties);
}

int			ft_square_init(char *str, t_data *data, int i)
{
	t_square	*new;
	void		**ppty;

	new = ft_square_new();
	if (!new)
		return (ERR_MEM);
	ppty = ft_square_properties(new);
	if (!ppty)
	{
		free(new);
		return (ERR_MEM);
	}
	ft_ato_i_or_f(str + i, ppty, 6);
	ft_square_addback(&data->sqr, new);
	if (ft_isinrange_double(-1.0, 1.0, ppty[3], 3) == 0)
		return (ERR_RANGE);
	if (ft_isinrange_int(0, 255, ppty[7], 3) == 0)
		return (ERR_RANGE);
	free(ppty);
	return (0);
}
