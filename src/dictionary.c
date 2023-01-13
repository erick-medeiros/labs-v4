/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:59:14 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/12 22:21:12 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	fill_dictionary(char **dictionary, t_node *root, char *path)
{
	if (!root->left && !root->right)
		dictionary[root->ch] = path;
	else
	{
		fill_dictionary(dictionary, root->left, ft_strjoin(path, "0"));
		fill_dictionary(dictionary, root->right, ft_strjoin(path, "1"));
		free(path);
	}
}

char	**generate_dictionary(t_node *root)
{
	char	**dictionary;

	dictionary = calloc(sizeof(char *), CHARSET_SIZE);
	fill_dictionary(dictionary, root, strdup(""));
	return (dictionary);
}
