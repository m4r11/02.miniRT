#include "bimlib.h"

/* filetype_is_valid */
int filetype_is_valid(char *arg, char *file_type)
{
    int file;
    file = ft_strlen(arg);
    if(arg[file - 1] == file_type[2] && arg[file - 2] == file_type[1] &&  arg[file - 3] == file_type[0])
        return(1);
    else
        return(0);
}
