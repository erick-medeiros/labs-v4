/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:59:14 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 12:26:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*ft_strjoin(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	char	*ret;

	len1 = strlen(str1);
	len2 = strlen(str2);
	ret = calloc(len1 + len2 + 1, sizeof(char));
	strcpy(ret, str1);
	strcpy(&ret[len1], str2);
	return (ret);
}

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
