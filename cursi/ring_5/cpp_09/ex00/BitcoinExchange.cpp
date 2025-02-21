#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cctype>

static bool isDigits(const std::string &s) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

static int getMaxDay(int year, int month) {
    if (month == 2) {
        return ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

static bool validateFormat(const std::string &date, std::string &yearStr, std::string &monthStr, std::string &dayStr) {
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    yearStr  = date.substr(0, 4);
    monthStr = date.substr(5, 2);
    dayStr   = date.substr(8, 2);
    return true;
}


BitcoinExchange::BitcoinExchange() : bitcoin() { }

BitcoinExchange::BitcoinExchange(const std::string &data) : bitcoin() {
    loadData(data);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : bitcoin(other.bitcoin) {
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        bitcoin = other.bitcoin;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::loadData(const std::string &data) {
    std::ifstream file(data.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open data file." << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string date;
        std::string rateStr;
        if (std::getline(iss, date, ',') && std::getline(iss, rateStr)) {
            double rate = atof(rateStr.c_str());
            bitcoin[date] = rate;
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string &dateStr) {
    std::string yearStr, monthStr, dayStr;
    if (!validateFormat(dateStr, yearStr, monthStr, dayStr))
        return false;
    if (!isDigits(yearStr) || !isDigits(monthStr) || !isDigits(dayStr))
        return false;
    int year  = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day   = std::atoi(dayStr.c_str());
    if (year <= 0)
        return false;
    if (month < 1 || month > 12)
        return false;
    int maxDay = getMaxDay(year, month);
    if (day < 1 || day > maxDay)
        return false;
    return true;
}

void BitcoinExchange::process(const std::string &inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    if (std::getline(file, line)) {
        if (line.find("date") == std::string::npos || line.find("value") == std::string::npos) {
            std::cerr << "Error: invalid header format." << std::endl;
            return;
        }
    }
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string date;
        std::string separator;
        std::string valueStr;
        if (!(iss >> date >> separator >> valueStr)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        double value = atof(valueStr.c_str());
        if (value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        std::map<std::string, double>::iterator it = bitcoin.lower_bound(date);
        if (it == bitcoin.end() || it->first != date) {
            if (it == bitcoin.begin()) {
                std::cout << "Error: no exchange rate available for date " << date << std::endl;
                continue;
            } else {
                --it;
            }
        }

        double rate = it->second;
        double result = value * rate;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
    file.close();
}
