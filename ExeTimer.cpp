//
//  ExeTimer.cpp
//  cpplibs
//
//  Created by Sean Grimes on 11/30/15.
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#include "ExeTimer.hpp"

void ExeTimer::start_timer(){
    _start = time_device::now();
}

void ExeTimer::stop_timer(){
    _stop = time_device::now();
}

double ExeTimer::get_exe_time_in_sec(){
    auto duration = _stop - _start;
    _exe_time_sec = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    return _exe_time_sec;
}

double ExeTimer::get_exc_time_in_ms(){
    auto duration = _stop - _start;
    _exe_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return _exe_time_ms;
}

double ExeTimer::get_exe_time_in_micro(){
    auto duration = _stop - _start;
    _exe_time_micro = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    return _exe_time_micro;
}

double ExeTimer::get_exe_time_in_nano(){
    auto duration = _stop - _start;
    _exe_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    return _exe_time_ns;
}