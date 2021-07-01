#ifndef QUEUE_H
# define QUEUE_H

# include <stdlib.h>
# include "ft_error.h"

# define QUEUE_MALLOC_FAIL "malloc failed when enqueing element"

typedef struct s_q_node
{
	char			*key;
	struct s_q_node	*next;
}*t_q_node;

typedef struct s_queue
{
	t_q_node	front;
	t_q_node	rear;
}*t_queue;

t_queue		create_queue(void);
void		enqueue(t_queue q, char *k);
char		*dequeue(t_queue q);
int			is_qempty(t_queue q);

#endif