/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/11 16:09:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

int	main(void)
{
	char	*memory;

	printf("decoder\n");
	memory = attach_memory_block(SHM_FILENAME, 1, SHM_BLOCK_SIZE);
	printf("%s\n", memory);
	detach_memory_block(memory);
	memory = attach_memory_block(SHM_FILENAME, 2, SHM_BLOCK_SIZE);
	printf("%s\n", memory);
	detach_memory_block(memory);
	destroy_memory_block(SHM_FILENAME, 1);
	destroy_memory_block(SHM_FILENAME, 2);
	return (0);
}
