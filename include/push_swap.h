/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:19:55 by wendrul           #+#    #+#             */
/*   Updated: 2021/07/01 13:14:22 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "stack.h"
# include "queue.h"
# include "ft_error.h"

# define MALLOC_FAIL_ERROR "malloc failed"

/**
 * Use for debuging
**/
# define VERBOSE_PUSH_SWAP
# define ARG_NOT_NUMBER "argument is not a number"
# define ARG_DUPLICATE "argument is duplicate"
# define INVALID_OP "invalid operation"
# define AMOUNT_OF_SORTS 10
# define AMOUNT_OF_OPS 8
# define MAX_BFS_DEPTH 5

# define AMOUNT_OF_OPS 8
# define NUMBER_OF_CHUNKS 3
# define OPERATIONS "sa\n, sb\n, pa\n, pb\n, ra\n, rb\n, rra\n, rrb\n"

typedef struct s_cost {
	int	for_a;
	int	for_b;
}t_cost;

typedef struct s_arr
{
	int	*arr;
	int	size;
	int	cur;
}t_arr;

typedef char*	(*t_sort_algo)(t_stack a, t_stack b);

int			puswa_error(char *msg);
int			is_number(char *nbr_str);
int			name_cmp(char *s1, char *s2);
int			ft_abs(int n);
int			count_char(char *str, char c);
int			get_last_op(char *instructions, char last_op_buf[]);
int			is_in_arr(int val, t_arr arr, int len);

int			is_already_in_stack(int nb, t_stack s);
int			is_sorted_inc(t_stack s);
int			is_sorted_dec(t_stack s);
int			is_cycle_sorted(t_stack s);
int			stack_min_index(t_stack s);

void		op_swap(t_stack s);
void		op_push(t_stack from, t_stack to);
void		op_rotate(t_stack s);
void		op_rev_rotate(t_stack s);

t_stack		parse_stack(int argc, char **argv);
t_stack		indexify_stack(t_stack s);

char		*join_delete(char *str1, char *str2);
int			execute_op(t_stack a, t_stack b, char *op);
char		*exec_and_str_op(t_stack a, t_stack b, char *op, char *ans);

int			gssa(t_arr items, int **ret, int value, int cur_pos);
int			ge_gssa_arr(t_stack a, t_arr *to_keep);
int			find_decent_pos(t_arr list);

char		*bubble_sort(t_stack a, t_stack b);
char		*insert_sort1(t_stack a, t_stack b);
char		*insert_sort2(t_stack a, t_stack b);
char		*brute_swap2(t_stack a, t_stack b);

t_cost		find_best_pivot(t_stack a, t_stack b);
char		*rotate_to_pivot(t_stack a, t_stack b, t_cost rotations, char *ans);
char		*discard_in_chunks(t_stack a, t_stack b, t_arr to_keep, char *ans);
char		*discard_no_chunks(t_stack a, t_stack b, t_arr to_keep, char *ans);

#endif