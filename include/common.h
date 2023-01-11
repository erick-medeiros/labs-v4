/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:50:33 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/11 16:07:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <errno.h>
# include <inttypes.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/shm.h>

# define SHM_BLOCK_SIZE 4096
# define SHM_FILENAME "Makefile"
# define SHM_ID_CONTROL 1
# define SHM_ID_DATA 2

typedef enum e_status
{
	STATUS
}	t_status;

typedef struct s_control
{
	t_status	status;
	uintmax_t	total_bytes;
}	t_control;

void	*attach_memory_block(char *filename, int id, int size);
bool	detach_memory_block(void *block);
bool	destroy_memory_block(char *filename, int id);

#endif