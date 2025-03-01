/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.tpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:32:59 by svilla-d          #+#    #+#             */
/*   Updated: 2025/03/01 19:33:00 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_TPP
#define SPAN_TPP

#include "Span.hpp"
#include <algorithm>
#include <iterator>

template <typename InputIterator>
void Span::addNumber(InputIterator first, InputIterator last)
{
    unsigned int dist = static_cast<unsigned int>(std::distance(first, last));
    if (numbers.size() + dist > capacity)
        throw std::runtime_error("Not enough capacity in Span to add the range of numbers.");
    numbers.insert(numbers.end(), first, last);
}

#endif
