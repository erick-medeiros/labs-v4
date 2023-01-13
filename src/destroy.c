/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:21:57 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/12 22:29:12 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	destroy_tree(t_node *node)
{
	if (!node)
		return ;
	destroy_tree(node->left);
	destroy_tree(node->right);
	free(node);
}

void	destroy_dictionary(char **dictionary)
{
	int	i;

	i = 0;
	while (i < CHARSET_SIZE)
		free(dictionary[i++]);
	free(dictionary);
}
