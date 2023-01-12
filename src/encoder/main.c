/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:19:41 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/12 18:57:03 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"
#include "debug.h"

int	main(int argc, char *argv[])
{
	t_freq	frequency_table[CHARSET_SIZE];
	t_node	*huffman_tree;
	int		i;

	if (argc <= 1)
		return (1);
	setlocale(LC_ALL, "utf8");
	memset(frequency_table, 0, CHARSET_SIZE * sizeof(t_freq));
	i = -1;
	while (argv[1][++i])
		frequency_table[(t_uchar)argv[1][i]]++;
	debug_frequency_table(frequency_table);
	huffman_tree = build_tree(frequency_table);
	debug_tree(huffman_tree);
	return (0);
}
