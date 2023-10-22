/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:36:04 by fwahl             #+#    #+#             */
/*   Updated: 2023/10/22 19:34:53 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	char	*buffer;
	char	*ptr;
	ssize_t	nbytes;
	
	buffer = (char *)malloc((BUFFER_SIZE + 1)*(sizeof(char)));
	if (!buffer)
		return (NULL);
	ptr = buffer;
	while((nbytes = read(fd, ptr, 1) > 0))
	{	
		if (*ptr == '\n')
		{	
			ptr++;
			*ptr = '\0';
			return (buffer);
		}
		ptr++;
	}
	if (nbytes < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (ptr == buffer)
	{
		free(buffer);
		return (NULL);
	}
	*ptr = '\0';
	return (buffer);
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
