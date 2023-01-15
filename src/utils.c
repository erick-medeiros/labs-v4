/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:53:44 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 13:22:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	mssleep(t_msec ms)
{
	t_msec	start;

	start = timestamp_in_ms();
	while (ms > timestamp_in_ms() - start)
		usleep(100);
	return (0);
}

t_msec	timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	set_bit(char *data, size_t bit, bool value)
{
	data[bit / 8] = data[bit / 8] | (value << (7 - (bit % 8)));
}

bool	get_bit(char *data, size_t bit)
{
	return ((data[bit / 8] >> (7 - (bit % 8))) & 1);
}

int	count_bits(char c)
{
	int	bits;
	int	i;

	bits = 0;
	i = 0;
	while (i < 8)
	{
		bits += get_bit(&c, i);
		++i;
	}
	return (bits);
}
