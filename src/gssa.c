/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gssa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:37:26 by ede-thom          #+#    #+#             */
/*   Updated: 2021/07/01 11:32:15 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ge_gssa_arr(t_stack a, t_arr *to_keep)
{
	int		pos;
	t_arr	list;
	int		i;
	int		prev;

	list.arr = a->items;
	list.size = a->size(a);
	pos = find_decent_pos(list);
	to_keep->arr = (int *)malloc(sizeof(int) * a->size(a));
	to_keep->size = 0;
	if (!to_keep->arr)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	i = -1;
	prev = -1;
	while (++i < a->size(a))
	{
		if (prev == -1 || prev > a->items[(pos + i) % a->size(a)])
		{
			to_keep->arr[to_keep->size] = a->items[(pos + i) % a->size(a)];
			to_keep->size++;
			prev = a->items[(pos + i) % a->size(a)];
		}
	}
	return (to_keep->size);
}

static int	gssa_ret(int value, int **ret, int **max_arr, int *max_val)
{
	if (value == 1)
	{
		free(*ret);
		*ret = *max_arr;
		*max_arr = NULL;
		value = *max_val;
		*max_val = 0;
		return (value);
	}
	return (value);
}

static int	copy_max_arr(int *max_arr, int **ret, int new_val)
{
	ft_memcpy(max_arr, *ret, new_val * sizeof(int));
	return (new_val);
}

static int	*alloc_static_max(int *max_arr, t_arr items)
{
	if (max_arr == NULL)
	{
		max_arr = (int *)malloc(sizeof(int) * items.size);
		if (max_arr == NULL)
			error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	}
	return (max_arr);
}

int	gssa(t_arr items, int **ret, int value, int cur_pos)
{
	static int	max_val = 0;
	static int	*max_arr = NULL;
	int			potential;
	int			i;
	int			new_val;

	max_arr = alloc_static_max(max_arr, items);
	if (value != 1 && (items.arr[cur_pos] <= 1 || cur_pos >= items.size))
		return (value);
	i = cur_pos;
	while (++i < items.size)
	{
		if (items.arr[i] < items.arr[cur_pos])
		{
			potential = ft_min(items.arr[i], items.size - i);
			if (potential > max_val)
			{
				(*ret)[value] = items.arr[i];
				new_val = gssa(items, ret, value + 1, i);
				if (new_val > max_val)
					max_val = copy_max_arr(max_arr, ret, new_val);
			}
		}
	}
	return (gssa_ret(value, ret, &max_arr, &max_val));
}
