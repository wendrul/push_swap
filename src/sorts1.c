/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:51:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/07/01 13:45:44 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*setup_arr(t_stack a, t_arr *items)
{
	int	*arr;

	arr = (int *)malloc(sizeof(int) * (a->size(a)));
	if (!arr)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	items->arr = a->items;
	items->size = a->size(a);
	arr[0] = a->items[0];
	return (arr);
}

static int	new_max(int val, int **ret, int *arr)
{
	int	max_val;

	max_val = val;
	free(*ret);
	*ret = arr;
	return (max_val);
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
		arr = setup_arr(a, &items);
		val = gssa(items, &arr, 1, 0);
		if (val > max_val)
			max_val = new_max(val, ret, arr);
		else
			free(arr);
		op_rotate(a);
	}
	delete_stack(&a);
	return (max_val);
}

char	*ins2_step2(t_stack a, t_stack b, char *ans)
{
	t_cost	rotations;

	while (!b->is_empty(b))
	{
		rotations = find_best_pivot(a, b);
		ans = rotate_to_pivot(a, b, rotations, ans);
		ans = exec_and_str_op(a, b, "pa", ans);
	}
	return (ans);
}

char	*insert_sort2(t_stack a, t_stack b)
{
	char	*ans;
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
	ans = ins2_step2(a, b, ans);
	if (a->peek(a) > a->size(a) / 2)
		while (!is_sorted_inc(a))
			ans = exec_and_str_op(a, b, "ra", ans);
	else
		while (!is_sorted_inc(a))
			ans = exec_and_str_op(a, b, "rra", ans);
	delete_stack(&a);
	delete_stack(&b);
	free(to_keep.arr);
	return (ans);
}
