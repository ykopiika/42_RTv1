/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 14:44:46 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/08 16:07:49 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	print_error_part3(int err_nb)
{
	if (err_nb == ERR_MINUS)
	{
		ft_putendl("Wrong  symbol's '-' position");
		exit(err_nb);
	}
	else if (err_nb == ERR_LEN)
	{
		ft_putendl("String contains more than 200 characters");
		exit(err_nb);
	}
	else if (err_nb == ERR_ROWS)
	{
		ft_putendl("Too many rows in the file");
		exit(err_nb);
	}
	else if (err_nb == ERR_NBR)
	{
		ft_putendl("Wrong number of numbers");
		exit(err_nb);
	}
}

static void	print_error_part2(int err_nb)
{
	if (err_nb == ERR_LINE)
	{
		ft_putendl("Missed some parameters");
		exit(err_nb);
	}
	else if (err_nb == ERR_ARGV)
	{
		ft_putendl("Invalid argument or empty scenne");
		exit(err_nb);
	}
	else if (err_nb == ERR_PIPE)
	{
		ft_putendl("Too many '|' in line");
		exit(err_nb);
	}
	else if (err_nb == ERR_DOT)
	{
		ft_putendl("No number around '.' or too many '.' in the number");
		exit(err_nb);
	}
	print_error_part3(err_nb);
}

void		print_error(int err_nb, int row)
{
	if (row >= 0)
	{
		ft_putstr("Line ");
		ft_putnbr(row + 1);
		ft_putstr(": ");
	}
	if (err_nb == ERR_MALLOC)
		ft_putendl("Malloc failed");
	else if (err_nb == ERR_SDL)
	{
		ft_putendl("SDL failed:");
		ft_putendl(SDL_GetError());
	}
	else if (err_nb == ERR_USAGE)
	{
		ft_putendl("Usage : ./RTv1 <the scenne>");
		exit(err_nb);
	}
	else if (err_nb == ERR_WRONG_SYMBOL)
	{
		ft_putendl("Detected invalid symbol");
		exit(err_nb);
	}
	print_error_part2(err_nb);
}
