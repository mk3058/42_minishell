/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:57:17 by bojung            #+#    #+#             */
/*   Updated: 2023/01/26 11:57:18 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_error(char **token)
{
	if (is_cmd(*token, 0) == PIPE)
		return (print_err("parse error near command"));
	while (*token)
	{
		if (is_cmd(*token, 0) == REDIR || is_cmd(*token, 0) == DOUBLED_REDIR)
		{
			if (*(token + 1) == NULL || is_cmd(*(token + 1), 0) > 2)
				return (print_err("parse error near command"));
		}
		if (is_cmd(*token, 0) == PIPE && is_cmd(*(token + 1), 0) == PIPE)
			return (print_err("parse error near pipe"));
		if (is_in_quote(*token, ft_strlen(*token)))
			return (print_err("parse error near quote"));
		if (err_special_char(*token) == -1)
			return (print_err("parse error"));
		token++;
	}
	return (0);
}

int	err_special_char(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!is_in_quote(token, i) && (token[i] == '\\' || token[i] == ';'))
			return (-1);
		i++;
	}
	return (0);
}

int	print_err(char *str)
{
	printf("minishell: %s\n", str);
	return (-1);
}
