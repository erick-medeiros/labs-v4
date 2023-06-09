/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:50:29 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 02:37:20 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODER_H
# define ENCODER_H

# include "common.h"

void	fill_frequency_table(t_freq *frequency_table, char *text);
int		get_text(int argc, char *argv[], t_text *text);

#endif
