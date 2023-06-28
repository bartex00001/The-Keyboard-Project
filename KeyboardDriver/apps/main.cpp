#include <cstdint>
#include <cstdio>

#include <pico/stdlib.h>
#include <bsp/board.h>
#include <tusb.h>

#include "KeyboardDriver/usbDescriptors.hpp"
#include "KeyboardDriver/UsbHidKeys.hpp"
#include "KeyboardDriver/KeyMatrix.hpp"
#include "KeyboardDriver/BufferManager.hpp"

int main()
{
    board_init();
    tusb_init();

    KeyMatrix::initKeyMatrix();

    while(true)
    {
        BufferManager::clearBuffer();
        sleep_ms(10); // Wait before next scan

        tud_task(); // tinyusb device task

        for(int i{}; i < KeyMatrix::outputLinesCount; i++)
        {
            gpio_put(KeyMatrix::outputLines[i], 1);

            sleep_us(1); // Wait for the diodes to switch

            for(int j{}; j < KeyMatrix::inputLinesCount; j++)
            {
                if(gpio_get(KeyMatrix::inputLines[j]))
                {
                    BufferManager::addKey(KeyMatrix::keyMatrix[j][i]);
                }
            }
            gpio_put(KeyMatrix::outputLines[i], 0);
        }
        
        BufferManager::sendReport();
    }

    return 0;
}

// Invoked when received SET_PROTOCOL request
void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol)
{
    (void) instance;
    (void) protocol;

    // Nothing to do 'cause we always use boot protocol (for best compatibility)
}

// Invoked when sent REPORT successfully to host
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) report;
  (void) len;

  // nothing to do (we only send one report)
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    (void) instance;
    (void) report_type;
    (void) reqlen;

    if(report_id != REPORT_ID_KEYBOARD)
        return 0;

    BufferManager::fillBuffer(buffer);

    return 8;
}

// Invoked when received SET_REPORT control request or 
// received data on OUT endpoint (report_id == 0)
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}
