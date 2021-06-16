/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:25:50 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 12:27:54 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ft_error.h"

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

t_stack	new_stack(int capacity)
{
	t_stack self = (t_stack )malloc(sizeof(struct s_stack));

	self->maxsize = capacity;
	self->top = -1;
	self->items = (int *)malloc(sizeof(int) * capacity);
	if (!self->items)
		error_exit(ERR_NEW_STACK_MALLOC, FATAL_ERROR);
	self->size = size;
	self->is_empty = is_empty;
	self->is_full = is_full;
	self->push = push;
	self->peek = peek;
	self->pop = pop;
	return (self);
}

void	print_stack(t_stack self)
{
	int i;

	i = self->top;
	ft_putstr_fd("    ", STDIN_FILENO);
	if (is_empty(self))
		ft_putstr_fd("\r  ...|", STDIN_FILENO);
	while (i >= 0)
	{
		ft_putnbr_fd(self->items[i], STDIN_FILENO);
		ft_putstr_fd("| ", STDIN_FILENO);
		i--;
	}
	ft_putendl_fd("", STDIN_FILENO);
}