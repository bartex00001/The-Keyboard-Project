#pragma once

#include <cstdint>

#include <KeyboardDriver/Key.hpp>
#include <KeyboardDriver/UsbHidKeys.hpp>

namespace KeyMatrix
{

void initKeyMatrix();
void scanKeyMatrix();

} // namespace KeyMatrix
