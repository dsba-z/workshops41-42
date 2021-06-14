
#include "person.h"

#include <sstream>

std::string Student::makeNameGroup() const
{
    std::stringstream ss;
    ss << "Name: " << _name << ", Group ID: " << _groupId;
    return ss.str();
    // ASK: what would happen if _name is a private field - change and see
}
