#include "push_swap.h"

static int	fdp_find_length(t_arr list, int i)
{
	int	length;
	int	j;
	int	prev;

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
	return (length);
}

int	find_decent_pos(t_arr list)
{
	int	best_length;
	int	best_pos;
	int	length;
	int	i;

	best_length = 0;
	i = -1;
	while (++i < list.size)
	{
		length = fdp_find_length(list, i);
		if (length > best_length)
		{
			best_pos = i;
			best_length = length;
		}
	}
	return (best_pos);
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
