/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:15:58 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 13:55:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static sem_t	*new_semaphore(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
	{
		dprintf(2, "panic: sem_open failed\n");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

int	wait_status(int *status, int expected)
{
	sem_t	*sem;
	int		value;

	sem = new_semaphore(SEM_NAME, 1);
	value = 0;
	while (1)
	{
		sem_wait(sem);
		value = *status;
		sem_post(sem);
		if (value == expected)
		{
			sem_close(sem);
			return (value);
		}
		mssleep(10);
	}
}

void	set_status(int *status, int value)
{
	sem_t	*sem;

	sem = new_semaphore(SEM_NAME, 1);
	sem_wait(sem);
	*status = value;
	sem_post(sem);
	sem_close(sem);
}
