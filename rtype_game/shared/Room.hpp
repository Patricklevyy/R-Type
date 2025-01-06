

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Room
{
public:
    Room(const std::string &roomName, int nbClient) : _roomName(roomName), _nbClient(nbClient) {}

    const std::string &getName() const { return _roomName; }
    int getNbClient() const { return _nbClient; }

private:
    std::string _roomName;
    int _nbClient;
};