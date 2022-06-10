#include <string>
#include <iomanip>
#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
//Conditional operator used, true:false
long hours, minutes;
hours = seconds/3600; //seconds in an hour
seconds = seconds%3600; //remainder
minutes = seconds/60; //seconds in a minute
seconds = seconds%60; //remainder

//below would give h::mm::s
//string output = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);

//followed knowledge base to use
std::ostringstream stream;
stream<<std::setw(2) <<std::setfill('0') << hours << ":"
<<std::setw(2) << std::setfill('0') << minutes << ":"
<<std::setw(2) << std::setfill('0') << seconds;
return stream.str();
}