#include "OscilloscopeNotification.h"

void OSC_Notification_PrintAll(void){
  uint32_t index;

  OSC_Settings_StringBuilder(&OSC_Settings_TriggerLevel,OSC_Notification_Info[0]);
  OSC_Settings_StringBuilder(&OSC_Settings_TriggerPosition,OSC_Notification_Info[1]);
  OSC_Settings_StringBuilder(&OSC_Settings_HorizontalResolution,OSC_Notification_Info[2]);
  OSC_Settings_StringBuilder(&OSC_Settings_HorizontalOffset,OSC_Notification_Info[3]);
  OSC_Settings_StringBuilder(&OSC_Settings_VerticalResolution,OSC_Notification_Info[4]);
  OSC_Settings_StringBuilder(&OSC_Settings_VerticalOffset,OSC_Notification_Info[5]);

  for (index = 0; index < OSC_DM_TEXT_LINE_COUNT; ++index) {
    OSC_DisplayManager_Text_PrintLine(OSC_Notification_Info[index],index,OSC_DisplayManager_PrintMode_Positive);
  }
}