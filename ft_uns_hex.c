#include "ft_printf.h"

char	*ft_itoa_uns_hex(unsigned int nb, int base)
{
	char			*str;
	unsigned int	tmp;
	int				len;

	len = 1;
	tmp = nb;
	while (tmp / base > 0)
	{
		tmp = tmp / base;
		len++;
	}
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if (nb % base < 10)
			str[len] = nb % base + '0';
		else
			str[len] = nb % base + 'a' - 10;
		nb = nb / base;
	}
	return (str);
}

void	ft_pre_uns_hex(t_flags *flags, int *space, int *zero, int *len)
{
	if (flags->precision > (*len))
		(*zero) = flags->precision - (*len);
	else if (flags->width > (*len) && flags->dot && !flags->precision)
		flags->zero = 0;
	else if (flags->width > 0 && flags->zero)
		(*zero) = flags->width - (*len);
	else
		(*zero) = 0;
	if ((*zero) > 0)
		(*len) = (*len) + (*zero);
	if (flags->width > (*len) && !flags->zero)
		(*space) = flags->width - (*len);
	else
		(*space) = 0;
}

void	ft_uns_hex_next(t_flags *flags, char *nbr, int *len)
{
	int		space;
	int		zero;
	int		i;

	i = 0;
	ft_pre_uns_hex(flags, &space, &zero, len);
	flags->ret = flags->ret + space + (*len);
	if (!flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	while (zero-- > 0)
		ft_putchar_fd('0', 1);
	if (*len)
		while (nbr[i])
			ft_putchar_fd(nbr[i++], 1);
	if (flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}

void	ft_uns_hex(va_list ap, t_flags *flags)
{
	char	*nbr;
	int		len;

	nbr = ft_itoa_uns_hex(va_arg(ap, unsigned int), 16);
	len = ft_strlen(nbr);
	if (nbr && flags->dot && !flags->precision && nbr[0] == '0')
		len = 0;
	ft_uns_hex_next(flags, nbr, &len);
	free(nbr);
}
