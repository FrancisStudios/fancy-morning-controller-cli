/**
 *  ------ [ Property of Francis Studios ] ------
 * ==============================================
 * This is an open source project, feel free to use
 * .. github:https://github.com/francisstudios ..
 * ____ ©2025 Francis Studios Softwares by L. ___
 */

#ifndef HEADLESS_H
#define HEADLESS_H

#pragma once
#include <stdio.h>
#include "../lib/serialib.h"
#include "./util.h"
#include <chrono>
#include <thread>

namespace FancyHeadless
{
    void dispatch(char *serialPortId, char *arg);
    void headlessConnectionTest(char *serialPortId);
}

#endif