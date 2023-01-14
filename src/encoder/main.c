/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:41 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/13 23:52:17 by eandre-f         ###   ########.fr       */
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

	i = -1;
	while (text[++i])
		frequency_table[(t_uchar)text[i]]++;
}

int	main(int argc, char *argv[])
{
	t_freq	frequency_table[CHARSET_SIZE];
	t_node	*huffman_tree;
	char	**dictionary;
	char	*text;
	char	*text_encoded;
	size_t	amount_bytes;

	if (argc <= 1)
		return (1);
	setlocale(LC_ALL, "utf8");
	memset(frequency_table, 0, CHARSET_SIZE * sizeof(t_freq));
	text = argv[1];
	fill_frequency_table(frequency_table, text);
	huffman_tree = build_tree(frequency_table);
	dictionary = generate_dictionary(huffman_tree);
	text_encoded = encoder(dictionary, text, &amount_bytes);
	print_bits(text_encoded, amount_bytes);
	free(text_encoded);
	destroy_dictionary(dictionary);
	destroy_tree(huffman_tree);
	return (0);
}
