/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 15:18:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"
#include "debug.h"

char	*decoder(char *encoded, t_info	*shm_info)
{
	t_node	*huffman_tree;
	t_text	decoded;
	size_t	bit;
	size_t	total_bits;
	size_t	size;

	shm_info->decompression_operation_time = timestamp_in_ms();
	total_bits = size_memory_block(SHM_FILENAME, SHM_ID_ENCODED);
	total_bits = (total_bits * 8) - count_bits(encoded[total_bits - 1]) - 8;
	huffman_tree = mount_huffman_tree();
	size = 0;
	bit = 0;
	while (bit < total_bits)
		decoder_count(huffman_tree, encoded, &size, &bit);
	decoded.data = calloc(size + 1, sizeof(char));
	decoded.size = 0;
	bit = 0;
	while (decoded.size < size)
		decoder_ch(huffman_tree, encoded, &decoded, &bit);
	shm_info->decompression_operation_time = timestamp_in_ms()
		- shm_info->decompression_operation_time;
	shm_info->amount_of_total_bytes = decoded.size;
	shm_info->amount_of_compressed_bytes = (total_bits / 8) + 1;
	destroy_tree(huffman_tree);
	return (decoded.data);
}

char	*decoding(char *encoded)
{
	t_info	*shm_info;
	char	*shm_decoded;
	char	*decoded;
	size_t	bytes;

	shm_info = attach_memory_block(SHM_FILENAME, SHM_ID_INFO, sizeof(t_info));
	decoded = decoder(encoded, shm_info);
	bytes = strlen(decoded);
	shm_decoded = attach_memory_block(SHM_FILENAME, SHM_ID_DECODED, bytes);
	memcpy(shm_decoded, decoded, bytes);
	detach_memory_block(shm_info);
	detach_memory_block(shm_decoded);
	return (decoded);
}

int	main(int argc, char *argv[])
{
	char	*decoded;
	int		*shm_status;
	char	*shm_encoded;
	char	*filename_d;
	char	*filename_c;

	setlocale(LC_ALL, "utf8");
	filename_c = get_arg_filename(argc, argv, "-c");
	filename_d = get_arg_filename(argc, argv, "-d");
	shm_status = attach_memory_block(SHM_FILENAME, SHM_ID_STATUS, sizeof(int));
	wait_status(shm_status, ENCODED);
	shm_encoded = attach_memory_block(SHM_FILENAME, SHM_ID_ENCODED, 0);
	if (filename_c)
		write_in_filename(filename_c, shm_encoded,
			size_memory_block(SHM_FILENAME, SHM_ID_ENCODED));
	decoded = decoding(shm_encoded);
	if (filename_d)
		write_in_filename(filename_d, decoded, strlen(decoded));
	free(decoded);
	set_status(shm_status, DECODED);
	detach_memory_block(shm_status);
	detach_memory_block(shm_encoded);
	destroy_memory_block(SHM_FILENAME, SHM_ID_ENCODED);
	return (0);
}
