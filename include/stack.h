/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:25:17 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 14:39:54 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

# define SUCCESS 69
# define IS_FULL_ERROR 70
# define ERR_NEW_STACK_MALLOC "malloc failed when creating a new stack"
# define ERR_FULL_STACK_PUSH "tried pushing into a full stack"
# define ERR_EMPTY_STACK_POP "tried to pop an empty stack"
# define ERR_EMPTY_STACK_PEEK "tried to peek an empty stack"

typedef struct s_stack
{
	int maxsize;
	int top;
	int *items;
	int (*size)(struct s_stack *self);
	int (*is_empty)(struct s_stack *self);
	int (*is_full)(struct s_stack *self);
	int (*peek)(struct s_stack *self);
	int (*pop)(struct s_stack *self);
	void (*push)(struct s_stack *self, int val);
	struct s_stack* (*copy)(struct s_stack *self);

}*t_stack;


void	    print_stack(t_stack self);
t_stack     new_stack(int capacity);
void		delete_stack(t_stack *s);  

#endif