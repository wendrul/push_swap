/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:51:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/23 11:23:29 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char *bounce_sort(t_stack a, t_stack b)
{
	char *ans;
	int i;
	int going_up;

	ans = ft_strdup("");
	i = 0;
	going_up = 1;
	while (!is_sorted_inc(a))
	{
		if (going_up)
		{
			/* This is exactly the same as down there on bubble*/
			if (i < a->size(a) - 1 && a->items[a->top] > a->items[a->top - 1])
				ans = exec_and_str_op(a, b, "sa", ans);
			if (is_sorted_inc(a))
				break ;
			ans = exec_and_str_op(a, b, "ra", ans);
			if (++i >= a->size(a))
				going_up = 0;
		}
		else
		{
			if (a->items[a->top] > a->items[a->top - 1])
				ans = exec_and_str_op(a, b, "sa", ans);
			if (is_sorted_inc(a))
				break ;
			if (i > 1)
				ans = exec_and_str_op(a, b, "rra", ans);
			if (--i <= 0)
				going_up = 1;
		}
	}
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

char *bubble_sort(t_stack a, t_stack b)
{
	char *ans;
	int i;
	int going_up;

	ans = ft_strdup("");
	i = 0;
	going_up = 1;
	while (!is_sorted_inc(a))
	{
		if (going_up)
		{
			if (i < a->size(a) - 1 && a->items[a->top] > a->items[a->top - 1])
				ans = exec_and_str_op(a, b, "sa", ans);
			if (is_sorted_inc(a))
				break ;
			ans = exec_and_str_op(a, b, "ra", ans);
			if (++i >= a->size(a))
				going_up = 0;
		}
		else
		{
			going_up = 1;
			i = 0;
		}
	}
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

char	*insert_sort1(t_stack a, t_stack b)
{
	char *ans;
	char *op;
	int min_index;
	int min;

	ans = ft_strdup("");
	while (!a->is_empty(a))
	{
		op = "ra";
		min_index = stack_min_index(a);
		min = a->items[min_index];
		if (min_index < a->size(a) / 2)
			op = "rra";
		while (a->peek(a) != min)
			ans = exec_and_str_op(a, b, op, ans);
		ans = exec_and_str_op(a, b, "pb", ans);
	}
	while (!b->is_empty(b))
		ans = exec_and_str_op(a, b, "pa", ans);
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

// char	*insert_sort2(t_stack a, t_stack b)
// {
	
// }