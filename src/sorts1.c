/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:51:01 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/22 12:59:11 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char    *bubble_sort(t_stack a, t_stack b)
{
    char    *ans;
    int     i;
    int     going_up;
    int     flag;

    ans = ft_strdup("");
    i = 0;
    going_up = 1;
    flag = 0;
    while (!is_sorted_inc(a))
    {
        if (going_up)
        {
            if (i < a->size(a) - 1 && a->items[a->top] > a->items[a->top - 1])
                ans = exec_and_str_op(a, b, "sa", ans);
            ans = exec_and_str_op(a, b, "ra", ans);    
            if (++i >= a->size(a))
                going_up = 0;
        }
        else
        {
            flag = 1;
            if (a->items[a->top] > a->items[a->top - 1])
                ans = exec_and_str_op(a, b, "sa", ans);
            if (i > 1)
                ans = exec_and_str_op(a, b, "rra", ans);   
            if (--i <= 0)
                going_up = 1;
        }
        // if (i < a->size(a) && a->items[a->top] > a->items[a->top - 1])
        // {
        //     execute_op(a, b, "sa");
        //     print_stack(a);
        //     ans = join_delete(ans, ft_strdup("sa"));
        // }            
        // execute_op(a, b, "ra");
        //     print_stack(a);
    
        // ans = join_delete(ans, ft_strdup("ra"));
        // i++;
        // if (i > a->size(a))
        //     i = 0;
    }
    delete_stack(&a);    
    delete_stack(&b);
    return (ans);
}

char    *bubble_sort_rev(t_stack a, t_stack b)
{
    char    *ans;

    ans = ft_strdup("");
    while (!is_sorted_inc(a))
    {
        if (a->items[a->top] > a->items[a->top - 1])
        {
            execute_op(a, b, "sa");
            join_delete(ans, ft_strdup("sa"));
        }
        execute_op(a, b, "rra");
        join_delete(ans, ft_strdup("rra"));
    }
    delete_stack(&a);    
    delete_stack(&b);
    return (ans);    
}