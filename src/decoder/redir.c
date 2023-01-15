/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:51:04 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/15 14:52:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	write_in_filename(char *filename, char *data, size_t size)
{
	int	fd;

	if (!filename)
		return ;
	fd = open(filename, O_RDWR | O_CREAT, 0644);
	if (fd > 0)
	{
		write(fd, data, size);
		close(fd);
	}
}

char	*get_arg_filename(int argc, char *argv[], char *flag)
{
	char	*filename;

	filename = NULL;
	if (argc == 3 && strcmp(argv[1], flag) == 0)
		filename = argv[2];
	else if (argc == 5 && strcmp(argv[3], flag) == 0)
		filename = argv[4];
	return (filename);
}
