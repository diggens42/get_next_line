/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:36:04 by fwahl             #+#    #+#             */
/*   Updated: 2023/10/24 00:27:15 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*resize_buffer(char *buffer, size_t *buffer_size, size_t *buffer_capacity)
{
	char *new_buffer;

	if (*buffer_size >= *buffer_capacity)
	{
		*buffer_capacity += BUFFER_SIZE;
		new_buffer = malloc(*buffer_capacity + 1);
		if (!new_buffer)
		{
			free(buffer);
			return (NULL);
		}
		ft_strlcpy(new_buffer, buffer, *buffer_size + 1);
		free(buffer);
		buffer = new_buffer;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	size_t	buffer_size;
	size_t	buffer_capacity;
	ssize_t	nbytes;
	char	*buffer;
	char	*line;
	
	buffer_size = 0;
	buffer_capacity = BUFFER_SIZE;
	buffer = malloc(buffer_capacity + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (42)
	{
		buffer = resize_buffer(buffer, &buffer_size, &buffer_capacity);
		if (!buffer)
			return(NULL);
		nbytes = read(fd, buffer + buffer_size, BUFFER_SIZE);
		if (nbytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer_size += nbytes;
		buffer[buffer_size] = '\0';
		if (ft_strchr(buffer, '\n') || nbytes == 0)
			break;
	}
	if (buffer_size == 0)
	{
		free(buffer);
		return (NULL);
	}
	line = get_line(buffer);
	free(buffer);
	return (line);
}

char	*get_line(char *str)
{
	char	*start;
	char	*line;
	char	*line_ptr;

	start = str;
	if (*start == '\0')
		return (NULL);
	while (*start != '\0' && *start != '\n')
		start++;
	line = malloc((sizeof(char)) * (start - str + 2));
	if (line == NULL)
		return (NULL);
	line_ptr = line;
	while (str != start)
		*line_ptr++ = *str++;
	if (*str == '\n')
		*line_ptr++ = *str++;
	return (line);
}

char	*get_remain(char *str)
{
	char	*p;
	char	*remain;
	
	p = str;
	while (*p && *p != '\n')
		p++;
	if (*p == '\0')
	{
		free(str);
		return (NULL);
	}
	p++;
	remain = (char *)malloc(ft_strlen(p) + 1);
	if (!remain)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(remain, p, ft_strlen(p) + 1);
	free(str);
	return (remain);
}

int main(void) {
	int fd = open("dracula.txt", O_RDONLY);
	
	char *line;
	while ((line = get_next_line(fd)) != NULL) {
		printf("%s", line);
		free(line);
	}
	printf("\n");
	
	close(fd);
	system("leaks a.out");
	return 0;
}

// char	*get_next_line(int fd)
// {
// 	char	*buffer;
// 	char	*res;
// 	char	*temp;
// 	ssize_t	nbytes;
	
// 	res = ft_strdup("");
// 	if (!res)
// 		return (NULL);
// 	while((nbytes = read_to_buff(fd, &buffer)) > 0)
// 	{	
// 		temp = ft_strjoin(res, buffer);
// 		if (!temp)
// 		{
// 			free(res);
// 			return (NULL);
// 		}
// 		free(res);
// 		res = temp;
// 		if (ft_strchr(res, '\n') != NULL)
// 			return (res);
// 	}
// 	if (nbytes < 0)
// 	{
// 		free(res);
// 		return (NULL);
// 	}
// 	if (*res == '\0')
// 	{
// 		free(res);
// 		return (NULL);
// 	}
// 	return (res);
// }

// ssize_t	read_to_buff(int fd, char **str_buffer)
// {
// 	static char	*buffer;
// 	ssize_t	nbytes;
	
// 	if (buffer == NULL)
// 		buffer = malloc(2 * (BUFFER_SIZE) * sizeof(char));
// 		if(!buffer)
// 			return (-1);
// 	nbytes = read(fd, buffer, BUFFER_SIZE);
// 	if (nbytes <= 0)
// 	{
// 		free(buffer);
// 		buffer = NULL;
// 		return (nbytes);
// 	}
// 	buffer[nbytes] = '\0';
// 	*str_buffer = buffer;
// 	return (nbytes);
// }



// char	*get_next_line(int fd)
// {
// 	static char	*remain;
// 	char		*newline;
// 	ssize_t		nbytes;
	
// 	if (fd < 0)
// 		return (NULL);
// 	newline = NULL;
// 	if (remain)
// 		newline = ft_strchr(remain, '\n');
// 	while (newline == NULL)
// 	{
// 		nbytes = ft_read(fd, &remain);
// 		if (nbytes <= 0)
// 			break;
// 		if (remain)
// 			newline = ft_strchr(remain, '\n');
// 	}
// 	if (remain)
// 		return (ft_extract_line(&remain));
// 	return (NULL);
// }

// static ssize_t	ft_read(int fd, char **remain)
// {
// 	char	*buffer;
// 	char	*new_remain;
// 	ssize_t	nbytes;

// 	buffer = malloc((BUFFER_SIZE + 1)*(sizeof(char)));
// 	if (!buffer)
// 		return (-1);
// 	nbytes = read(fd, buffer, BUFFER_SIZE);
// 	if (nbytes > 0)
// 	{
// 		buffer[nbytes] = '\0';
// 		new_remain = ft_strjoin(*remain, buffer);
// 		if (*remain)
// 			free(*remain);
// 		*remain = new_remain;
// 	}
// 	free(buffer);
// 	return (nbytes);
// }

// static char	*ft_extract_line(char **remain)
// {
// 	char	*newline;
// 	char	*res;

// 	if (!remain || !*remain)
// 		return (NULL);
// 	newline = ft_strchr(*remain, '\n');
// 	if (newline)
// 		*newline = '\0';
// 	res = ft_strdup(*remain);
// 	if (!res)
// 		return (NULL);
// 	if (newline)
// 	{
// 		char *new_remain = ft_strdup(newline + 1);
// 		if (!new_remain)
// 		{
// 			free(res);
// 			return (NULL);
// 		}
// 		free(*remain);
// 		*remain = new_remain;
// 	}
// 	else
// 	{
// 		free(*remain);
// 		*remain = NULL;
// 	}
// 	return (res);
// }
