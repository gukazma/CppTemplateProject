#include <iostream>
#include <thread>
#include <LibName/Timer.hpp>
int main(int argc, char* argv[])
{
    LibName::Timer timer;
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::cout << "Sleep for: " << timer.GetElapsedSecondsD() << std::endl;
}
