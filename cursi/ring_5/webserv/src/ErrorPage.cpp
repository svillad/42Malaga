#include "ErrorPage.hpp"
#include <cstdlib>

ErrorPage::ErrorPage() : _pagePath("") {
}

ErrorPage::ErrorPage(const ErrorPage &other) {
    *this = other;
}

ErrorPage &ErrorPage::operator=(const ErrorPage &other) {
    if (this != &other) {
        _errorCodes = other._errorCodes;
        _pagePath = other._pagePath;
    }
    return *this;
}

ErrorPage::ErrorPage(const std::vector<int> &errorCodes, const std::string &pagePath)
    : _errorCodes(errorCodes), _pagePath(pagePath) {
}

ErrorPage::~ErrorPage() {
}

// Setters
void ErrorPage::setErrorCodes(const std::vector<int> &errorCodes) {
    _errorCodes = errorCodes;
}

void ErrorPage::setPagePath(const std::string &pagePath) {
    _pagePath = pagePath;
}

// Getters
const std::vector<int>& ErrorPage::getErrorCodes() const {
    return _errorCodes;
}

const std::string& ErrorPage::getPagePath() const {
    return _pagePath;
}
