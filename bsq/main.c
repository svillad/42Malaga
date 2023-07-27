#include <stdio.h>
#include "ft_file.h"
#include "ft_utils.h"
#include "ft_get_sizes.h"
#include "ft_line_one.h"
#include "ft_prints.h"
#include "ft_square.h"
#include "ft_map.h"
#include "ft_case_n.h"
#include "ft_case_1.h"

int	main(int n, char **arg)
{
	int	i;
	int	error;

	if (n == 1)
	{
		error = ft_case_1();
		if (error == -1)
			write(1, "error\n", 6);
		else if (error == -2)
			write(1, "map error\n", 10);
	}
	else
	{
		i = 0;
		while (++i < n)
		{
			error = ft_case_n(arg[i]);
			if (error == -1)
				write(1, "error\n", 6);
			else if (error == -2)
				write(1, "map error\n", 10);
		}
	}
	return (0);
}
