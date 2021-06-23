/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:51:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/23 17:41:42 by ede-thom         ###   ########.fr       */
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
				break;
			ans = exec_and_str_op(a, b, "ra", ans);
			if (++i >= a->size(a))
				going_up = 0;
		}
		else
		{
			if (a->items[a->top] > a->items[a->top - 1])
				ans = exec_and_str_op(a, b, "sa", ans);
			if (is_sorted_inc(a))
				break;
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
				break;
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

char *insert_sort1(t_stack a, t_stack b)
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

int	where_to_place(t_stack s, int c)
{
	int i;
	int max_index;

	#ifdef VERBOSE_PUSH_SWAP	
	if (!is_cycle_sorted(s))
		error_exit("wtf dude that shit aint even sorted", FATAL_ERROR);
	#endif
	i = 0;
	max_index = 0;
	while (i < s->size(s))
	{
		if (s->items[i] > s->items[max_index])
			i = max_index;
		i++;
	}
	i = max_index;
	while (c < s->items[max_index])
	{
		i++;
		if (i > s->size(s))
			i = 0;
	}
	return (i);
}

int	find_best_pivot(t_stack a, t_stack b, char **op, int *a_index)
{
	int i;
	int cost;
	int cost_min;
	int min_index;

	i = 0;
	cost_min = ft_max(b->top - 0, a->top - where_to_place(a, b->items[0]));
	min_index = 0;
	*op = "rr";
	*a_index = a->top - where_to_place(a, b->items[0]);
	while (i < b->size(b))
	{
		cost = ft_max(b->top - i, a->top - where_to_place(a, b->items[i]));
		if (cost < cost_min)
		{
			*a_index = a->top - where_to_place(a, b->items[i]);
			cost_min = cost;
			min_index = i;
		}
		i++;
	}
	i = 0;
	while (i < b->size(b))
	{
		cost = ft_max(i + 1, where_to_place(a, b->items[i]) + 1);
		if (cost < cost_min)
		{
			*a_index = where_to_place(a, b->items[i]) + 1;
			*op = "rrr";
			cost_min = cost;
			min_index = i;
		}
		i++;
	}
	return (min_index);
}

char	*insert_sort2(t_stack a, t_stack b)
{
	char *ans;
	int pivot;
	int below_pivot;
	int below_pivot_idx;
	char *op;
	

	ans = ft_strdup("");
	while (!is_cycle_sorted(a))
	{
		if (a->peek(a) > a->items[a->top - 1])
			ans = exec_and_str_op(a, b, "pb", ans);
		else
			ans = exec_and_str_op(a, b, "ra", ans);
	}
	while (!b->is_empty(b))
	{
		pivot = b->items[find_best_pivot(a, b, &op, &below_pivot_idx)];
		below_pivot = a->items[below_pivot_idx];
		printf("b-pivot: %d, a-pivot: %d\n", pivot, below_pivot);
		while (b->peek(b) != pivot && a->peek(a) != below_pivot)
			ans = exec_and_str_op(a, b, op, ans);
		op = name_cmp("rrr", op) ? "rrb" : "rb";
		while (b->peek(b) != pivot)
			ans = exec_and_str_op(a, b, op, ans);
		op = name_cmp("rrb", op) ? "rra" : "ra";
		while (a->peek(a) != below_pivot)
			ans = exec_and_str_op(a, b, op, ans);
		ans = exec_and_str_op(a, b, "pa", ans);
	}
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

char *geek_sort(t_stack a, t_stack b)
{
	char *ans;
	int tmp;

	ans = ft_strdup("");
	while (!a->is_empty(a))
	{
		tmp = a->peek(a);
		ans = exec_and_str_op(a, b, "pb", ans);
		ans = exec_and_str_op(a, b, "rb", ans);
		while (!b->is_empty(b) && b->peek(b) > tmp)
			ans = exec_and_str_op(a, b, "pa", ans);
		ans = exec_and_str_op(a, b, "rrb", ans);
	}
	while (!b->is_empty(b))
		ans = exec_and_str_op(a, b, "pa", ans);
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}
