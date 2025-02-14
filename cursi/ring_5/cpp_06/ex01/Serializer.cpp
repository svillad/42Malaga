#include "Serializer.hpp"

ILogger* Serializer::logger = NULL;

Serializer::Serializer() {
}

Serializer::Serializer(const Serializer &) {
}

Serializer& Serializer::operator=(const Serializer &other) {
    (void)other;
    return *this;
}

void Serializer::setLogger(ILogger* log) {
    logger = log;
    if (logger)
        logger->log(DEBUG, "[Serializer] Logger initialized.");
}

uintptr_t Serializer::serialize(Data* ptr) {
    uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
    if (logger)
        logger->log(DEBUG, "[Serializer] Serialized pointer: " + to_string(raw));
    return raw;
}

// Convert unsigned integer back to pointer
Data* Serializer::deserialize(uintptr_t raw) {
    Data* ptr = reinterpret_cast<Data*>(raw);
    if (logger)
        logger->log(DEBUG, "[Serializer] Deserialized pointer: " + to_string(raw));
    return ptr;
}
