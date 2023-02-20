/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prossi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 09:56:49 by prossi            #+#    #+#             */
/*   Updated: 2021/10/21 18:04:38 by prossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	

static char	*ft_read_line(int fd, char *buf, char *mem)
{
	int		read_line;
	char	*temp_mem;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!mem)
			mem = ft_strdup("");
		temp_mem = mem;
		mem = ft_strjoin(temp_mem, buf);
		free(temp_mem);
		temp_mem = NULL;
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (mem);
}

static char	*extract_line(char *line)
{
	size_t	count;
	char	*mem;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	mem = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*mem == '\0')
	{
		free(mem);
		mem = NULL;
	}
	line[count + 1] = '\0';
	return (mem);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*mem;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = ft_read_line(fd, buf, mem);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	mem = extract_line(line);
	return (line);
}
