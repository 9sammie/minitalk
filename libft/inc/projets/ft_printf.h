/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:34:26 by maballet          #+#    #+#             */
/*   Updated: 2025/03/20 22:13:00 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_putstr_printf(int fd, char *s);
int		ft_putnbr_printf(int fd, int n);
int		ft_pnbrb(int fd, unsigned long n, char *base, unsigned long baselen);
int		ft_putptr(int fd, void *ptr);
int		ft_putchar_printf(int fd, char c);
int		ft_strlen_printf(char *s);
char	*ft_strchr_printf(const char *s, int c);
int		ft_check(int fd, va_list ap, int *i, const char *s);

#endif