/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:51:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/30 19:27:41 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rotations_till_push(const t_stack s, int c, int rotation_dir)
{
	int	i;
	int	should_get_to_top;
	int	min_index;

	min_index = stack_min_index(s);
	should_get_to_top = -1;
	i = 0;
	if (c < s->items[min_index])
		should_get_to_top = min_index;
	else
	{
		while (++i < s->size(s) + 1)
			if (should_get_to_top == -1
				&& s->items[(min_index + i) % s->size(s)] < c)
				should_get_to_top = (min_index + i - 1) % s->size(s);
	}
	if (rotation_dir < 0)
		return (-((should_get_to_top + 1) % s->size(s)));
	else
		return (s->top - should_get_to_top);
}

t_cost	lesser_cost(t_cost cost1, t_cost cost2)
{
	if (ft_max(ft_abs(cost1.for_a), ft_abs(cost1.for_b))
		< ft_max(ft_abs(cost2.for_a), ft_abs(cost2.for_b)))
		return (cost1);
	return (cost2);
}

t_cost	get_cost(t_stack a, t_stack b, int p_index)
{
	t_cost	cost_rr;
	t_cost	cost_rrr;

	cost_rr.for_a = rotations_till_push(a, b->items[p_index], 1);
	cost_rr.for_b = b->top - p_index;
	cost_rrr.for_a = rotations_till_push(a, b->items[p_index], -1);
	cost_rrr.for_b = -((p_index + 1) % b->size(b));
	if (a->size(a) <= 2)
		return (cost_rr);
	return (lesser_cost(cost_rr, cost_rrr));
}

t_cost	find_best_pivot(t_stack a, t_stack b)
{
	int		i;
	t_cost	min_cost;
	int		chunk;

	min_cost.for_a = 10 * a->maxsize;
	min_cost.for_b = 10 * a->maxsize;
	chunk = NUMBER_OF_CHUNKS - 1;
	while (++chunk <= NUMBER_OF_CHUNKS)
	{
		i = -1;
		while (++i < b->size(b))
		{
			if (b->items[i] < chunk * (1 + (a->maxsize / NUMBER_OF_CHUNKS)))
				min_cost = lesser_cost(min_cost, get_cost(a, b, i));
		}
	}
	return (min_cost);
}

char	*rotate_to_pivot(t_stack a, t_stack b, t_cost rotations, char *ans)
{
	if (rotations.for_a < 0 || rotations.for_b < 0)
	{
		while (rotations.for_a < 0 && rotations.for_b < 0)
		{
			ans = exec_and_str_op(a, b, "rrr", ans);
			rotations.for_a++;
			rotations.for_b++;
		}
		while (rotations.for_a < 0)
		{
			ans = exec_and_str_op(a, b, "rra", ans);
			rotations.for_a++;
		}
		while (rotations.for_b < 0)
		{
			ans = exec_and_str_op(a, b, "rrb", ans);
			rotations.for_b++;
		}
	}
	else
	{
		while (rotations.for_a > 0 && rotations.for_b > 0)
		{
			ans = exec_and_str_op(a, b, "rr", ans);
			rotations.for_a--;
			rotations.for_b--;
		}
		while (rotations.for_a > 0)
		{
			ans = exec_and_str_op(a, b, "ra", ans);
			rotations.for_a--;
		}
		while (rotations.for_b > 0)
		{
			ans = exec_and_str_op(a, b, "rb", ans);
			rotations.for_b--;
		}
	}
	return (ans);
}

int	is_in_arr(int val, t_arr arr, int len)
{
	int	i;

	if (!arr.arr)
		return (0);
	i = -1;
	while (++i < len)
	{
		if (val == arr.arr[i])
			return (1);
	}
	return (0);
}

int	gssa_arr(t_stack a, int **ret)
{
	int		*arr;
	int		val;
	int		max_val;
	int		i;
	t_arr	items;

	i = -1;
	max_val = 0;
	*ret = NULL;
	while (++i < a->size(a))
	{
		if (a->items[0] < max_val * 1.2)
			break ;
		arr = (int *)malloc(sizeof(int) * (a->size(a)));
		if (!arr)
			error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
		items.arr = a->items;
		items.size = a->size(a);
		arr[0] = a->items[0];
		val = gssa(items, &arr, 1, 0);
		if (val > max_val)
		{
			max_val = val;
			free(*ret);
			*ret = arr;
		}
		else
			free(arr);
		op_rotate(a);
	}
	delete_stack(&a);
	return (max_val);
}

char	*discard_in_chunks(t_stack a, t_stack b, t_arr to_keep, char *ans)
{
	int	initial_stack_len;
	int	deleted;
	int	i;
	int	len;
	int	chunk;

	deleted = 0;
	initial_stack_len = a->size(a);
	chunk = 0;
	while (++chunk <= NUMBER_OF_CHUNKS)
	{
		len = a->size(a);
		i = -1;
		while (++i < len && a->size(a) > 2)
		{
			if (!is_in_arr(a->peek(a), to_keep, to_keep.size) && a->peek(a)
				<= chunk * (1 + (initial_stack_len / NUMBER_OF_CHUNKS)))
			{
				deleted++;
				ans = exec_and_str_op(a, b, "pb", ans);
			}
			else
				ans = exec_and_str_op(a, b, "ra", ans);
		}
	}
	return (ans);
}

char	*discard_no_chunks(t_stack a, t_stack b, t_arr to_keep, char *ans)
{
	int	deleted;
	int	i;
	int	len;

	i = -1;
	deleted = 0;
	len = a->size(a);
	while (++i < len && a->size(a) > 2 && deleted < (len - to_keep.size))
	{
		if (!is_in_arr(a->peek(a), to_keep, to_keep.size))
		{
			deleted++;
			ans = exec_and_str_op(a, b, "pb", ans);
		}
		else
			ans = exec_and_str_op(a, b, "ra", ans);
	}
	return (ans);
}

int	find_decent_pos(t_arr list)
{
	int	best_length;
	int	best_pos;
	int	length;
	int	prev;
	int	i;
	int	j;

	best_length = 0;
	i = -1;
	while (++i < list.size)
	{
		length = 1;
		prev = list.arr[i];
		j = -1;
		while (++j < list.size)
		{
			if (list.arr[(i + j) % list.size] < prev)
			{
				prev = list.arr[(i + j) % list.size];
				length++;
			}
		}
		if (length > best_length)
		{
			best_pos = i;
			best_length = length;
		}
	}
	return (best_pos);
}

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

char	*insert_sort2(t_stack a, t_stack b)
{
	char	*ans;
	t_cost	rotations;
	t_arr	to_keep;

	ans = ft_strdup("");
	if (a->size(a) <= 105)
		to_keep.size = gssa_arr(a->copy(a), &to_keep.arr);
	else
		to_keep.size = ge_gssa_arr(a, &to_keep);
	if (a->size(a) > 105)
		ans = discard_in_chunks(a, b, to_keep, ans);
	else
		ans = discard_no_chunks(a, b, to_keep, ans);
	while (!b->is_empty(b))
	{
		rotations = find_best_pivot(a, b);
		ans = rotate_to_pivot(a, b, rotations, ans);
		ans = exec_and_str_op(a, b, "pa", ans);
	}
	if (a->peek(a) > a->size(a) / 2)
		while (!is_sorted_inc(a))
			ans = exec_and_str_op(a, b, "ra", ans);
	else
		while (!is_sorted_inc(a))
			ans = exec_and_str_op(a, b, "rra", ans);
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}
