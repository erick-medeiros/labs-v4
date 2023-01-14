/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:53:44 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/13 23:06:53 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

char	*ft_strjoin(char *str1, char *str2)
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

void	set_bit(char *data, size_t bit, bool value)
{
	data[bit / 8] = data[bit / 8] | (value << (7 - (bit % 8)));
}

bool	get_bit(char *data, size_t bit)
{
	return ((data[bit / 8] >> (7 - (bit % 8))) & 1);
}
