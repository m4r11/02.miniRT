# *+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
# *|G|e|n|e|r|i|c| |M|a|k|e|f|i|l|e|
# *+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+

EXEC 		= ./minirt
IROOT		= includes
L1			= libs/libft
L2			= libs/libbim
L3			= libs/minilibx_ogl
SROOT		= srcs/engine \
							srcs/interface \
							srcs/render \
							srcs/set
SRC 		:= $(shell find $(SROOT) -name '*.c')
BROOT 		= bin/
OROOT		= obj/
OBJ 		= $(patsubst %.c,%.o,${SRC:%.c})
_DEPS 		= includes/rtlib.h

CC			= gcc
LINKMLX		= -L${L3}/ -lmlx -framework OpenGL -framework AppKit
LINKLIBFT	= -L${L1}/bin -lft
LINKBIM		= -L${L2}/bin -lbim
LINKFLAGS	= ${LINKMLX} ${LINKLIBFT} ${LINKBIM}
CFLAGS		= -g -fsanitize=address -Imlx -Werror -Wall -Wextra 
LIBS		= libft.a libbim.a libmlx.a

# ********************************************************************************
# * for building an executable dependent on many libraries.
# * use config file with caution 
# * Sugestions are welcome, 
# * Enjoy (vendettta Mlib0.0 / Mlib0.0.mk)
# ********************************************************************************