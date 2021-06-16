/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:29:10 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 13:36:36 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_sorted_dec(t_stack s)
{
    int i;

    i = s->top - 1;
    while (i >= 0)
    {
        if (s->items[i] > s->items[i + 1])
            return(0);
        i--;
    }
    return (1);
}

int is_sorted_inc(t_stack s)
{
    int i;

    i = s->top - 1;
    while (i >= 0)
    {
        if (s->items[i] < s->items[i + 1])
            return(0);
        i--;
    }
    return (1);
}

int	is_already_in_stack(int nb, t_stack s)
{
	int	i;

	i = s->top;
	while (i >= 0)
	{
		if (nb == s->items[i])
			return (1);
		i--;
	}
	return (0);
}


