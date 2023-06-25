#include <cstdint>
#include <cstdio>

#include <pico/stdlib.h>
#include <bsp/board.h>
#include <tusb.h>

#include "KeyboardDriver/usbDescriptors.hpp"
#include "KeyboardDriver/UsbHidKeys.hpp"

int main()
{
    board_init();
    tusb_init();

    while(true)
    {   
        tud_task();
        
        if(tud_suspended())
        {
            tud_remote_wakeup();
        }
        else
        {
            if(tud_hid_ready())
            {
                const std::uint8_t modifier{0};
                uint8_t keycode[6]{0};

                keycode[0] = KEY_A;

                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);

                sleep_ms(10);

                tud_task();
                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, nullptr);
                
                sleep_ms(1000);
            }
        }
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
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
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
