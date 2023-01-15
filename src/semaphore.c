/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:15:58 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 00:52:16 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

sem_t	*new_semaphore(const char *name, unsigned int value)
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

void	destroy_semaphore(const char *name, sem_t *sem)
{
	sem_close(sem);
	sem_unlink(name);
}

int	wait_ctrl_status(t_ctrl *ctrl, sem_t *sem, int wait_status)
{
	int	status;

	status = 0;
	while (1)
	{
		sem_wait(sem);
		status = ctrl->status;
		sem_post(sem);
		if (status == wait_status)
			return (status);
		mssleep(10);
	}
}

void	set_ctrl_status(t_ctrl *ctrl, sem_t *sem, int status)
{
	sem_wait(sem);
	ctrl->status = status;
	sem_post(sem);
}
