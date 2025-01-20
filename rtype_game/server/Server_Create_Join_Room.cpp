/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server_Create_And_Join_Room
*/

#include "Server.hpp"

namespace rtype
{
    void Server::createRoom(const unsigned int id, std::string &params)
    {
        (void) id;

        (void)id;

        std::cout << "JE parse" << std::endl;
        std::map<std::string, std::string> map_params = Utils::parseMessageParams(params);
        std::cout << "JE check" << std::endl;
        checkCreateRoomArgs(map_params);

        std::cout << "JE set LA OMMAND" << std::endl;
        auto newRoom = std::make_shared<Room>(_currentPort, map_params["room_name"]);
        newRoom->start(_currentPort, map_params["x"], map_params["y"], map_params["dif"]);
        _rooms.push_back(newRoom);
        _currentPort++;
    }

    void Server::joinRoom(
        const unsigned int id, std::string &params, std::string &lastclientAdr)
    {
        (void) id;

        std::map<std::string, std::string> map_params =
            Utils::parseMessageParams(params);

        checkJoinRoomArgs(map_params);

        for (auto &room : _rooms)
        {
            if (room->getName() == map_params["room_name"])
            {
                if (map_params.find("client_name") != map_params.end())
                {
                    room->createClient(lastclientAdr, map_params["client_name"]);
                }
                else
                {
                    room->createClient(lastclientAdr, "");
                }
            }
        }
    }

    void Server::checkCreateRoomArgs(std::map<std::string, std::string> params)
    {
        if (params.find("room_name") == params.end())
            throw ERROR::MissingRoomsParamsExceptions(
                "Missing 'room_name' param");

        for (auto &room : _rooms) {
            if (room->getName() == params["room_name"]) {
                throw ERROR::RoomAlreadyExistingExceptions("This name is already taken for a room");
            }
        }
    }

    void Server::checkJoinRoomArgs(std::map<std::string, std::string> params)
    {
        if (params.find("room_name") == params.end()
            || params.find("client_name") == params.end())
            throw ERROR::MissingRoomsParamsExceptions(
                "Missing 'room_name' param or 'client_name' param");

        bool roomFound = false;

        for (auto &room : _rooms) {
            if (room->getName() == params["room_name"]) {
                roomFound = true;
                if (room->getNbClient() >= 4) {
                    throw ERROR::RoomIsFullExceptions("The room is full of client (4 MAX PER ROOM)");
                }
            }
        }

        if (!roomFound) {
            throw ERROR::RoomNotFoundExceptions("Room not found");
        }
    }
} // namespace rtype