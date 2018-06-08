#include "block.h"

void	free_chain(t_block *chain)
{
	t_block	*tmp;

	while (chain->prev_block != 0)
		chain = chain->prev_block;
	if (!chain->next_block)
	{
		free(chain->hash);
		free(chain->tx_data);
		free(chain);
	}
	while (chain->next_block != 0)
	{
		tmp = chain;
		chain = chain->next_block;
		free(tmp->hash);
		free(tmp->tx_data);
		free(tmp);
	}
}

int	numlen(unsigned long long nbr)
{
	int	i;

	i = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

char	find_char(int nbr)
{
	if (nbr >= 10)
		return (nbr - 10 + 'a');
	else
		return (nbr + '0');
}

char	*itoabase(unsigned long long nbr)
{
	int	nlen;
	char	*newnbr;

	nlen = numlen(nbr) - 1;
	newnbr = ft_memalloc(nlen + 1);
	if (!nbr)
		*newnbr = '0';
	while (nbr)
	{
		newnbr[nlen] = find_char(nbr % 16);
		nbr /= 16;
		nlen--;
	}
	return (newnbr);
}

char	*make_hash(t_block *chain)
{
	unsigned long long	nbr;
	t_block			*tmp;
	int			i;

	if (chain->prev_block)
		tmp = chain->prev_block;
	else
		tmp = 0;
	i = 0;
	nbr = 1;
	while (chain->tx_data[i])
	{
		nbr += nbr + (nbr << 5) + (chain->tx_data[i] * i) + (chain->index *chain->index + 1) + sizeof(tmp);
		i++;
	}
	return (itoabase(nbr));
}

void	make_block(t_block *chain)
{
	char *tmp;

	if (chain->prev_block)
	{
		t_block	*tmp;
		tmp = chain->prev_block;
		chain->prev_hash = tmp->hash;
	}
	tmp = chain->hash = make_hash(chain);
	chain->hash = ft_strjoin("0x", chain->hash);
	free(tmp);
}

void	print_block(t_block *chain)
{
	printf("Block: %d | tx data: %12s | current hash: %15s | previous hash: %s\n", 
		chain->index, chain->tx_data, chain->hash, chain->prev_hash);
}

void	print_chain(t_block *chain)
{
	while (chain->prev_block)
		chain = chain->prev_block;
	while (chain)
	{
		print_block(chain);
		chain = chain->next_block;
	}
}

int	main(void)
{
	t_block	*chain;
	t_block	*tmp;
	int		action;
	int		index;

	//this value will track the current index of the block
	index = 0;
	//allocates & zero's out all values. That way we don't have to
	//set any previous values in the first block
	chain = ft_memalloc(sizeof(t_block));
	//space allocated here is arbitrary
	chain->tx_data = ft_memalloc(12);
	chain->next_block = 0;
	chain->prev_block = 0;
	printf("\nTo enter tx data, type up to 11 characters without spaces or tabs\n\n");
	printf("Space for chain malloc'd. Enter tx data for first block\n");
	while (scanf("%11s", chain->tx_data))
	{
		chain->index = index;
		make_block(chain);
		printf("block %3d has been hashed, previous and next values have been set\n", index);
		printf("Options:\n	1). Create new block\n	2). Print out all the ");
		printf("block's data and exit the program\n	3). Exit program\nPro");
		printf("gram will exit if an invalid number is entered\n");
		action = 0;
		scanf("%d", &action);
		if (action == 1)
		{
			tmp = chain;
			chain->next_block = ft_memalloc(sizeof(t_block));
			printf("New block created, enter tx data\n");
			chain = chain->next_block;
			chain->tx_data = ft_memalloc(12);
			chain->prev_block = tmp;
		}
		else if (action == 2)
		{
			print_chain(chain);
			free_chain(chain);
			break;
		}
		else
		{
			free_chain(chain);
			break;
		}
		index++;
	}
	return (0);
}
