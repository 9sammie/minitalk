/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:54:06 by maballet          #+#    #+#             */
/*   Updated: 2025/03/31 22:47:54 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	

void	signal_server_handler(int signum, siginfo_t *info, void *context)
{
	static int		len = 0;
	static char		*str = NULL;
	static int		receiving_len = 1;
	int				client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (receiving_len == 1)
	{
		usleep(500);
		if (len != 0)
			get_strlen(0, 0);
		len = get_strlen(client_pid, signum);
		str = str_alloc(len, &receiving_len, str);
		return ;
	}
	str = store_str(client_pid, str, signum);
	print_str(len, &str, &receiving_len);
	if (receiving_len == 1)
	{
		usleep(500);
		kill(client_pid, SIGUSR2);
		len = 0;
	}
}

int	sigaction_server_init(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = signal_server_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf_fd(2, "Error: Failed to set up SIGUSR1\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf_fd(2, "Error: Failed to set up SIGUSR2\n");
		return (1);
	}
	return (0);
}
