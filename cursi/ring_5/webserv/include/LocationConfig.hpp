#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>

class LocationConfig {
private:
    std::string _path;
    std::string _root;
    std::string _index;
    bool        _autoindex;
    std::string _cgiPass;

public:
    LocationConfig();
    LocationConfig(const LocationConfig &other);
    LocationConfig &operator=(const LocationConfig &other);
    LocationConfig(const std::string &path,
                   const std::string &root,
                   const std::string &index,
                   bool autoindex,
                   const std::string &cgiPass);
    ~LocationConfig();

    // Setters
    void setPath(const std::string &path);
    void setRoot(const std::string &root);
    void setIndex(const std::string &index);
    void setAutoindex(bool autoindex);
    void setCgiPass(const std::string &cgiPass);

    // Getters
    const std::string& getPath() const;
    const std::string& getRoot() const;
    const std::string& getIndex() const;
    bool getAutoindex() const;
    const std::string& getCgiPass() const;
};

#endif
