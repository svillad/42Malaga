#ifndef ERRORPAGE_HPP
#define ERRORPAGE_HPP

#include <string>
#include <vector>

class ErrorPage {
private:
    std::vector<int> _errorCodes;
    std::string _pagePath;

public:
    ErrorPage();
    ErrorPage(const ErrorPage &other);
    ErrorPage &operator=(const ErrorPage &other);
    ErrorPage(const std::vector<int> &errorCodes, const std::string &pagePath);
    ~ErrorPage();

    // Setters
    void setErrorCodes(const std::vector<int> &errorCodes);
    void setPagePath(const std::string &pagePath);

    // Getters
    const std::vector<int>& getErrorCodes() const;
    const std::string& getPagePath() const;
};

#endif
