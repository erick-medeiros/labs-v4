/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:48:58 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/12 18:50:47 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_node	*create_node(t_uchar ch, t_freq freq)
{
	t_node	*node;

	node = calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->ch = ch;
	node->freq = freq;
	return (node);
}

void	insert_sorted(t_list *list, t_node *node)
{
	t_node	*temp;

	if (list->start == NULL)
		list->start = node;
	else if (node->freq < list->start->freq)
	{
		node->next = list->start;
		list->start = node;
	}
	else
	{
		temp = list->start;
		while (temp->next && temp->next->freq <= node->freq)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
	list->size++;
}

t_node	*remove_start(t_list *list)
{
	t_node	*node;

	node = NULL;
	if (list->size > 0)
	{
		node = list->start;
		list->start = node->next;
		list->size--;
		node->next = NULL;
	}
	return (node);
}

void	build_list(t_list *list, t_freq frequency_table[])
{
	t_uchar	ch;

	list->start = NULL;
	list->size = 0;
	ch = 0;
	while (ch < CHARSET_SIZE - 1)
	{
		if (frequency_table[ch] > 0)
			insert_sorted(list, create_node(ch, frequency_table[ch]));
		++ch;
	}
}

t_node	*build_tree(t_freq frequency_table[])
{
	t_list	list;
	t_node	*node;

	build_list(&list, frequency_table);
	while (list.size > 1)
	{
		node = create_node(0, 0);
		node->left = remove_start(&list);
		node->right = remove_start(&list);
		node->freq = node->left->freq + node->right->freq;
		insert_sorted(&list, node);
	}
	return (remove_start(&list));
}
