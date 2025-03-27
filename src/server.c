/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:40:48 by maballet          #+#    #+#             */
/*   Updated: 2025/03/27 11:20:14 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	str_index = 0;

int	get_strlen(int signum, siginfo_t *info, void *context)
{
    static int		bit_count = 0;
    static pid_t	client_pid = 0;
	static int		len;

    (void)context;
	if (bit_count == 0)
	{
		len = 0;
		client_pid = 0;
	}
    if (!client_pid)
        client_pid = info->si_pid;
    if (signum == SIGUSR2)
        len |= (1 << bit_count);
    kill(client_pid, SIGUSR1);
    bit_count++;
    if (bit_count == 32)
    {
		ft_printf_fd(1, "len %d\n", len);
        bit_count = 0;
        return (len);
    }
	return (0);
}

char	*store_str(char *str, int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (str_index == 0 && bit_count == 0)
		client_pid = 0;
	if (!client_pid)
		client_pid = info->si_pid;
	if (bit_count == 0)
		c = 0;
	if (signum == SIGUSR2)
		c |= (1 << bit_count);
	kill(client_pid, SIGUSR1);
	bit_count++;
	if (bit_count == 8)
	{
		str[str_index++] = c;
		c = 0;
		bit_count = 0;
	}
	return (str);
}

void	print_str(int len, char **str)
{
	static int	received_bits = 0;

	received_bits++;
	if (received_bits == len * 8)
	{
		ft_printf_fd(1, "%s\n", str);
		free(str);
		str = NULL;
		len = 0;
		received_bits = 0;
		str_index = 0;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		len = 0;
	static char		*str = NULL;
	static int		receiving_len = 1;
	static int		received_bits = 0;

	if (receiving_len == 1)
	{
		len = 0;
		len = get_strlen(signum, info, context);
		if (len > 0)
		{
			receiving_len = 0;
			str = malloc(sizeof(char) * (len + 1));
			if (!str)
				return ;
			str[len] = '\0';
			str_index = 0;
		}
		return ;
	}
	str = store_str(str, signum, info, context);
	print_str(len, str);
	receiving_len = 1;
}

int	sigaction_init(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = signal_handler;
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

int	main(void)
{
	ft_printf_fd(1, "Server PID : %d\n", getpid());
	if (sigaction_init() == 1)
		return (1);
	while (1)
	{
		pause();
	}
	return (0);
}
