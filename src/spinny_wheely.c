#include "push_swap.h"

char	*rrr_to_pivot(t_stack a, t_stack b, char *ans, t_cost rotations)
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
	return (ans);
}

char	*rr_to_pivot(t_stack a, t_stack b, char *ans, t_cost rotations)
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
	return (ans);
}

char	*rotate_to_pivot(t_stack a, t_stack b, t_cost rotations, char *ans)
{
	if (rotations.for_a < 0 || rotations.for_b < 0)
		ans = rrr_to_pivot(a, b, ans, rotations);
	else
		ans = rr_to_pivot(a, b, ans, rotations);
	return (ans);
}
