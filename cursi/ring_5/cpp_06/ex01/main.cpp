#include "Serializer.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"

int main() {
    ILogger* logger = NULL;

    #ifdef LOG_MODE_CONSOLE
        logger = new ConsoleLogger();
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: Console" << std::endl;
    #elif defined(LOG_MODE_FILE)
        logger = new FileLogger("logs.log");
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: File" << std::endl;
    #else
        std::cerr << "[  ERROR  ] No valid LOG_MODE specified!" << std::endl;
        return 1;
    #endif
    logger->log(DEBUG, "[main] New program execution");

    Serializer::setLogger(logger);

    std::cout << "\n---------- Original Data ----------" << std::endl;
    Data original;
    original.id = 42;
    original.value = 3.14f;
    for (int i = 0; i < 24; i++) {
        original.name[i] = 'A' + (i % 26); // Rellenar con caracteres
    }
    original.name[24] = '\0';

    std::cout << "Original Data Object: " << std::endl;
    std::cout << "ID: " << original.id << std::endl;
    std::cout << "Name: " << original.name << std::endl;
    std::cout << "Value: " << original.value << std::endl;

    std::cout << "\n---------- Serializer's tests ----------" << std::endl;
    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "\nSerialized Address: " << raw << std::endl;

    Data* deserialized = Serializer::deserialize(raw);

    std::cout << "\n---------- Deserialized's tests ----------" << std::endl;
    std::cout << "\nDeserialized Data Object: " << std::endl;
    std::cout << "ID: " << deserialized->id << std::endl;
    std::cout << "Name: " << deserialized->name << std::endl;
    std::cout << "Value: " << deserialized->value << std::endl;

    if (deserialized == &original) {
        std::cout << "\nSuccess: Deserialized pointer matches the original pointer." << std::endl;
    } else {
        std::cout << "\nError: Deserialized pointer does not match the original pointer." << std::endl;
    }

    return 0;
}
