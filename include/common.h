/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:50:33 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/14 17:17:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <errno.h>
# include <fcntl.h>
# include <inttypes.h>
# include <locale.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

# define SHM_FILENAME "Makefile"
# define SHM_ID_CTRL 1
# define SHM_ID_DATA 2
# define SHM_ID_FREQ 3
# define CHARSET_SIZE 256

typedef unsigned char	t_uchar;
typedef uint32_t		t_freq;
typedef long			t_msec;

typedef enum e_status
{
	STATUS
}	t_status;

typedef struct s_ctrl
{
	t_status	status;
	uintmax_t	total_bytes;
	uintmax_t	total_chars;
}	t_ctrl;

typedef struct s_node
{
	t_uchar			ch;
	t_freq			freq;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*start;
	int		size;
}	t_list;

typedef struct s_text
{
	char	*data;
	size_t	size;
}	t_text;

void	*attach_memory_block(char *filename, int id, int size);
bool	detach_memory_block(void *block);
bool	destroy_memory_block(char *filename, int id);

t_node	*build_tree(t_freq frequency_table[]);
char	**generate_dictionary(t_node *root);

// destroy

void	destroy_tree(t_node *node);
void	destroy_dictionary(char **dictionary);

// utils

char	*ft_strjoin(char *str1, char *str2);
void	set_bit(char *data, size_t bit, bool value);
bool	get_bit(char *data, size_t bit);
t_msec	timestamp_in_ms(void);

#endif
