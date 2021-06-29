/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:51:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/29 15:11:52 by ede-thom         ###   ########.fr       */
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

int rotations_till_push(const t_stack s_original, int c, int rotation_dir)
{
	t_stack s;
	int rrs;

	rrs = 0;
#ifdef VERBOSE_PUSH_SWAP
	if (!is_cycle_sorted(s_original))
		error_exit("wtf dude that shit aint even sorted", DEFAULT_ERROR);
#endif
	if (rotation_dir == 1)
	{
		s = s_original->copy(s_original);
		s->push(s, c);
		while (!is_cycle_sorted(s))
		{
			s->pop(s);
			op_rotate(s);
			s->push(s, c);
			rrs++;
		}
		delete_stack(&s);
	}
	else if (rotation_dir == -1)
	{
		s = s_original->copy(s_original);
		s->push(s, c);
		while (!is_cycle_sorted(s))
		{
			s->pop(s);
			op_rev_rotate(s);
			s->push(s, c);
			rrs--;
		}
		delete_stack(&s);
	}
	else
		error_exit("wrong direction", DEFAULT_ERROR);

	return (rrs);
}

int ft_abs(int n)
{
	if (n > 0)
		return (n);
	return (-n);
}

t_cost lesser_cost(t_cost cost1, t_cost cost2)
{
	if (ft_max(ft_abs(cost1.for_a), ft_abs(cost1.for_b)) < ft_max(ft_abs(cost2.for_a), ft_abs(cost2.for_b)))
		return (cost1);
	return (cost2);
}

t_cost get_cost(t_stack a, t_stack b, int p_index)
{
	t_cost cost_rr;
	t_cost cost_rrr;

	cost_rr.for_a = rotations_till_push(a, b->items[p_index], 1);
	cost_rr.for_b = b->top - p_index;

	cost_rrr.for_a = rotations_till_push(a, b->items[p_index], -1);
	cost_rrr.for_b = -(p_index + 1);

	return (lesser_cost(cost_rr, cost_rrr));
}

t_cost find_best_pivot(t_stack a, t_stack b)
{
	int i;
	t_cost min_cost;

#ifdef VERBOSE_PUSH_SWAP
	if (a->is_empty(a) || b->is_empty(b))
		error_exit("wtf can't find pivot on an empty stack", DEFAULT_ERROR);
#endif

	min_cost = get_cost(a, b, 0);
	i = -1;
	while (++i < b->size(b))
		min_cost = lesser_cost(min_cost, get_cost(a, b, i));
	return (min_cost);
}

char *rotate_to_pivot(t_stack a, t_stack b, t_cost rotations, char *ans)
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

int is_in_arr(int val, t_arr arr, int len)
{
	int i;

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



int gssa_arr(t_stack a, int **ret)
{
	int *arr;
	int val;
	int max_val;
	int i;

	i = -1;
	max_val = 0;
	*ret = NULL;
	while (++i < a->size(a))
	{
		if (a->items[0] < max_val * 5)
			break;
		arr = (int *)malloc(sizeof(int) * (a->size(a)));
		if (!arr)
			error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
		arr[0] = a->items[0];
		val = gssa(a->items, &arr, 1, 0, a->size(a));
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

char *discard_in_chunks(t_stack a, t_stack b, t_arr to_keep, char *ans)
{
	int initial_stack_len;
	int deleted;
	int i;
	int len;
	int chunk;

	deleted = 0;
	initial_stack_len = a->size(a);
	chunk = 0;
	while (++chunk <= NUMBER_OF_CHUNKS)
	{
		len = a->size(a);
		i = -1;
		while (++i < len && a->size(a) > 2)
		{
			if (!is_in_arr(a->peek(a), to_keep, to_keep.size) && a->peek(a) <= chunk * (1 + (initial_stack_len / NUMBER_OF_CHUNKS)))
			{
				deleted++;
				ans = exec_and_str_op(a, b, "pb", ans);
			}
			else
				ans = exec_and_str_op(a, b, "ra", ans);
		}
		// write(2, "\n\n\n", 3);
		// fprintf(stderr, "All elements lower than %d should have been erased\n", chunk * (1 + (initial_stack_len / NUMBER_OF_CHUNKS)));
		// print_stack(a);
		// write(2, "\n\n\n", 3);
	}
	return (ans);
}

char *insert_sort2(t_stack a, t_stack b)
{
	char *ans;
	t_cost rotations;

	ans = ft_strdup("");
	//fprintf(stderr, "starting\n");
	// while (!is_cycle_sorted(a))
	// {
	// 	if (a->peek(a) > a->items[a->top - 1])
	// 		ans = exec_and_str_op(a, b, "pb", ans);
	// 	else
	// 		ans = exec_and_str_op(a, b, "ra", ans);
	// }
	/* IDEALLY FIND AN ALGORITHM THAT FINDS THE BIGGEST SORTED SUBSET*/
	// while (a->size(a) > 2)
	// 	ans = exec_and_str_op(a, b, "pb", ans);

	t_arr to_keep;
	if (a->size(a) <= 105)
	{
		to_keep.size = gssa_arr(a->copy(a), &to_keep.arr);
	}
	else
	{
		to_keep.arr = NULL;
		to_keep.size = 0;
	}
	ans = discard_in_chunks(a, b, to_keep, ans);
#ifdef VERBOSE_PUSH_SWAP
	if (!is_cycle_sorted(a))
		error_exit("Stack not sorted wtf", DEFAULT_ERROR);
#endif
	fprintf(stderr, "step 1 finished (get sorted cycle) [%d operations]\n", current_ops);
	//printf("you should place %d at index [%d] aka %d\n", b->items[0], where_to_place(a, b->items[0]), a->items[where_to_place(a, b->items[0])]);
	// t_stack test;
	// test = new_stack(20);
	// test->push(test, 8);
	// test->push(test, 3);
	// test->push(test, 2);
	// test->push(test, 1);
	// test->push(test, 9);
	// test->push(test, 4);
	// print_stack(test);
	// printf("iscyclesort: %d\n", is_cycle_sorted(test));
	// exit(0);
	while (!b->is_empty(b))
	{
		rotations = find_best_pivot(a, b);
		ans = rotate_to_pivot(a, b, rotations, ans);
		ans = exec_and_str_op(a, b, "pa", ans);
	}
	fprintf(stderr, "step 2 finished (pivot to a) [%d operations]\n", current_ops);

	while (!is_sorted_inc(a))
		ans = exec_and_str_op(a, b, "rra", ans);
	fprintf(stderr, "step 3 finished (rotate back)[%d operations]\n", current_ops);
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
