#include "queue.h"

static t_q_node	new_qnode(char *k)
{
	t_q_node	temp;

	temp = (t_q_node)malloc(sizeof(*temp));
	if (!temp)
		return (NULL);
	temp->key = k;
	temp->next = NULL;
	return (temp);
}

t_queue	create_queue(void)
{
	t_queue	q;

	q = (t_queue)malloc(sizeof(*q));
	if (!q)
		return (NULL);
	q->front = NULL;
	q->rear = NULL;
	return (q);
}

int	is_qempty(t_queue q)
{
	return (q->front == NULL);
}

void	enqueue(t_queue q, char *k)
{
	t_q_node	temp;

	temp = new_qnode(k);
	if (!temp)
		error_exit(QUEUE_MALLOC_FAIL, FATAL_ERROR);
	if (q->rear == NULL)
	{
		q->front = temp;
		q->rear = temp;
		return ;
	}
	q->rear->next = temp;
	q->rear = temp;
}

char	*dequeue(t_queue q)
{
	t_q_node	temp;
	char		*ret;

	if (q->front == NULL)
		return (NULL);
	temp = q->front;
	ret = temp->key;
	q->front = q->front->next;
	if (q->front == NULL)
		q->rear = NULL;
	free(temp);
	return (ret);
}
