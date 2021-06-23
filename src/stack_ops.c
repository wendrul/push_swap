/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:29:10 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/23 11:08:47 by ede-thom         ###   ########.fr       */
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

void execute_op(t_stack a, t_stack b, char *op)
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
	else if (name_cmp(op, "ss"))
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
    {
        ft_putstr_fd(op, STDERR_FILENO);
        ft_putendl_fd(": did not match any operations", STDERR_FILENO);
    }
}


