/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:20:21 by mvaldeta          #+#    #+#             */
/*   Updated: 2022/04/20 13:33:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bimlib.h"

char *parse_input(int fd)
{
	char *data = NULL;
	data = get_next_line(fd);
	return(data);
}

char *save_raw(char *input)
{
	char *raw;
	int i = 0;
	raw = malloc(ft_strlen(input) + 1);
	while(input[i])
	{
		raw[i] = input[i];
		i++;
	}
	raw[i] = 0;
	return(raw);
}