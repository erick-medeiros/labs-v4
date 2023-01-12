/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:27:56 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/12 18:47:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	debug_frequency_table(t_freq frequency_table[])
{
	int	i;

	i = 0;
	printf("\nfrequency table:\n\n");
	while (i < CHARSET_SIZE)
	{
		if (frequency_table[i] > 0)
			printf("code %d freq %d\n", i, frequency_table[i]);
		++i;
	}
	printf("\n");
}

static void	debug_tree_req(t_node *root, int height)
{
	if (!root)
		return ;
	else if (!root->left && !root->right)
		printf("ch %c freq %d height %d\n", root->ch, root->freq, height);
	else
	{
		debug_tree_req(root->left, height + 1);
		debug_tree_req(root->right, height + 1);
	}
}

void	debug_tree(t_node *root)
{
	printf("\nhuffman tree:\n\n");
	debug_tree_req(root, 0);
	printf("\n");
}
