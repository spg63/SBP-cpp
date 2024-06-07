//
//  ExeTimer.hpp
//  cpplibs
//
//  Created by Sean Grimes on 11/30/15.
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#ifndef ExeTimer_hpp
#define ExeTimer_hpp

#include <chrono>
#include <iostream>

using time_device = std::chrono::system_clock;
using time_p = std::chrono::system_clock::time_point;

class ExeTimer{
public:
    void start_timer();
    void stop_timer();
    double get_exe_time_in_sec();
    double get_exc_time_in_ms();
    double get_exe_time_in_micro();
    double get_exe_time_in_nano();
   
private:
    time_p _start;
    time_p _stop;
    double _exe_time_sec{};
    double _exe_time_ms{};
    double _exe_time_micro{};
    double _exe_time_ns{};
};

#endif /* ExeTimer_hpp */
