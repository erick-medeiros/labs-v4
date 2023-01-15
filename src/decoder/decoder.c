/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:15:19 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 15:15:47 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void	decoder_count(t_node *node, char *encoded, size_t *size, size_t *bit)
{
	if (!node->left && !node->right)
		(*size)++;
	else
	{
		if (get_bit(encoded, (*bit)++))
			decoder_count(node->right, encoded, size, bit);
		else
			decoder_count(node->left, encoded, size, bit);
	}
}

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

t_node	*mount_huffman_tree(void)
{
	t_node	*huffman_tree;
	t_freq	*shm_freq;

	shm_freq = attach_memory_block(SHM_FILENAME, SHM_ID_FREQ,
			sizeof(t_freq) * CHARSET_SIZE);
	huffman_tree = build_tree(shm_freq);
	detach_memory_block(shm_freq);
	destroy_memory_block(SHM_FILENAME, SHM_ID_FREQ);
	return (huffman_tree);
}
