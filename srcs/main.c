/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:44:53 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/07 10:50:39 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "ft_mini_ls.h"

int		mls_errend(char *str)
{
	ft_putstr_fd("ft_mini_ls: ", FD_STDERR);
	if (str)
	{
		ft_putstr_fd(str, FD_STDERR);
		ft_putstr_fd(": ", FD_STDERR);
	}
	if (!errno)
		ft_putstr_fd(": No arguments allowed\n", FD_STDERR);
	else
		perror("");
	return (1);
}

t_list	*mls_makedirlst(DIR *dptr)
{
	int				ret;
	t_list			*dlst;
	struct dirent	*dent;
	t_dirdata		*ddata;

	dlst = NULL;
	while ((dent = readdir(dptr)))
	{
		if (*(dent->d_name) == '.')
			continue ;
		ddata = (t_dirdata *)malloc(sizeof(t_dirdata));
		ft_strlcpy(ddata->name, dent->d_name, __DARWIN_MAXPATHLEN);
		if ((ret = lstat(ddata->name, &ddata->stat)))
		{
			printf("ret = %d\n", ret);
			return (NULL);
		}
		ft_lstadd_back(&dlst, ft_lstnew(ddata));
	}
	return (dlst);
}

void	mls_put_dname(void *ddata_ptr)
{
	t_dirdata		*ddata;

	ddata = (t_dirdata *)ddata_ptr;
	ft_putendl_fd(ddata->name, FD_STDOUT);
}

int		mls_cmp_atime(t_dirdata *dir1, t_dirdata *dir2)
{
	if (dir1->stat.st_mtimespec.tv_sec < dir2->stat.st_mtimespec.tv_sec)
		return (-1);
	else if (dir1->stat.st_mtimespec.tv_sec > dir2->stat.st_mtimespec.tv_sec)
		return (1);
	else if (dir1->stat.st_mtimespec.tv_nsec < dir2->stat.st_mtimespec.tv_nsec)
		return (-1);
	else if (dir1->stat.st_mtimespec.tv_nsec > dir2->stat.st_mtimespec.tv_nsec)
		return (1);
	return (-ft_strncmp(dir1->name, dir2->name, __DARWIN_MAXPATHLEN));
}

int		main(int argc, char **argv)
{
	DIR				*dptr;
	t_list			*dlst;

	dlst = NULL;
	if (argc != 1)
		return (mls_errend(argv[1]));
	if (!(dptr = opendir(".")))
		return (mls_errend("."));
	dlst = mls_makedirlst(dptr);
	closedir(dptr);
	if (errno)
	{
		ft_lstclear(&dlst, free);
		return (mls_errend(NULL));
	}
	ft_lstsort(&dlst, mls_cmp_atime);
	ft_lstiter(dlst, mls_put_dname);
	ft_lstclear(&dlst, free);
	return (0);
}
