/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:57:38 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/14 18:50:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

#define BUFFER_SIZE 4096

int	copy_file_data_to_file(char *filename, FILE *tmp_out)
{
	int		fd;
	ssize_t	bytes;
	char	buff[BUFFER_SIZE];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		dprintf(2, "open: %s: failed\n", filename);
		return (1);
	}
	while (1)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		fwrite(buff, sizeof(char), bytes, tmp_out);
	}
	close(fd);
	return (0);
}

int	copy_file_data_to_string(char *str, FILE *tmp_out)
{
	char	buff[BUFFER_SIZE];
	ssize_t	bytes;
	size_t	index;

	index = 0;
	while (1)
	{
		bytes = fread(buff, sizeof(char), BUFFER_SIZE, tmp_out);
		if (bytes <= 0)
			break ;
		memcpy(&str[index], buff, bytes);
		index += bytes;
	}
	return (0);
}

long int	get_file_size(FILE *tmp_out)
{
	long int	size;

	fseek(tmp_out, 0L, SEEK_END);
	size = ftell(tmp_out);
	rewind(tmp_out);
	return (size);
}

int	get_text(int argc, char *argv[], t_text *text)
{
	FILE	*tmp_out;
	int		i;

	if (argc <= 1)
		return (1);
	tmp_out = tmpfile();
	if (strcmp(argv[1], "-f") == 0)
	{
		i = 1;
		while (++i < argc)
			if (copy_file_data_to_file(argv[i], tmp_out))
				return (1);
	}
	else
	{
		i = 0;
		while (++i < argc)
			fwrite(argv[i], sizeof(char), strlen(argv[i]), tmp_out);
	}
	text->data = calloc(get_file_size(tmp_out) + 1, sizeof(char));
	text->size = get_file_size(tmp_out);
	copy_file_data_to_string(text->data, tmp_out);
	fclose(tmp_out);
	return (0);
}
