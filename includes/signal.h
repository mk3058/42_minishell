/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:50:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/31 19:19:49 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>
# include <readline/readline.h>
# include <termios.h>
# include <unistd.h>

# define DFL 0
# define IGN 1

void	set_handler(void (*sint_handler)(int s), void (*squit_handler)(int s));
void	set_signal(int sigint, int sigquit);

void	print_prompt(int sig);
void	print_newline(int sig);
void	quite(int sig);
void	set_echoctl(int mode);

#endif