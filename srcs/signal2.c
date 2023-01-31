/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:28:58 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/31 19:32:42 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_echoctl(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (mode)
		term.c_lflag |= (ECHOCTL);
	else
		term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
// 터미널의 시그널 반향 출력을 설정합니다 
// mode = 1일경우 반향이 출력되고 0이면 무시됩니다