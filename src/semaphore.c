/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:15:58 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/13 09:17:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

sem_t	*new_semaphore(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
	{
		dprintf(2, "panic: sem_open failed\n");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

void	destroy_semaphore(const char *name, sem_t *sem)
{
	sem_close(sem);
	sem_unlink(name);
}
