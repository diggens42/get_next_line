/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:36:04 by fwahl             #+#    #+#             */
/*   Ubuffer[i]dated: 2023/10/27 18:56:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;
	
	if (!buffer)
	{
	buffer = malloc((sizeof(char) * (BUFFER_SIZE + 1)));
		if (!buffer)
			return (NULL);
	}
	buffer = read_to_buff(fd, buffer);
	if (buffer == NULL || (buffer[0] == '\0' && ft_strchr(buffer, '\n') == NULL))
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	next_line = get_line_from_buff(buffer);
	buffer = get_remain(buffer);
	return (next_line);
}

char	*get_line_from_buff(char *buffer)
{
	char	*line;
	int		i;
	int		j;
	
	i = 0;
	while(buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = malloc(sizeof(char)*(i + 2));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		line[i++] = buffer[j++];
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*read_to_buff(int fd, char *buffer)
{
	size_t	nbytes;
	char	*read_string;

	read_string = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_string)
		return(NULL);
	while (1)
	{
		nbytes = read(fd, read_string, BUFFER_SIZE);
		if (nbytes <= 0)
		{
			free(read_string);
			if (nbytes == 0)
				return (buffer);
			return (NULL);
		}
		read_string[nbytes] = '\0';
		buffer = ft_strjoin(buffer, read_string);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free(read_string);
	return (buffer);
}

char	*get_remain(char *buffer)
{
	char	*remain;
	int		i;
	int 	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	remain = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!remain)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		remain[j++] = buffer[i++];
	remain[j] = '\0';
	free(buffer);
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
// 	char	*tembuffer[i];
// 	ssize_t	nbytes;
	
// 	res = ft_strdubuffer[i]("");
// 	if (!res)
// 		return (NULL);
// 	while((nbytes = read_to_buff(fd, &buffer)) > 0)
// 	{	
// 		tembuffer[i] = ft_strjoin(res, buffer);
// 		if (!tembuffer[i])
// 		{
// 			free(res);
// 			return (NULL);
// 		}
// 		free(res);
// 		res = tembuffer[i];
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
// 	res = ft_strdubuffer[i](*remain);
// 	if (!res)
// 		return (NULL);
// 	if (newline)
// 	{
// 		char *new_remain = ft_strdubuffer[i](newline + 1);
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
