/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:45:27 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/03 16:31:26 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS
# define FT_MINI_LS

# include <sys/types.h>
# include <sys/stat.h>

typedef struct	s_dirdata
{
	char		name[__DARWIN_MAXPATHLEN];
	struct stat	stat;
}				t_dirdata;

#endif
