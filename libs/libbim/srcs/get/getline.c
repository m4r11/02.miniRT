/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:33:37 by user              #+#    #+#             */
/*   Updated: 2022/04/20 13:34:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include "bimlib.h"

int has_line(char *str)
{
    int i = 0;
    if(!str)
        return (NO_LINE);
    while(str[i])
    {
        if (str[i] == '\n')
            return (i);
        i++;
    }
    return (NO_LINE);
}

char *make_line(char *archive)
{
    int i = 0;
    char *line;
    int line_size = has_line(archive) + 1;
      
    line = malloc(line_size + 1);

    while (line_size)
    {
        line[i] = archive[i];
        i++;
        line_size--;
    }
    line[i] = 0;
    return (line);
}

char *make_less(char *archive, int new_start)
{
    int i = 0;
    int arch_size = ft_strlen(archive);

    if(new_start == arch_size)
    {
        free(archive);
        archive = NULL;
        return(NULL);
    }

    char *new = malloc(arch_size - new_start + 1);

    while (archive[new_start])
    {
        new[i] = archive[new_start];
        i++;
        new_start++;
    }
    new[i] = 0;
    free(archive);
    return (new);
}

char *ft_join(char *buf, char *archive)
{
    int i = 0;
    int k = 0;
    int size_arch =ft_strlen(archive);
    int size_buf = ft_strlen(buf);

    char *new = malloc(size_buf + size_arch + 1);
    
    while(archive[i])
    {
        new[i] = archive[i];
        i++;
    }
    while(buf[k])
    {
        new[i] = buf[k];
        i++;
        k++;
    }
    
    new[i] = 0;
    return (new);
}

char *get_next_line(int fd)
{
    char *line;
    static char *archive;

    char buf[BUFFER_SIZE + 1] = "";
    int r;
    if (!archive)
    {
        archive = malloc(0);
        archive = "";
    }
    if (archive)
    {
        if(has_line(archive) != NO_LINE)
        {
            line = make_line(archive);
            archive = make_less(archive, ft_strlen(line));
            return (line);
        }
    }
    while ((r = read(fd, buf, BUFFER_SIZE)))
    {
        archive = ft_join(buf, archive);
        if (has_line(buf) != NO_LINE)
        {
            line = make_line(archive);
            archive = make_less(archive, ft_strlen(line));
            return (line);
        }
    }
    return(NULL);
}