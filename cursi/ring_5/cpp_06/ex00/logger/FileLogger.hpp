/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileLogger.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:21:08 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:21:09 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "ILogger.hpp"
#include <fstream>
#include <ctime>

class FileLogger : public ILogger {
private:
    std::ofstream file;
    std::string getTimestamp() const;
    
public:
    FileLogger(const std::string& filename);
    ~FileLogger();
    void log(LogLevel level, const std::string& msg);
};

#endif
