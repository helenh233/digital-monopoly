#include "Utility.h"

int genRandom(int lower, int upper) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(lower, upper);
    
    int random_number = dist(gen);
    return random_number;
}

std::map<std::string, std::vector<std::string>> MONOPOLY_BLOCK = {
  {"Arts1", {"AL", "ML"}},
  {"Arts2", {"ECH", "PAS", "HH"}},
  {"Eng", {"RCH", "DWE", "CPH"}},
  {"Health", {"LHI", "BMH", "OPT"}}, 
  {"Env", {"EV1", "EV2", "EV3"}},
  {"Sci1", {"PHYS", "B1", "B2"}},
  {"Sci2", {"EIT", "ESC", "C2"}},
  {"Math", {"MC", "DC"}}
}; 

std::map<std::string, std::string> BUILDING_TO_BLOCK = {
  {"AL", "Arts1"}, {"ML", "Arts1"}, 
  {"ECH", "Arts2"}, {"PAS", "Arts2"}, {"HH", "Arts2"}, 
  {"RCH", "Eng"}, {"DWE", "Eng"}, {"CPH", "Eng"},
  {"LHI", "Health"}, {"BMH", "Health"}, {"OPT", "Health"},
  {"EV1", "Env"}, {"EV2", "Env"}, {"EV3", "Env"},
  {"PHYS", "Sci1"}, {"B1", "Sci1"}, {"B2", "Sci1"},
  {"EIT", "Sci2"}, {"ESC", "Sci2"}, {"C2", "Sci2"},
  {"MC", "Math"}, {"DC", "Math"}
}; 


std::map<std::string, int> BLOCK_PROP_COUNT = {
	{"Arts1", 2}, {"Arts2", 3}, {"Eng", 3}, {"Health", 3},
	{"Env", 3}, {"Sci1", 3}, {"Sci2", 3}, {"Math", 2}
};


std::vector<std::string> PROPS = {"AL", "ML", "ECH", "PAS", "HH", "RCH", "DWE", "CPH", "LHI",
  "BMH", "OPT", "EV1", "EV2", "EV3", "PHYS", "B1", "B2",
  "EIT", "ESC", "C2", "MC", "DC", "PAC", "CIF", "MKV", "UWP", "V1", "REV"}; 
