#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <unordered_map>

// 定义移动方向枚举
enum class Direction {
    LEFT = 'L',
    RIGHT = 'R',
    STAY = 'S'
};

class StateManager {
public:
    StateManager() : nextStateId(0) {}

    // Add a new state if it doesn't exist
    int addState(const std::string& stateName) {
        if (nameToId.find(stateName) != nameToId.end()) {
            return nameToId[stateName];
        }
        
        int newId = nextStateId++;
        nameToId[stateName] = newId;
        idToName[newId] = stateName;
        return newId;
    }

    // Get state ID from name
    int getStateId(const std::string& stateName) const {
        auto it = nameToId.find(stateName);
        if (it == nameToId.end()) {
            throw std::runtime_error("State not found: " + stateName);
        }
        return it->second;
    }

    // Get state name from ID
    std::string getStateName(int stateId) const {
        auto it = idToName.find(stateId);
        if (it == idToName.end()) {
            throw std::runtime_error("Invalid state ID: " + std::to_string(stateId));
        }
        return it->second;
    }

    // Get total number of states
    size_t getStateCount() const {
        return nameToId.size();
    }

private:
    std::unordered_map<std::string, int> nameToId;
    std::unordered_map<int, std::string> idToName;
    int nextStateId;
};
