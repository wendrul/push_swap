/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puswa_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 19:14:32 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/30 19:21:02 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_index(int *arr, int size, int element)
{
	int	i;
	int	amount_smaller;

	i = -1;
	amount_smaller = 0;
	while (++i < size)
	{
		if (arr[i] < element)
			amount_smaller++;
	}
	return (amount_smaller);
}

t_stack	indexify_stack(t_stack s)
{
	t_stack	idx;
	int		i;

	idx = s->copy(s);
	i = -1;
	while (++i < s->size(s))
	{
		idx->items[i] = get_index(s->items, s->size(s), s->items[i]) + 1;
	}
	return (idx);
}

int ft_abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

