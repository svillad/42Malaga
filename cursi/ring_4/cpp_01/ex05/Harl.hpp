#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <string>

# define LEVELS 4

class Harl {
private:
    std::string	levels[4];

	void	(Harl::*actions[4])(void);
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);

public:
	Harl();
	void	complain(std::string level);
	int		get_complain_index(std::string level);
};

#endif
