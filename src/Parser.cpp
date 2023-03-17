/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Parser.hpp"
#include <string.h>
#include <algorithm>

std::vector<std::string> plazza::Parser::cutEachCommand(std::string cmd)
{
    std::vector<std::string> pizzaInfos;
    int start = 0;
    int end = cmd.find(" ");
    int count = 0;
    std::string tmp;

    if (end == -1)
        return (pizzaInfos);
    while (end != -1) {
        tmp = cmd.substr(start, end - start);
        if (count == 0 && strcasecmp(tmp.c_str(), "regina") != 0 &&
            strcasecmp(tmp.c_str(), "margarita") != 0
            && strcasecmp(tmp.c_str(), "americana") != 0 &&
            strcasecmp(tmp.c_str(), "fantasia") != 0) {
            pizzaInfos.clear();
            return (pizzaInfos);
        } else if (count == 1 && strcasecmp(tmp.c_str(), "S") != 0 &&
                   strcasecmp(tmp.c_str(), "M") != 0
                   && strcasecmp(tmp.c_str(), "L") != 0 &&
                   strcasecmp(tmp.c_str(), "XL") != 0 &&
                   strcasecmp(tmp.c_str(), "XXL") != 0) {
            pizzaInfos.clear();
            return (pizzaInfos);
        }
        for (int i = 0; i < tmp.size(); i++)
            tmp[i] = std::tolower(tmp[i]);
        pizzaInfos.push_back(tmp);
        start = end + 1;
        end = cmd.find(" ", start);
        count++;
    }
    if (count != 2) {
        pizzaInfos.clear();
        return (pizzaInfos);
    }
    tmp = cmd.substr(start, cmd.size());
    if (tmp[0] != 'x' || atoi(tmp.c_str() + 1) == 0) {
        pizzaInfos.clear();
        return (pizzaInfos);
    }
    pizzaInfos.push_back(tmp.c_str() + 1);

    return (pizzaInfos);
}

std::vector<struct plazza::infosCommandsString> plazza::Parser::parseCommand(std::string cmd)
{
    int i = 0;
    int end = cmd.find(";");
    int start = 0;
    std::string tmp;
    std::vector<struct infosCommandsString> tmpVectorStruct;
    std::vector<std::string> tmpVector;
    struct infosCommandsString tmpStruct = {"", "", 0};

    for (i = 0; end != -1; i++) {
        if (cmd[end] == ';')
            tmp = cmd.substr(start, (end - start));
        else
            tmp = cmd.substr(start, (end - start) - 1);
        tmpVector = cutEachCommand(tmp);
        if (tmpVector.empty()) {
            tmpVectorStruct.clear();
            return (tmpVectorStruct);
        }
        tmpVectorStruct.push_back(tmpStruct);
        tmpVectorStruct[i].Type = tmpVector[0];
        tmpVectorStruct[i].Size = tmpVector[1];
        tmpVectorStruct[i].nb = atoi(tmpVector[2].c_str());
        start = end + 2;
        end = cmd.find(";", start);
        if (start > end && end != -1) {
            tmpVectorStruct.clear();
            return (tmpVectorStruct);
        }
        tmp.clear();
    }
    tmp = cmd.substr(start, cmd.size());
    tmpVector = cutEachCommand(tmp);
    if (tmpVector.empty()) {
        tmpVectorStruct.clear();
        return (tmpVectorStruct);
    }
    tmpVectorStruct.push_back(tmpStruct);
    tmpVectorStruct[i].Type = tmpVector[0];
    tmpVectorStruct[i].Size = tmpVector[1];
    tmpVectorStruct[i].nb = atoi(tmpVector[2].c_str());

    return (tmpVectorStruct);
}