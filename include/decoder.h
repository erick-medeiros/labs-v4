/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:50:00 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 15:16:36 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H

# include "common.h"

void	write_in_filename(char *filename, char *data, size_t size);
char	*get_arg_filename(int argc, char *argv[], char *flag);
void	decoder_count(t_node *node, char *encoded, size_t *size, size_t *bit);
void	decoder_ch(t_node *node, char *encoded, t_text *decoded, size_t *bit);
t_node	*mount_huffman_tree(void);

#endif