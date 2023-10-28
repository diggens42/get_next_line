/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:36:04 by fwahl             #+#    #+#             */
/*   Updated: 2023/10/28 20:54:10 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc((sizeof(char) * (BUFFER_SIZE + 1)));
		if (!buffer)
			return (NULL);
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	}
	buffer = read_to_buff(fd, buffer);
	if (buffer == NULL || (buffer[0] == '\0'))
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
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
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (i > j++)
		line[j - 1] = buffer[j - 1];
	line[i] = '\0';
	return (line);
}

char	*read_to_buff(int fd, char *buffer)
{
	size_t	nbytes;
	char	read_string[BUFFER_SIZE + 1];
	char	*temp;

	if (read(fd, NULL, 0) == -1)
	{
		free(buffer);
		return (NULL);
	}
	while (1)
	{
		nbytes = read(fd, read_string, BUFFER_SIZE);
		if (nbytes == 0)
			return (buffer);
		if (nbytes <= BUFFER_SIZE)
			read_string[nbytes] = '\0';
		temp = ft_strjoin(buffer, read_string);
		if (temp == NULL)
			return (NULL);
		free(buffer);
		buffer = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_remain(char *buffer)
{
	char	*remain;
	int		i;
	int		j;

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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*conv_str;
	unsigned char	conv_c;
	size_t			i;

	conv_str = (unsigned char *)b;
	conv_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		conv_str[i] = conv_c;
		i++;
	}
	return (b);
}

// int main(void) {
// 	int fd = open("dracula.txt", O_RDONLY);
// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL) {
// 		printf("%s", line);
// 		free(line);
// 	}
// 	printf("\n");
// 	close(fd);
// 	system("leaks a.out");
// 	return 0;
// }