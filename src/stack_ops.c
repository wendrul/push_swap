/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:29:10 by wendrul           #+#    #+#             */
/*   Updated: 2021/07/01 13:35:34 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted_inc(t_stack s)
{
	int	i;

	i = s->top - 1;
	while (i >= 0)
	{
		if (s->items[i] < s->items[i + 1])
			return (0);
		i--;
	}
	return (1);
}

int	is_cycle_sorted(t_stack s)
{
	int	i;
	int	discontinuities;

	discontinuities = 0;
	i = 0;
	if (s->size(s) <= 2)
		return (1);
	if (s->items[s->top] < s->items[0])
		discontinuities++;
	while (i < s->size(s) - 1)
	{
		if (s->items[i] < s->items[i + 1])
			discontinuities++;
		i++;
	}
	return (discontinuities <= 1);
}

int	stack_min_index(t_stack s)
{
	int	i;
	int	min_index;

	i = 0;
	min_index = 0;
	while (i < s->size(s))
	{
		if (s->items[i] < s->items[min_index])
			min_index = i;
		i++;
	}
	return (min_index);
}

static int	exec_op_aux(t_stack a, t_stack b, char *op)
{
	if (name_cmp(op, "ss"))
	{
		op_swap(a);
		op_swap(b);
	}
	else if (name_cmp(op, "rr"))
	{
		op_rotate(a);
		op_rotate(b);
	}
	else if (name_cmp(op, "rrr"))
	{
		op_rev_rotate(a);
		op_rev_rotate(b);
	}
	else
		return (0);
	return (1);
}

int	execute_op(t_stack a, t_stack b, char *op)
{
	if (name_cmp(op, "sa"))
		op_swap(a);
	else if (name_cmp(op, "sb"))
		op_swap(b);
	else if (name_cmp(op, "pa"))
		op_push(b, a);
	else if (name_cmp(op, "pb"))
		op_push(a, b);
	else if (name_cmp(op, "ra"))
		op_rotate(a);
	else if (name_cmp(op, "rb"))
		op_rotate(b);
	else if (name_cmp(op, "rra"))
		op_rev_rotate(a);
	else if (name_cmp(op, "rrb"))
		op_rev_rotate(b);
	else
		return (exec_op_aux(a, b, op));
	return (1);
}
