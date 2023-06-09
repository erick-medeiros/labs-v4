/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:30:20 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/13 15:32:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "common.h"

void	debug_frequency_table(t_freq frequency_table[]);
void	debug_tree(t_node *root);
void	debug_dictionary(char **dictionary);
void	print_bits(char *bytes, size_t num_bytes);

#endif
