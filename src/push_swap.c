/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:21:45 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 15:09:41 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void add_instruction(char instructions[], char *op)
{
	int i;
	int j;

	i = -1;
	j = ft_strlen(instructions);
	while (op[++i])
	{
		instructions[j] = op[i];
		j++;
	}
	instructions[j] = '\n';
	instructions[j + 1] = '\0';
}

void remove_instruction(char instructions[])
{
	int i;
	i = ft_strlen(instructions) - 2;
	while (i > 0 && instructions[i] != '\n')
	{
		i--;
	}
	if (instructions[i] == '\n')
		i++;
	while (instructions[i])
	{
		instructions[i] = '\0';
		i++;
	}
}

// void	replace_instruction(char instructions[])
// {
// }

void execute_op(t_stack a, t_stack b, char *op)
{
	if (name_cmp(op, "sa"))
		op_swap(a);
	else if (name_cmp(op, "sb"))
		op_swap(b);
	else if (name_cmp(op, "pa"))
		op_push(b, a);
	else if (name_cmp(op, "pb"))
		op_push(a, b);
	else if (name_cmp(op, "ra"))
		op_rotate(a);
	else if (name_cmp(op, "rb"))
		op_rotate(b);
	else if (name_cmp(op, "rra"))
		op_rev_rotate(b);
	else if (name_cmp(op, "rrb"))
		op_rev_rotate(b);
	else if (name_cmp(op, "ss"))
	{
		op_swap(a);
		op_swap(b);
	}
	else if (name_cmp(op, "rr"))
	{
		op_rotate(a);
		op_rotate(b);
	}
	else if (name_cmp(op, "rrr"))
	{
		op_rev_rotate(a);
		op_rev_rotate(b);
	}
}

#define AMOUNT_OF_OPS 8

char *brute_swap(t_stack a, t_stack b, char instructions[], char **operations, int depth)
{
	t_stack a_cpy;
	t_stack b_cpy;
	int i;
	char *ans;

	ans = NULL;
	if (depth > 12) //a->maxsize * 2 + 2)
		return (NULL);
	if (is_sorted_inc(a) && b->size(b) == 0)
		return (ft_strdup(instructions));
	i = -1;
	while (++i < AMOUNT_OF_OPS)
	{
		//fprintf(stderr, "\nsssss\n%seeeeeee\n", instructions);
		add_instruction(instructions, operations[i]);
		a_cpy = a->copy(a);
		b_cpy = b->copy(b);
//		printf("doing op %s :\n", operations[i]);
//		print_stack(a_cpy);
		execute_op(a_cpy, b_cpy, operations[i]);
//		print_stack(a_cpy);
//		printf("---------------\n");
		ans = brute_swap(a_cpy, b_cpy, instructions, operations, depth + 1);
		delete_stack(&a_cpy);
		delete_stack(&b_cpy);
		if (ans)
		{
			break;
		}
		remove_instruction(instructions);
	}
	return (ans);
}


int test_instructions(t_stack a, t_stack b, char *instructions)
{
	int ans;
	int i;
	char **steps;

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

int operation_coherence(char *instrctions, char *new_op)
{
	(void)new_op;
	(void)instrctions;

	return (1);
}

int count_char(char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char *brute_swap2(t_stack a, t_stack b, char **operations)
{
	int i;
	t_queue q;
	char *tmp;
	char *tmp2;

	tmp = ft_strdup("");
	q = create_queue();
	if(!q || !tmp)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	enqueue(q, tmp);
	while (!is_qempty(q))
	{
		tmp = dequeue(q);
		//`printf("\n\nsssssssss\n%seeeeeee\n\n", tmp);
		if (count_char(tmp, '\n') > 4)
			break;
		if (test_instructions(a->copy(a), b->copy(b), tmp))
			return (tmp);
		i = -1;
		while (++i < AMOUNT_OF_OPS)
		{
			if (operation_coherence(tmp, operations[i]))
			{
				tmp2 = ft_strjoin(tmp, operations[i]);
				enqueue(q, tmp2);
			}
		}
		free(tmp);
	}
	return (NULL);
}


void push_swap(t_stack a, t_stack b)
{
	char instrucions[300];
	char *ops[] = {"sa\n", "sb\n", "pa\n", "pb\n", "ra\n", "rb\n", "rra\n", "rrb\n"};
	instrucions[0] = 0;
	// char *ans = brute_swap(a, b, instrucions, ops, 0);
	char *ans = brute_swap2(a, b, ops);
	if (ans)
		ft_putstr_fd(ans, STDIN_FILENO);
	else
	{
		ft_putendl_fd("No solution found", STDERR_FILENO);
	}
}

int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	a = parse_stack(argc, argv);
	b = new_stack(a->maxsize);
	printf("testing : %d\n", test_instructions(a->copy(a),b->copy(b), "sa\n"));
	//push_swap(a, b);
	delete_stack(&b);
	delete_stack(&a);
	return (0);
}