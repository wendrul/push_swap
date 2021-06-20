/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:45:57 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/20 11:17:55 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_swap(t_stack s)
{
	int nb1;
	int nb2;

	if (s->size(s) > 1)
	{
		nb1 = s->pop(s);
		nb2 = s->pop(s);
		s->push(s, nb1);
		s->push(s, nb2);
	}
}

void	op_push(t_stack from, t_stack to)
{
	if (!from->is_empty(from))
	{
		to->push(to, from->pop(from));
	}
}

void	op_rotate(t_stack s)
{
	int tmp;
	int i;

	if (s->size(s) <= 1)
		return;
	i = s->top;
	tmp = s->items[s->top];
	while (i > 0)
	{
		s->items[i] = s->items[i - 1];
		i--;
	}
	s->items[0] = tmp;
}

void	op_rev_rotate(t_stack s)
{
	int tmp;
	int i;

	if (s->size(s) <= 1)
		return;
	i = 0;
	tmp = s->items[0];
	while (i < s->top)
	{
		s->items[i] = s->items[i + 1];
		i++;
	}
	s->items[s->top] = tmp;
}


