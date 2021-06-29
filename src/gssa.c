/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gssa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:37:26 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/28 17:45:52 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//todo gotta force stacks to be values n [1, n] for an n length stack (i.e not [1,16, 34] ==> [1,2,3])

void print_arr(int *arr, int size)
{
    int i;

    i = -1;
    while (++i < size)
    {
        ft_putstr_fd("[  ", STDERR_FILENO);
        ft_putnbr_fd(arr[i], STDERR_FILENO);
        ft_putstr_fd(" ] ", STDERR_FILENO);
    }
    ft_putstr_fd("\n", STDERR_FILENO);
}

int gssa(int *arr, int **ret, int value, int cur_pos, int len)
{
    static int max_val = 0;
    static int *max_arr = NULL;
    int potential;
    int i;
    int new_val;

    if (max_arr == NULL)
        max_arr = (int *)malloc(sizeof(int) * len);
    if (max_arr == NULL)
        error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
    if (value != 1 && (arr[cur_pos] <= 1 || cur_pos >= len))
        return (value);
    i = cur_pos;
    while (++i < len)
    {
        if (arr[i] < arr[cur_pos])
        {
            potential = ft_min(arr[i], len - i);
            if (potential > max_val)
            {
                (*ret)[value] = arr[i];
                new_val = gssa(arr, ret, value + 1, i, len);
                if (new_val > max_val)
                {
                    max_val = new_val;
                    // fprintf(stderr, "\n\nchanging MAX new_val is :%d\n", new_val);                    
                    // print_arr(*ret, new_val);
                    ft_memcpy(max_arr, *ret, new_val * sizeof(int));
                    // print_arr(max_arr, max_val);
                    // fprintf(stderr, "ENDMAX\n");
                }
            }
        }
    }
    if (value == 1)
    {
        // print_arr(max_arr, max_val);
        // printf("lol size is %d\n", max_val);
        free(*ret);
        *ret = max_arr;
        max_arr = NULL;
        value = max_val;
        max_val = 0;
        return (value);
    }
    return (value);
}
