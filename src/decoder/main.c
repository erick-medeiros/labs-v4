/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/14 09:47:03 by eandre-f         ###   ########.fr       */
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

char	*decoder(t_node *root, void *encoded, size_t size)
{
	t_text	decoded;
	size_t	bit;

	decoded.data = calloc(size + 1, sizeof(char));
	decoded.size = 0;
	bit = 0;
	while (decoded.size != size)
		decoder_ch(root, encoded, &decoded, &bit);
	return (decoded.data);
}

int	main(void)
{
	t_ctrl	*shm_ctrl;
	char	*shm_data;
	char	*shm_freq;
	t_node	*huffman_tree;
	char	*decoded;

	setlocale(LC_ALL, "utf8");
	shm_ctrl = attach_memory_block(SHM_FILENAME, SHM_ID_CTRL, sizeof(t_ctrl));
	shm_data = attach_memory_block(SHM_FILENAME, SHM_ID_DATA,
			shm_ctrl->total_bytes);
	shm_freq = attach_memory_block(SHM_FILENAME, SHM_ID_FREQ,
			sizeof(t_freq) * CHARSET_SIZE);
	huffman_tree = build_tree((t_freq *)shm_freq);
	decoded = decoder(huffman_tree, shm_data, shm_ctrl->total_chars);
	printf("%s\n", decoded);
	detach_memory_block(shm_ctrl);
	detach_memory_block(shm_freq);
	detach_memory_block(shm_data);
	destroy_memory_block(SHM_FILENAME, SHM_ID_CTRL);
	destroy_memory_block(SHM_FILENAME, SHM_ID_FREQ);
	destroy_memory_block(SHM_FILENAME, SHM_ID_DATA);
	return (0);
}
