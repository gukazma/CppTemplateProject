#include <LibName/Timer.hpp>
#include <iostream>
#include <thread>
int main(int argc, char* argv[])
{
    LibName::Timer timer;
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    std::cout << "Sleep for: " << timer.GetElapsedSecondsD() << std::endl;
}
