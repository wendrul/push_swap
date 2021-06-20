/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:25:50 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/20 11:33:20 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ft_error.h"
#include <stdio.h>

int	size(t_stack self)
{
	return self->top + 1;
}

int	is_empty(t_stack self)
{
	return self->top == -1;
}

int	is_full(t_stack self)
{
	return self->top == self->maxsize - 1;
}

void	push(t_stack self, int val)
{
	if (is_full(self))
		error_exit(ERR_FULL_STACK_PUSH, DEFAULT_ERROR);
	self->items[++self->top] = val;
}

int	peek(t_stack self)
{
	if (!is_empty(self))
		return self->items[self->top];
	return (error_exit(ERR_EMPTY_STACK_PEEK, DEFAULT_ERROR));
}

int	pop(t_stack self)
{
	if (!is_empty(self))
		return self->items[self->top--];
	return (error_exit(ERR_EMPTY_STACK_POP, DEFAULT_ERROR));
}

t_stack	copy_stack(t_stack self)
{
	t_stack stack_cpy;
	int i;

	stack_cpy = new_stack(self->maxsize);
	stack_cpy->top = self->top;
	stack_cpy->size = self->size;
	stack_cpy->is_empty = self->is_empty;
	stack_cpy->is_full = self->is_full;
	stack_cpy->push = self->push;
	stack_cpy->peek = self->peek;
	stack_cpy->pop = self->pop;
	stack_cpy->copy = self->copy;
	i = self->top;
	while (i >= 0)
	{
		stack_cpy->items[i] = self->items[i];
		i--;
	}
	return (stack_cpy);
}

t_stack	new_stack(int capacity)
{
	t_stack self = (t_stack)malloc(sizeof(struct s_stack));

	self->maxsize = capacity;
	self->top = -1;
	self->items = (int*)malloc(sizeof(int) * capacity);
	if (!self->items)
		error_exit(ERR_NEW_STACK_MALLOC, FATAL_ERROR);
	self->size = size;
	self->is_empty = is_empty;
	self->is_full = is_full;
	self->push = push;
	self->peek = peek;
	self->pop = pop;
	self->copy = copy_stack;
	return (self);
}

void	print_stack(t_stack self)
{
	int i;

	if (!self)
		return ft_putendl_fd("    null_stack", STDERR_FILENO);
	i = self->top;
	ft_putstr_fd("    ", STDERR_FILENO);
	if (is_empty(self))
		ft_putstr_fd("\r   []|", STDERR_FILENO);
	while (i >= 0)
	{
		ft_putnbr_fd(self->items[i], STDERR_FILENO);
		ft_putstr_fd("| ", STDERR_FILENO);
		i--;
	}
	ft_putendl_fd("", STDERR_FILENO);
}

void	delete_stack(t_stack *s)
{
	free((*s)->items);
	(*s)->items = NULL;
	free(*s);
	*s = NULL;
}
