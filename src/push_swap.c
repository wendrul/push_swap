/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:21:45 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/30 16:07:21 by ede-thom         ###   ########.fr       */
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

// char *brute_swap(t_stack a, t_stack b, char instructions[], char **operations, int depth)
// {
// 	t_stack a_cpy;
// 	t_stack b_cpy;
// 	int i;
// 	char *ans;

// 	ans = NULL;
// 	if (depth > 12) //a->maxsize * 2 + 2)
// 		return (NULL);
// 	if (is_sorted_inc(a) && b->size(b) == 0)
// 		return (ft_strdup(instructions));
// 	i = -1;
// 	while (++i < AMOUNT_OF_OPS)
// 	{
// 		//fprintf(stderr, "\nsssss\n%seeeeeee\n", instructions);
// 		add_instruction(instructions, operations[i]);
// 		a_cpy = a->copy(a);
// 		b_cpy = b->copy(b);
// //		printf("doing op %s :\n", operations[i]);
// //		print_stack(a_cpy);
// 		execute_op(a_cpy, b_cpy, operations[i]);
// //		print_stack(a_cpy);
// //		printf("---------------\n");
// 		ans = brute_swap(a_cpy, b_cpy, instructions, operations, depth + 1);
// 		delete_stack(&a_cpy);
// 		delete_stack(&b_cpy);
// 		if (ans)
// 		{
// 			break;
// 		}
// 		remove_instruction(instructions);
// 	}
// 	return (ans);
// }

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
	// fprintf(stderr, "deletingSTACKS\n");
	// print_stack(a);
	// print_stack(b);
	delete_stack(&a);
	delete_stack(&b);
	return (ans);
}

int get_last_op(char *instructions, char last_op_buf[])
{
	int i;
	int j;
	i = ft_strlen(instructions) - 2;
	if (i < 0)
		return (0);
	while (i > 0 && instructions[i] != '\n')
	{
		i--;
	}
	if (instructions[i] == '\n')
		i++;
	j = 0;
	while (instructions[i] != '\n')
	{
		last_op_buf[j] = instructions[i];
		i++;
		j++;
	}
	last_op_buf[j] = '\0';
	return (1);
}

int operation_coherence(char *instructions, char *new_op)
{
	char last[12];

	if (!get_last_op(instructions, last))
		return (1);
	if (name_cmp(new_op, "sa") && (name_cmp(last, "sa") || name_cmp(last, "sb")))
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

void free_queue(t_queue q)
{
	while (!is_qempty(q))
	{
		free(dequeue(q));
	}
	free(q);
}

char *brute_swap2(t_stack a, t_stack b, char **operations)
{
	int i;
	t_queue q;
	char *tmp;
	char *tmp2;

	tmp = ft_strdup("");
	q = create_queue();
	if (!q || !tmp)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	enqueue(q, tmp);
	while (!is_qempty(q))
	{
		tmp = dequeue(q);
		//`printf("\n\nsssssssss\n%seeeeeee\n\n", tmp);
		if (count_char(tmp, '\n') > MAX_BFS_DEPTH)
			break;
		if (test_instructions(a->copy(a), b->copy(b), tmp))
		{
			free_queue(q);
			return (tmp);
		}
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
		free(tmp);
	}
	free_queue(q);
	return (NULL);
}

void push_swap(t_stack a, t_stack b)
{
	char *ops[] = {"sa\n", "sb\n", "pa\n", "pb\n", "ra\n", "rb\n", "rra\n", "rrb\n"};
	char *ans;
	char *ans2;
	t_sort_algo sort_algo_list[AMOUNT_OF_SORTS + 1];
	int i;

	sort_algo_list[0] = insert_sort2;
	sort_algo_list[1] = insert_sort1;
	sort_algo_list[2] = bubble_sort;
	sort_algo_list[3] = NULL;

	(void)ops;
	ans = NULL;
	if (a->size(a) > 5)
		sort_algo_list[1] = NULL;
	else
		ans = brute_swap2(a, b, ops);
	if (ans)
		ft_putstr_fd(ans, STDOUT_FILENO);
	else
	{
		i = -1;
		while (sort_algo_list[++i])
		{
			ans2 = sort_algo_list[i](a->copy(a), b->copy(b));
			if (!ans || count_char(ans, '\n') > count_char(ans2, '\n'))
			{
				free(ans);
				ans = ans2;
			}
			else
				free(ans2);
		}
		ft_putstr_fd(ans, STDOUT_FILENO);
	}
	free(ans);
}

int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;
	char *argv2[10] = {"lol", "1", "2", "4", "3", "9", "8"};
	current_ops = 0;
	(void)argc;
	(void)argv;
	(void)argv2;
	a = parse_stack(argc, argv);
	b = indexify_stack(a);
	delete_stack(&a);
	a = b;
	b = new_stack(a->maxsize);
	//printf("testing : %d\n", test_instructions(a->copy(a),b->copy(b), ""));
	push_swap(a, b);
	delete_stack(&b);
	delete_stack(&a);
	return (0);
}