#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_flags
{
	int	ret;
	int	dash;
	int	zero;
	int	dot;
	int	precision;
	int	width;
	int	negative;
	int	zero_per;
}				t_flags;

void	ft_char(va_list ap, t_flags *flags);
void	ft_verif_flags(const char *format, va_list ap, t_flags *flags, \
		int *count);
void	ft_hex(va_list ap, t_flags *flags);
void	ft_int(va_list ap, t_flags *flags);
void	ft_string(va_list ap, t_flags *flags);
void	ft_uns_hex(va_list ap, t_flags *flags);
void	ft_uns_maj_hex(va_list ap, t_flags *flags);
void	ft_uns(va_list ap, t_flags *flags);
void	ft_percent(t_flags *flags);
int		ft_printf(const char *format, ...);

#endif