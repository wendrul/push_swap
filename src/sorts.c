/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:20:02 by ede-thom          #+#    #+#             */
/*   Updated: 2021/07/01 13:53:36 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	going_down(int *i)
{
	*i = 0;
	return (1);
}

char	*bubble_sort(t_stack a, t_stack b)
{
	char	*ans;
	int		i;
	int		going_up;

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
			going_up = going_down(&i);
	}
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

static char	*sort_3(t_stack a, char *ans)
{
	t_stack	empty;
	char	*tmp;

	empty = new_stack(a->maxsize);
	tmp = ft_strjoin(ans, brute_swap2(a, empty));
	if (!tmp)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	free(ans);
	ans = NULL;
	delete_stack(&empty);
	return (tmp);
}

char	*insert_sort1(t_stack a, t_stack b)
{
	char	*ans;
	char	*op;
	int		min_index;
	int		min;

	ans = ft_strdup("");
	while (a->size(a) > 3)
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
	ans = sort_3(a, ans);
	while (!b->is_empty(b))
		ans = exec_and_str_op(a, b, "pa", ans);
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}
