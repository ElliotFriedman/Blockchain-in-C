#ifndef BLOCK_H
# define BLOCK_H

#include <stdio.h>
#include "libft/libft.h"

typedef struct		s_block
{
	int				index;
	char			*hash;
	char			*prev_hash;
	char			*tx_data;
	struct s_block	*next_block;
	struct s_block	*prev_block;
}					t_block;

#endif
