/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frequency.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:35:57 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 02:36:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	fill_frequency_table(t_freq *frequency_table, char *text)
{
	int	i;

	memset(frequency_table, 0, CHARSET_SIZE * sizeof(t_freq));
	i = -1;
	while (text[++i])
		frequency_table[(t_uchar)text[i]]++;
}
