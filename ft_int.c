#include "ft_printf.h"

static void	ft_pre_d_i(t_flags *flags, int *space, int *zero, int *len)
{
	if (flags->precision > (*len))
		(*zero) = flags->precision - (*len);
	else if (flags->width > (*len) && !flags->precision && flags->dot)
		flags->zero = 0;
	else if (flags->width > (*len) && flags->zero)
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

static void	ft_get_d_i(t_flags *flags, char *nbr, int *len)
{
	int	space;
	int	zero;
	int	i;

	i = 0;
	ft_pre_d_i(flags, &space, &zero, len);
	flags->ret = flags->ret + space + (*len);
	if (!flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	if (flags->negative)
		ft_putchar_fd(nbr[i++], 1);
	while (zero-- > 0)
		ft_putchar_fd('0', 1);
	if (*len)
		while (nbr[i])
			ft_putchar_fd(nbr[i++], 1);
	if (flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}

void	ft_int(va_list ap, t_flags *flags)
{
	char	*nbr;
	int		len;
	int		i;

	i = 0;
	nbr = ft_itoa(va_arg(ap, int));
	len = ft_strlen(nbr);
	if (nbr && nbr[i] == '-')
	{
		flags->negative = 1;
		if (flags->precision > 0)
			flags->precision += 1;
	}
	if (nbr && flags->dot && !flags->precision && nbr[0] == '0')
		len = 0;
	ft_get_d_i(flags, nbr, &len);
	free(nbr);
}
