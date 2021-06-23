/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:21:45 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/23 11:25:06 by ede-thom         ###   ########.fr       */
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

void	free_queue(t_queue q)
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
	if(!q || !tmp)
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
			if (operation_coherence(tmp, operations[i]))
			{
				tmp2 = ft_strjoin(tmp, operations[i]);
				enqueue(q, tmp2);
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

	sort_algo_list[0] = insert_sort1;
	sort_algo_list[1] = bubble_sort;
	sort_algo_list[2] = bounce_sort;
	sort_algo_list[3] = NULL;

	ans = brute_swap2(a, b, ops);
	//free(ans);
	//ans = NULL;
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
				fprintf(stderr, "algo %d is better\n", i);
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
	char *argv2[10] = {"lol", "1", "2", "4", "3"};

	(void)argc;
	(void)argv;
	(void)argv2;
	a = parse_stack(argc, argv);
	b = new_stack(a->maxsize);
	//printf("testing : %d\n", test_instructions(a->copy(a),b->copy(b), ""));
	push_swap(a, b);
	delete_stack(&b);
	delete_stack(&a);
	return (0);
}