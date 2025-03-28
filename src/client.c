/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:22:26 by maballet          #+#    #+#             */
/*   Updated: 2025/03/28 18:46:55 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_signal_received = 0;

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_signal_received = 1;
	if (signum == SIGUSR2)
		ft_printf_fd(1, "Message entirely received by the server 🏝️\n");
}

void	send_char(pid_t pid, unsigned char c)
{
	int	bit_index;
	int	time_out;

	bit_index = 0;
	while (bit_index < 8)
	{
		g_signal_received = 0;
		if ((c &(1 << bit_index)) != 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_signal_received == 0)
		{
			time_out++;
			pause();
		}
		if (time_out >= 100)
		{
			ft_printf_fd(1, "No news from the server 💔\n");
			return ;
		}
		bit_index++;
	}
}

void	send_len(pid_t pid, int len)
{
	int	bit_index;
	int	time_out;

	bit_index = 0;
	while (bit_index < 32)
	{
		g_signal_received = 0;
		if ((len &(1 << bit_index)) != 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_signal_received == 0 && time_out < 100)
		{
			time_out++;
			pause();
		}
		if (time_out >= 100)
		{
			ft_printf_fd(1, "No news from the server 💔\n");
			return ;
		}
		bit_index++;
	}
}

void	send_message(pid_t pid, char *message)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(message);
	send_len(pid, len);
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
}

int	sigaction_init(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	return (0);
}

int	param_check(int argc, char**argv)
{
	int i;

	i = 0;
	if (argc != 3)
	{
		ft_printf_fd(2, "Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_printf_fd(2,"Invalid PID 🛟\n");
			return (1);	
		}
		i++;
	}
	if (argv[2][0] == 0)
	{
		ft_printf_fd(2, "Message missing 🛟\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*message;

	if (param_check(argc, argv) == 1)
		return (1);
	sigaction_init();
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf_fd(2, "Error : Invalid PID\n");
		return (1);
	}
	message = argv[2];
	ft_printf_fd(1, "Sending message to the server 🏄 (PID: %d)...\n", server_pid);
	send_message(server_pid, message);
	return (0);
}
