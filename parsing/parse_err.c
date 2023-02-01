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

/*
 * Error 처리 함수
 * main function : check_error(char **token)
 * @when	:1. Check sequence commands and no parameter case
			 2. Check unspecified special characters like \ or ;
			 3. Check quote error case
			 3. Check smth occurs errors
 * @return	: Error(-1), Pass(0)
*/
int	check_error(char **token)
{
	if (ft_strncmp(*token, "|", 1) == 0)
		return (print_err("parse error near command"));
	while (*token)
	{
		if (is_cmd(*token, 0))
		{
			if (is_cmd(*(token + 1), 0) || *(token + 1) == NULL)
				return (print_err("parse error near command"));
		}
		if (is_in_quote(*token, ft_strlen(*token)))
			return (print_err("parse error near quote"));
		if (err_special_char(*token) == -1)
			return (print_err("parse error"));
		
		token++;
	}
	return (0);
}

// check special character case
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
