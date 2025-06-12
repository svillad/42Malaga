#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {
}

TargetGenerator::~TargetGenerator() {
    for (std::map<std::string, ATarget*>::iterator it = targets.begin(); it != targets.end(); ++it)
        delete it->second;
}

void TargetGenerator::learnTargetType(ATarget *target) {
    if (!target) return;

    if (targets.find(target->getType()) == targets.end())
        targets[target->getType()] = target->clone();
}

void TargetGenerator::forgetTargetType(const std::string &type) {
    std::map<std::string,ATarget*>::iterator it = targets.find(type);
    if (it != targets.end()) {
        delete it->second;
        targets.erase(it);
    }
}

ATarget *TargetGenerator::createTarget(const std::string &type) {
    std::map<std::string, ATarget*>::iterator it = targets.find(type);
    if (it != targets.end())
        return it->second->clone();
    return 0;
}
