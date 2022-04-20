/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bimlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <mvaldeta@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:26:06 by user              #+#    #+#             */
/*   Updated: 2022/04/20 13:26:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*   Welcome to a naive Basic Input Management Library (.c)
*   BIM for short, 
*   and libbim for standards.
*  ____ ____ ____ 
* ||B |||I |||M ||
* ||__|||__|||__||
* |/__\|/__\|/__\|
*     ____ ____ ____ ____ _________ ____ 
*    ||P |||a |||r |||t |||       |||I ||
*    ||__|||__|||__|||__|||_______|||__||
*    |/__\|/__\|/__\|/__\|/_______\|/__\|
*
* checks on validity of the input
*   FILE TYPE
*   ~ filetype_is_valid(char *arg, char *file_type);
*       file extension three chars passed as string
*/


#ifndef BIMLIB_H
# define BIMLIB_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"

int filetype_is_valid(char *arg, char *file_type);

/* 
** input parse 
*/

char *parse_input(int fd);
char *save_raw(char *input);


/* 
** input convertions
*/

int ascii_to_int(char *data);
float ascii_to_float(char *data);
unsigned int ascii_to_hex(int r, int g, int b);

#endif