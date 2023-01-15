/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:18:13 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 11:57:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#define IPC_ERROR -1

static int	get_shared_block(char *filename, int id, int size)
{
	key_t	key;

	key = ftok(filename, id);
	if (key == IPC_ERROR)
		return (IPC_ERROR);
	return (shmget(key, size, 0644 | IPC_CREAT));
}

void	*attach_memory_block(char *filename, int id, int size)
{
	int		shmid;
	void	*memory;

	shmid = get_shared_block(filename, id, size);
	if (shmid == IPC_ERROR)
		return (NULL);
	memory = shmat(shmid, NULL, 0);
	if (memory == (void *)IPC_ERROR)
		return (NULL);
	return (memory);
}

bool	detach_memory_block(void *block)
{
	return (shmdt(block) != IPC_ERROR);
}

bool	destroy_memory_block(char *filename, int id)
{
	int	shmid;

	shmid = get_shared_block(filename, id, 0);
	if (shmid == IPC_ERROR)
		return (false);
	return (shmctl(shmid, IPC_RMID, NULL) != IPC_ERROR);
}

size_t	size_memory_block(char *filename, int id)
{
	struct shmid_ds	buf;
	int				shmid;

	shmid = get_shared_block(filename, id, 0);
	shmctl(shmid, IPC_STAT, &buf);
	return (buf.shm_segsz);
}
