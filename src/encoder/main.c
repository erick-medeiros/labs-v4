/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:41 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/14 19:15:16 by eandre-f         ###   ########.fr       */
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

	*amount_bytes = count_amount_bytes(dictionary, text);
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
	return (compressed);
}

void	fill_frequency_table(t_freq *frequency_table, char *text)
{
	int	i;

	memset(frequency_table, 0, CHARSET_SIZE * sizeof(t_freq));
	i = -1;
	while (text[++i])
		frequency_table[(t_uchar)text[i]]++;
}

void	save_to_shared_memory(t_freq *freq, t_text *text, t_text *encoded)
{
	t_ctrl	*shm_ctrl;
	char	*shm_data;
	char	*shm_freq;

	shm_ctrl = attach_memory_block(SHM_FILENAME, SHM_ID_CTRL, sizeof(t_ctrl));
	shm_data = attach_memory_block(SHM_FILENAME, SHM_ID_DATA, encoded->size);
	shm_freq = attach_memory_block(SHM_FILENAME, SHM_ID_FREQ,
			sizeof(t_freq) * CHARSET_SIZE);
	memset(shm_ctrl, 0, sizeof(t_ctrl));
	shm_ctrl->total_bytes = encoded->size;
	shm_ctrl->total_chars = text->size;
	memcpy(shm_data, encoded->data, encoded->size);
	memcpy(shm_freq, freq, sizeof(t_freq) * CHARSET_SIZE);
	detach_memory_block(shm_ctrl);
	detach_memory_block(shm_freq);
	detach_memory_block(shm_data);
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
	encoded.data = encoder(dictionary, text.data, &encoded.size);
	save_to_shared_memory(frequency_table, &text, &encoded);
	free(text.data);
	free(encoded.data);
	destroy_dictionary(dictionary);
	destroy_tree(huffman_tree);
	return (0);
}
