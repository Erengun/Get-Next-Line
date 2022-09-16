/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egun <egun@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:24:32 by egun              #+#    #+#             */
/*   Updated: 2022/01/30 20:09:17 by egun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_error(int a, char *str, char *buffer)
{
	if (a < 0)
	{
		free (str);
		free (buffer);
		return (0);
	}
	return (1);
}

char	*getstr(int fd, char *str)
{
	int		a;
	char	*buffer;
	char	*s;

	if (!str)
		str = ft_strdup("");
	a = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((a != 0) && !(ft_strchr(str, '\n')))
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == 0)
			break ;
		if (!check_error(a, str, buffer))
			return (NULL);
		buffer[a] = '\0';
		s = ft_strjoin(str, buffer);
		free(str);
		str = s;
	}
	free(buffer);
	return (str);
}

char	*getnewline(char *str)
{
	char	*ptr;
	int		len;

	if (!str)
		return (NULL);
	if (!*str)
		return (NULL);
	ptr = ft_strchr(str, '\n');
	if (!ptr)
		return (ft_strdup(str));
	ptr++;
	if (!*ptr)
		return (ft_strdup(str));
	len = ft_strlen(str) - ft_strlen(ptr);
	return (ft_substr(str, 0, len));
}

char	*getremain(char *str)
{
	char	*ptr;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
	{
		free(str);
		return (NULL);
	}
	ptr++;
	if (!(*ptr))
	{
		free(str);
		return (NULL);
	}
	ptr = ft_strdup(ptr);
	free (str);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	str[fd] = getstr(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = getnewline(str[fd]);
	str[fd] = getremain(str[fd]);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int   main(int argc, char **argv)
{
  int   fd;
  char *c;

  fd = open(argv[1], O_RDWR);
  c = get_next_line(fd);
  while(c)
  {
    printf("%s",c);
    free(c);
    c = get_next_line(fd);
  }
  free(c);
  // For checking leaks
  //system("leaks a.out");
  return (0);
}
