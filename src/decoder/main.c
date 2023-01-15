/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 02:40:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"
#include "debug.h"

void	decoder_ch(t_node *node, char *encoded, t_text *decoded, size_t *bit)
{
	if (!node->left && !node->right)
		decoded->data[decoded->size++] = node->ch;
	else
	{
		if (get_bit(encoded, (*bit)++))
			decoder_ch(node->right, encoded, decoded, bit);
		else
			decoder_ch(node->left, encoded, decoded, bit);
	}
}

char	*decoder(void *encoded, size_t size, t_msec *timestamp)
{
	t_node	*huffman_tree;
	t_freq	*shm_freq;
	t_text	decoded;
	size_t	bit;

	shm_freq = attach_memory_block(SHM_FILENAME, SHM_ID_FREQ,
			sizeof(t_freq) * CHARSET_SIZE);
	huffman_tree = build_tree(shm_freq);
	decoded.data = calloc(size + 1, sizeof(char));
	decoded.size = 0;
	bit = 0;
	*timestamp = timestamp_in_ms();
	while (decoded.size != size)
		decoder_ch(huffman_tree, encoded, &decoded, &bit);
	*timestamp = timestamp_in_ms() - *timestamp;
	destroy_tree(huffman_tree);
	detach_memory_block(shm_freq);
	destroy_memory_block(SHM_FILENAME, SHM_ID_FREQ);
	return (decoded.data);
}

void	decoding(t_ctrl	*shm_ctrl)
{
	char	*shm_data;
	t_info	*shm_info;
	char	*shm_deco;
	char	*decoded;
	t_msec	timestamp;

	shm_ctrl = attach_memory_block(SHM_FILENAME, SHM_ID_CTRL, sizeof(t_ctrl));
	shm_data = attach_memory_block(SHM_FILENAME, SHM_ID_DATA,
			shm_ctrl->total_bytes);
	decoded = decoder(shm_data, shm_ctrl->total_chars, &timestamp);
	shm_ctrl->total_chars = strlen(decoded);
	shm_info = attach_memory_block(SHM_FILENAME, SHM_ID_INFO, sizeof(t_info));
	shm_deco = attach_memory_block(SHM_FILENAME, SHM_ID_DECO,
			shm_ctrl->total_chars);
	memcpy(shm_deco, decoded, shm_ctrl->total_chars);
	free(decoded);
	shm_info->amount_of_total_bytes = shm_ctrl->total_chars;
	shm_info->amount_of_compressed_bytes = shm_ctrl->total_bytes;
	shm_info->decompression_operation_time = timestamp;
	detach_memory_block(shm_data);
	detach_memory_block(shm_info);
	detach_memory_block(shm_deco);
	destroy_memory_block(SHM_FILENAME, SHM_ID_DATA);
}

int	main(void)
{
	sem_t	*sem;
	t_ctrl	*shm_ctrl;

	setlocale(LC_ALL, "utf8");
	shm_ctrl = attach_memory_block(SHM_FILENAME, SHM_ID_CTRL, sizeof(t_ctrl));
	sem = new_semaphore(SEM_NAME, 1);
	wait_ctrl_status(shm_ctrl, sem, 1);
	decoding(shm_ctrl);
	set_ctrl_status(shm_ctrl, sem, 2);
	detach_memory_block(shm_ctrl);
	sem_close(sem);
	return (0);
}
