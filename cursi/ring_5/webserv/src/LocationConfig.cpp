#include "LocationConfig.hpp"

LocationConfig::LocationConfig() : _autoindex(false) {
}

LocationConfig::LocationConfig(const LocationConfig &other) {
   *this = other;
}

LocationConfig &LocationConfig::operator=(const LocationConfig &other) {
    if (this != &other) {
        _path = other._path;
        _root = other._root;
        _index = other._index;
        _autoindex = other._autoindex;
        _cgiPass = other._cgiPass;
    }
    return *this;
}

LocationConfig::LocationConfig(const std::string &path, const std::string &root,
                               const std::string &index, bool autoindex,
                               const std::string &cgiPass)
    : _path(path), _root(root), _index(index), _autoindex(autoindex), _cgiPass(cgiPass) {
}

LocationConfig::~LocationConfig() {
}

// Setters
void LocationConfig::setPath(const std::string &path) {
    _path = path;
}

void LocationConfig::setRoot(const std::string &root) {
    _root = root;
}

void LocationConfig::setIndex(const std::string &index) {
    _index = index;
}

void LocationConfig::setAutoindex(bool autoindex) {
    _autoindex = autoindex;
}

void LocationConfig::setCgiPass(const std::string &cgiPass) {
    _cgiPass = cgiPass;
}

// Getters
const std::string& LocationConfig::getPath() const {
    return _path;
}

const std::string& LocationConfig::getRoot() const {
    return _root;
}

const std::string& LocationConfig::getIndex() const {
    return _index;
}

bool LocationConfig::getAutoindex() const {
    return _autoindex;
}

const std::string& LocationConfig::getCgiPass() const {
    return _cgiPass;
}
