#include "ft_printf.h"

static int	ft_lg_uns(unsigned int n)
{
	int	len;

	if (n == 0)
		return (len = 1);
	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_uns(unsigned int n)
{
	char	*str;
	size_t	i;

	i = ft_lg_uns(n);
	str = malloc(sizeof(char) * i + 1);
	if (!(str))
		return (NULL);
	str[i] = '\0';
	i--;
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

static void	ft_pre_u(t_flags *flags, int *space, int *zero, int *len)
{
	if (flags->precision > (*len))
		(*zero) = flags->precision - (*len);
	else if (!flags->precision && flags->dot && flags->width > (*len))
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

static void	ft_get_u(t_flags *flags, char *nbr_uns, int *len)
{
	int	space;
	int	zero;
	int	i;

	i = 0;
	ft_pre_u(flags, &space, &zero, len);
	flags->ret = flags->ret + space + (*len);
	if (!flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	while (zero-- > 0)
		ft_putchar_fd('0', 1);
	if (*len)
		while (nbr_uns[i])
			ft_putchar_fd(nbr_uns[i++], 1);
	if (flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}

void	ft_uns(va_list ap, t_flags *flags)
{
	char	*nbr_uns;
	int		len;

	nbr_uns = ft_itoa_uns(va_arg(ap, unsigned int));
	len = ft_strlen(nbr_uns);
	if (nbr_uns && flags->dot && !flags->precision && nbr_uns[0] == '0')
		len = 0;
	ft_get_u(flags, nbr_uns, &len);
	free(nbr_uns);
}
