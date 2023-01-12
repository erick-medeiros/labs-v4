/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:41 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/12 12:51:53 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

int	main(void)
{
	char	*memory;

	setlocale(LC_ALL, "utf8");
	printf("%s\n", "encoder");
	memory = attach_memory_block(SHM_FILENAME, 1, SHM_BLOCK_SIZE);
	if (!memory)
		return (1);
	strncpy(memory, "erick", SHM_BLOCK_SIZE);
	detach_memory_block(memory);
	memory = attach_memory_block(SHM_FILENAME, 2, SHM_BLOCK_SIZE);
	strncpy(memory, "medeiros", SHM_BLOCK_SIZE);
	detach_memory_block(memory);
	return (0);
}
