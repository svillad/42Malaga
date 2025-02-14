#include "ILogger.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    ILogger* logger = NULL;

    #ifdef LOG_MODE_CONSOLE
        logger = new ConsoleLogger();
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: Console" << std::endl;
    #elif defined(LOG_MODE_FILE)
        logger = new FileLogger("logs.log");
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: File" << std::endl;
    #else
        std::cerr << COLOR_ERROR << "[  ERROR  ] " << COLOR_RESET << "No valid LOG_MODE specified!" << COLOR_RESET << std::endl;
        return 1;
    #endif
    logger->log(DEBUG, "[main] New program execution");

    try {
        std::cout << "\n---------- Bureaucrat's tests ----------" << std::endl;
        Bureaucrat b1("Jesica", 1);
        b1.setLogger(logger);
        Bureaucrat b2("Sebas", 150);
        b2.setLogger(logger);
        
        std::cout << b1 << std::endl;
        std::cout << b2 << std::endl;

        b1.decrementGrade();
        b2.incrementGrade();
        std::cout << b1 << std::endl;
        std::cout << b2 << std::endl;

        std::cout << "\n---------- Exception's test ----------" << std::endl;
        Bureaucrat b3("Juan", 10);
        b3.setLogger(logger);
        for (int i = 0; i < 100; i++) {
            b3.incrementGrade();
        }
        std::cout << b3 << std::endl;
    } catch (const std::exception &e) {
        logger->log(ERROR, "[main] Exception: " + std::string(e.what()));
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    delete logger;
    return 0;
}
