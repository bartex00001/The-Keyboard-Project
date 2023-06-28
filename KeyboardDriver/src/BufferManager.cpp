#include <bsp/board.h>
#include <tusb.h>

#include "KeyboardDriver/BufferManager.hpp"
#include "KeyboardDriver/UsbHidKeys.hpp"
#include "KeyboardDriver/usbDescriptors.hpp"

namespace BufferManager
{
std::uint8_t keyBuffer[6]{};
std::uint8_t modifiers;
unsigned short encodedKeys{};

enum KeyState {
    CLEAR = 0,
    CLEAR_KEYS = 1,
    SEND_KEYS = 2
} keyState{};

void clearBuffer()
{
    std::memset(keyBuffer, 0, sizeof(keyBuffer));
    modifiers = 0;
    encodedKeys = 0;
}

void addKey(const Key &key)
{
    keyState = KeyState::SEND_KEYS;
    modifiers |= key.modifiers;

    if(encodedKeys >= 6)
        return;
    
    if(key.code == KEY_NONE)
        return;

    keyBuffer[encodedKeys] = key.code;
    encodedKeys++;
}

void sendReport()
{
    if(tud_suspended() && keyState)
        tud_remote_wakeup();

    if(!tud_hid_ready())
        return;

    if(keyState == KeyState::SEND_KEYS)
    {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifiers, keyBuffer);
        keyState = KeyState::CLEAR_KEYS;
    }
    else if(keyState == KeyState::CLEAR_KEYS)
    {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, nullptr);
        keyState = KeyState::CLEAR;
    }
}

void fillBuffer(std::uint8_t* buffer)
{
    buffer[0] = modifiers;
    std::memcpy(buffer+2, keyBuffer, sizeof(keyBuffer));
}

}