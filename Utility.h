#ifndef _UTILITY_H
#define _UTILITY_H

#include <random>
#include <vector>
#include <string>
#include <map>

extern int genRandom(int lower, int upper);
extern std::map<std::string, std::vector<std::string>> MONOPOLY_BLOCK;

extern std::map<std::string, std::string> BUILDING_TO_BLOCK;

extern std::map<std::string, int> BLOCK_PROP_COUNT;

extern std::vector<std::string> PROPS;

#endif
