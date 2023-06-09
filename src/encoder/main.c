/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:41 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 14:00:20 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"
#include "debug.h"

size_t	count_amount_bytes(char **dictionary, char *text)
{
	size_t	amount_bits;
	int		i;

	amount_bits = 0;
	i = -1;
	while (text[++i])
		amount_bits += strlen(dictionary[(t_uchar)text[i]]);
	return ((amount_bits / 8) + 1);
}

void	*encoder(char **dictionary, char *text, size_t *amount_bytes)
{
	char	*compressed;
	char	*code;
	int		i;
	int		j;
	size_t	bit;

	*amount_bytes = count_amount_bytes(dictionary, text) + 1;
	compressed = calloc(*amount_bytes, 1);
	bit = 0;
	i = -1;
	while (text[++i])
	{
		code = dictionary[(t_uchar)text[i]];
		j = -1;
		while (code[++j])
		{
			if (code[j] == '1')
				set_bit(compressed, bit, 1);
			else
				set_bit(compressed, bit, 0);
			++bit;
		}
	}
	compressed[*amount_bytes - 1] = 0B11111111 >> bit % 8;
	return (compressed);
}

void	save_to_shared_memory(t_freq *freq, t_text *encoded)
{
	int		*shm_status;
	char	*shm_data;
	char	*shm_freq;

	shm_status = attach_memory_block(SHM_FILENAME, SHM_ID_STATUS, sizeof(int));
	shm_data = attach_memory_block(SHM_FILENAME, SHM_ID_ENCODED, encoded->size);
	shm_freq = attach_memory_block(SHM_FILENAME, SHM_ID_FREQ,
			sizeof(t_freq) * CHARSET_SIZE);
	memcpy(shm_data, encoded->data, encoded->size);
	memcpy(shm_freq, freq, sizeof(t_freq) * CHARSET_SIZE);
	detach_memory_block(shm_status);
	detach_memory_block(shm_freq);
	detach_memory_block(shm_data);
}

void	show_information(void)
{
	t_info	*shm_info;
	char	*shm_decoded;
	int		*shm_status;

	shm_status = attach_memory_block(SHM_FILENAME, SHM_ID_STATUS, sizeof(int));
	set_status(shm_status, ENCODED);
	wait_status(shm_status, DECODED);
	shm_info = attach_memory_block(SHM_FILENAME, SHM_ID_INFO, sizeof(t_info));
	shm_decoded = attach_memory_block(SHM_FILENAME, SHM_ID_DECODED, 0);
	printf("uncompressed data:\n%s\n", shm_decoded);
	printf("amount of total bytes: %lu\n", shm_info->amount_of_total_bytes);
	printf("amount of compressed bytes: %lu\n",
		shm_info->amount_of_compressed_bytes);
	printf("decompression operation time: %lu milliseconds\n",
		shm_info->decompression_operation_time);
	detach_memory_block(shm_info);
	detach_memory_block(shm_decoded);
	detach_memory_block(shm_status);
	destroy_memory_block(SHM_FILENAME, SHM_ID_INFO);
	destroy_memory_block(SHM_FILENAME, SHM_ID_DECODED);
	destroy_memory_block(SHM_FILENAME, SHM_ID_STATUS);
	unlink(SEM_NAME);
}

int	main(int argc, char *argv[])
{
	t_freq	frequency_table[CHARSET_SIZE];
	t_node	*huffman_tree;
	char	**dictionary;
	t_text	text;
	t_text	encoded;

	setlocale(LC_ALL, "utf8");
	if (get_text(argc, argv, &text))
		return (EXIT_FAILURE);
	fill_frequency_table(frequency_table, text.data);
	huffman_tree = build_tree(frequency_table);
	dictionary = generate_dictionary(huffman_tree);
	destroy_tree(huffman_tree);
	encoded.data = encoder(dictionary, text.data, &encoded.size);
	destroy_dictionary(dictionary);
	save_to_shared_memory(frequency_table, &encoded);
	free(text.data);
	free(encoded.data);
	show_information();
	return (0);
}
