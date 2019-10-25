/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 18:00:40 by ykopiika          #+#    #+#             */
/*   Updated: 2019/10/14 18:29:34 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_read	*malloc_lst(t_read *read, char *str)
{
	if (!read)
	{
		if (!(read = (t_read *)malloc(sizeof(t_read))))
			print_error(ERR_MALLOC, -1);
		read->line = ft_strdup(str);
		read->row = 0;
		read->len = ft_strlen(str);
		read->next = NULL;
		read->prev = NULL;
		return (read);
	}
	else
	{
		read->next = (t_read *)malloc(sizeof(t_read));
		if (!read->next)
			print_error(ERR_MALLOC, -1);
		read->next->line = ft_strdup(str);
		read->next->row = read->row + 1;
		read->next->len = ft_strlen(str);
		read->next->next = NULL;
		read->next->prev = read;
		return (read->next);
	}
}

static int		check_dot(char *str, int i)
{
	if (i == 0)
		return (0);
	if (ft_isdigit(str[i - 1]) && ft_isdigit(str[i + 1]))
		return (1);
	return (0);
}

static void		check_line(char *line, int len, int row)
{
	int i;
	int pipe;

	i = 0;
	pipe = 0;
	while (i < len && line[i] != COMNT)
	{
		if (!ft_isdigit(line[i]) && !ft_isalpha(line[i])
			&& line[i] != ' ' && line[i] != '|'
			&& line[i] != '-' && line[i] != '.')
			print_error(ERR_WRONG_SYMBOL, row);
		if (line[i] == '|')
			pipe++;
		if (line[i] == '.' && !(check_dot(line, i)))
			print_error(ERR_DOT, row);
		if (line[i] == '-' && !(ft_isdigit(line[i + 1])))
			print_error(ERR_MINUS, row);
		i++;
	}
	if (pipe > PIPE_NBR)
		print_error(ERR_PIPE, row);
}

void			validation_file(t_data *data, int fd)
{
	int		gnl;
	char	*string;

	gnl = 0;
	string = NULL;
	data->read = NULL;
	while ((gnl = get_next_line2(fd, &string)) == 1)
	{
		data->read = malloc_lst(data->read, string);
		if (data->read->len > MAX_LEN)
			print_error(ERR_LEN, data->read->row);
		check_line(data->read->line, data->read->len, data->read->row);
		ft_strdel(&string);
	}
	if ((data->read == NULL) || gnl == -1)
		print_error(ERR_ARGV, -1);
	if (data->read->row > MAX_ROWS)
		print_error(ERR_ROWS, -1);
	while (data->read->prev != NULL)
		data->read = data->read->prev;
}
