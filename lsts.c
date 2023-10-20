#include "main.h"

/**
 * add_nd - add a nn
 * @head: head
 * @s: ssing
 * @n: ii
 * Return: size
 */
list_t *add_nd(list_t **head, const char *s, int n)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->num = n;
	if (s)
	{
		n_head->str = _strdup(s);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * add_nd_end - adds a nn to the end of the list
 * @head: address of pointer to head nn
 * @ss: str field of nn
 * @num: nn ii used by history
 *
 * Return: size of list
 */
list_t *add_nd_end(list_t **head, const char *ss, int num)
{
	list_t *new_nn, *nn;

	if (!head)
		return (NULL);

	nn = *head;
	new_nn = malloc(sizeof(list_t));
	if (!new_nn)
		return (NULL);
	_memset((void *)new_nn, 0, sizeof(list_t));
	new_nn->num = num;
	if (ss)
	{
		new_nn->str = _strdup(ss);
		if (!new_nn->str)
		{
			free(new_nn);
			return (NULL);
		}
	}
	if (nn)
	{
		while (nn->next)
			nn = nn->next;
		nn->next = new_nn;
	}
	else
		*head = new_nn;
	return (new_nn);
}

/**
 * p_lst_str - print list
 * @h: pointer to node
 * Return: size
 */
size_t p_lst_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * dlt_node_i - delete node
 * @head: head
 * @ii: index
 * Return: 1 on success
 */
int dlt_node_i(list_t **head, unsigned int ii)
{
	list_t *nn, *prev_nn;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ii)
	{
		nn = *head;
		*head = (*head)->next;
		free(nn->str);
		free(nn);
		return (1);
	}
	nn = *head;
	while (nn)
	{
		if (i == ii)
		{
			prev_nn->next = nn->next;
			free(nn->str);
			free(nn);
			return (1);
		}
		i++;
		prev_nn = nn;
		nn = nn->next;
	}
	return (0);
}

/**
 * fff_list - free list
 * @h_ptr: address of pointer to head nn
 *
 * Return: void
 */
void fff_list(list_t **h_ptr)
{
	list_t *nn, *next_nn, *head;

	if (!h_ptr || !*h_ptr)
		return;
	head = *h_ptr;
	nn = head;
	while (nn)
	{
		next_nn = nn->next;
		free(nn->str);
		free(nn);
		nn = next_nn;
	}
	*h_ptr = NULL;
}
