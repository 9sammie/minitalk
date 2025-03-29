/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:09 by maballet          #+#    #+#             */
/*   Updated: 2025/03/29 12:58:54 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L

# include "../libft/inc/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int		param_check(int argc, char**argv);
void	send_message(pid_t pid, char *message);
void	send_char(pid_t pid, unsigned char c);
void	send_len(pid_t pid, int len);
void	signal_server_handler(int signum, siginfo_t *info, void *context);
int		sigaction_server_init(void);
char	*str_alloc(int len, int *receiving_len, char *str);
void	print_str(int len, char **str, int *receiving_len);
char	*store_str(int client_pid, char *str, int signum);
int		get_strlen(int client_pid, int signum);

#endif