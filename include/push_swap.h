/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:19:55 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/24 21:52:01 by ede-thom         ###   ########.fr       */
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
# define AMOUNT_OF_SORTS 10
# define AMOUNT_OF_OPS 8
# define MAX_BFS_DEPTH 5


typedef struct  s_cost {
    int for_a;
    int for_b;
}t_cost;

typedef char* (*t_sort_algo)(t_stack a, t_stack b);

int			puswa_error(char *msg);
int			is_number(char *nbr_str);
int			name_cmp(char *s1, char *s2);

int			is_already_in_stack(int nb, t_stack s);
int			is_sorted_inc(t_stack s);
int			is_sorted_dec(t_stack s);
int         is_cycle_sorted(t_stack s);
int         stack_min_index(t_stack s);

void		op_swap(t_stack s);
void		op_push(t_stack from, t_stack to);
void		op_rotate(t_stack s);
void		op_rev_rotate(t_stack s);

t_stack		parse_stack(int argc, char **argv);

char		*join_delete(char *str1, char *str2);
void		execute_op(t_stack a, t_stack b, char *op);
char		*exec_and_str_op(t_stack a, t_stack b, char *op, char *ans);

char    *bounce_sort(t_stack a, t_stack b);
char    *bubble_sort(t_stack a, t_stack b);
char	*insert_sort1(t_stack a, t_stack b);
char	*insert_sort2(t_stack a, t_stack b);
char    *geek_sort(t_stack a, t_stack b);

#endif