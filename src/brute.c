/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:59:21 by ede-thom          #+#    #+#             */
/*   Updated: 2021/07/01 11:07:40 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	test_instructions(t_stack a, t_stack b, char *instructions)
{
	int		ans;
	int		i;
	char	**steps;

	ans = 0;
	steps = ft_split_charset(instructions, "\n");
	if (!steps)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	i = -1;
	while (steps[++i])
	{
		execute_op(a, b, steps[i]);
		free(steps[i]);
	}
	free(steps);
	if (is_sorted_inc(a) && b->size(b) == 0)
		ans = 1;
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

static int	operation_coherence(char *instructions, char *new_op)
{
	char	last[12];

	if (!get_last_op(instructions, last))
		return (1);
	if (name_cmp(new_op, "sa")
		&& (name_cmp(last, "sa") || name_cmp(last, "sb")))
		return (0);
	else if (name_cmp(new_op, "sb") && (name_cmp(last, "sb")))
		return (0);
	else if (name_cmp(new_op, "pa") && (name_cmp(last, "pb")))
		return (0);
	else if (name_cmp(new_op, "pb") && (name_cmp(last, "pa")))
		return (0);
	else if (name_cmp(new_op, "ra") && (name_cmp(last, "rra")))
		return (0);
	else if (name_cmp(new_op, "rra") && (name_cmp(last, "ra")))
		return (0);
	else if (name_cmp(new_op, "rb") && (name_cmp(last, "rrb")))
		return (0);
	else if (name_cmp(new_op, "rrb") && (name_cmp(last, "rb")))
		return (0);
	return (1);
}

static void	free_queue(t_queue q, char **ops)
{
	int	i;

	i = -1;
	while (ops[++i])
		free(ops[i]);
	free(ops);
	while (!is_qempty(q))
	{
		free(dequeue(q));
	}
	free(q);
}

static void	queue_new_op(char *tmp, char **operations, t_queue q)
{
	char	*tmp2;
	int		i;

	i = -1;
	while (++i < AMOUNT_OF_OPS)
	{
		if (count_char(tmp, '\n') < 7)
		{
			if (operation_coherence(tmp, operations[i]))
			{
				tmp2 = ft_strjoin(tmp, operations[i]);
				enqueue(q, tmp2);
			}
		}
	}
}

char	*brute_swap2(t_stack a, t_stack b)
{
	t_queue	q;
	char	*tmp;
	char	**operations;

	operations = ft_split_charset(OPERATIONS, ", ");
	tmp = ft_strdup("");
	q = create_queue();
	if (!q || !tmp)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	enqueue(q, tmp);
	while (!is_qempty(q))
	{
		tmp = dequeue(q);
		if (count_char(tmp, '\n') > MAX_BFS_DEPTH)
			break ;
		if (test_instructions(a->copy(a), b->copy(b), tmp))
		{
			free_queue(q, operations);
			return (tmp);
		}
		queue_new_op(tmp, operations, q);
		free(tmp);
	}
	free_queue(q, operations);
	return (NULL);
}
