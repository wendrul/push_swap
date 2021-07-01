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
