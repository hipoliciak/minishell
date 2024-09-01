/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:21:53 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/01 21:24:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_blocked(int sig_num)
{
	(void)sig_num;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_signal_handlers(int interactive)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (interactive)
	{
		act.sa_handler = &sigint_handler;
		sigaction(SIGINT, &act, NULL);
		act.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &act, NULL);
	}
	else
	{
		act.sa_handler = SIG_IGN;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
}

void	reset_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sigint_handler_blocked;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
