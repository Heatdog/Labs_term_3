#include "Mission.h"

int main() {
    Mission mission;

    std::cout << mission.get_pirate_table()->count() << std::endl;
    mission.get_pirate_table()->erase("pirate1");
    if(mission.get_pirate_table()->find("pirate1") == nullptr){
        std::cout << "кек" << std::endl;
    }
    std::cout << mission.get_pirate_table()->count();

    return 0;
}
