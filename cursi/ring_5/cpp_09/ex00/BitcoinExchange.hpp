#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
private:
    std::map<std::string, double> bitcoin;

    void loadData(const std::string &data);
    bool isValidDate(const std::string &date);

public:
    // Constructor por defecto
    BitcoinExchange();
    BitcoinExchange(const std::string &data);
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void process(const std::string &inputFile);
};

#endif // BITCOINEXCHANGE_HPP
