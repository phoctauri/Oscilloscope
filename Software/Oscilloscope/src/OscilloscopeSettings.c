#include "OscilloscopeSettings.h"

OSC_Settings_IntegerContinuousValue_Type   OSC_Settings_IntegerContinuousCallback_Default(OSC_Settings_IntegerContinuous_Type*  this,
                                                                                          OSC_Settings_Event_Type               settingsEvent)
{
  if(this == NULL) return ~0;
  switch(settingsEvent){
    case OSC_Settings_Event_StepUpSingle:
      if((this->value + this->incrementStepSingle) > this->upperBound){
        this->value = this->upperBound;
      } else {
        this->value += this->incrementStepSingle;
      }
      break;
    case OSC_Settings_Event_StepUpMultiple:
      if((this->value + this->incrementStepMultiple) > this->upperBound){
        this->value = this->upperBound;
      } else {
        this->value += this->incrementStepMultiple;
      }
      break;
    case OSC_Settings_Event_StepDownSingle:
      if((this->value - this->incrementStepSingle) < this->lowerBound){
        this->value = this->lowerBound;
      } else {
        this->value -= this->incrementStepSingle;
      }
      break;
    case OSC_Settings_Event_StepDownMultiple:
      if((this->value - this->incrementStepMultiple) < this->lowerBound){
        this->value = this->lowerBound;
      } else {
        this->value -= this->incrementStepMultiple;
      }
      break;
    default: return ~0;
  }
  return this->value;
}

OSC_Settings_IntegerDiscreteIndex_Type     OSC_Settings_IntegerDiscreteCallback_Default(OSC_Settings_IntegerDiscrete_Type*      this,
                                                                                        OSC_Settings_Event_Type                 settingsEvent)
{
  if(this == NULL) return ~0;
  switch(settingsEvent){
    case OSC_Settings_Event_StepUpSingle:
    case OSC_Settings_Event_StepUpMultiple:
      this->currentIndex = ((this->currentIndex + 1) < this->length) ? this->currentIndex + 1: 0;
      break;

    case OSC_Settings_Event_StepDownSingle:
    case OSC_Settings_Event_StepDownMultiple:
      this->currentIndex = ((this->currentIndex == 0)? this->length : this->currentIndex) - 1;
      break;
    default: return ~0;
  }
  return this->currentIndex;
}

OSC_Settings_OnOffValue_Type               OSC_Settings_OnOffCallback_Default(OSC_Settings_OnOff_Type*                          this,
                                                                              OSC_Settings_Event_Type                           settingsEvent)
{
  if(this == NULL) return ~0;
  switch(settingsEvent){
    case OSC_Settings_Event_StepUpSingle:
    case OSC_Settings_Event_StepUpMultiple:
    case OSC_Settings_Event_StepDownSingle:
    case OSC_Settings_Event_StepDownMultiple:
      this->status = !this->status;
      break;
    default: return ~0;
  }
  return this->status;
}

OSC_Settings_OptionValue_Type              OSC_Settings_OptionCallback_Default(OSC_Settings_Option_Type*                        this,
                                                                               OSC_Settings_Event_Type                          settingsEvent)
{
  if(this == NULL) return ~0;
  switch(settingsEvent){
    case OSC_Settings_Event_StepUpSingle:
    case OSC_Settings_Event_StepUpMultiple:
      if(this->optionID == (this->optionCount - 1)){
        this->optionID = 0;
      } else {
        this->optionID++;
      }
      break;
    case OSC_Settings_Event_StepDownSingle:
    case OSC_Settings_Event_StepDownMultiple:
      if(this->optionID == 0){
        this->optionID = this->optionCount - 1;
      } else {
        this->optionID--;
      }
      break;
    default: return ~0;
  }
  return this->optionID;
}

void  OSC_Settings_StringBuilder(OSC_Settings_Type* menuElement,char* strDest){
  char strTemp[OSC_SETTINGS_TEXT_CHARACTER_BUFFER_SIZE];
  const char menuTextFormat[] = "%-13s%8s";

  switch(menuElement->typeInfo){
    case OSC_Settings_TypeInfo_IntegerContinuous:
      snprintf(strTemp,OSC_SETTINGS_TEXT_CHARACTER_BUFFER_SIZE,"%d%s",
              (int)((OSC_Settings_IntegerContinuous_Type*)menuElement->settingsDataPtr)->value,
              (char*)((OSC_Settings_IntegerContinuous_Type*)menuElement->settingsDataPtr)->unitName);
      snprintf(strDest,OSC_SETTINGS_TEXT_CHARACTER_BUFFER_SIZE,menuTextFormat,
             (char*)((OSC_Settings_IntegerContinuous_Type*)menuElement->settingsDataPtr)->name, strTemp);
      break;
    case OSC_settings_TypeInfo_IntegerDiscrete:
      snprintf(strDest,OSC_SETTINGS_TEXT_CHARACTER_BUFFER_SIZE,menuTextFormat,
             (char*)((OSC_Settings_IntegerDiscrete_Type*)menuElement->settingsDataPtr)->name,
             (char*)((OSC_Settings_IntegerDiscrete_Type*)menuElement->settingsDataPtr)->nameOfValues
             [((OSC_Settings_IntegerDiscrete_Type*)menuElement->settingsDataPtr)->currentIndex]);
      break;
    case OSC_Settings_TypeInfo_OnOff:
      snprintf(strDest,OSC_SETTINGS_TEXT_CHARACTER_BUFFER_SIZE,menuTextFormat,
              (char*)((OSC_Settings_OnOff_Type*)menuElement->settingsDataPtr)->name,
              (char*)((OSC_Settings_OnOff_Type*)menuElement->settingsDataPtr)->statusNames
              [((OSC_Settings_OnOff_Type*)menuElement->settingsDataPtr)->status]);
      break;
    case OSC_Settings_TypeInfo_Option:
      snprintf(strDest,OSC_SETTINGS_TEXT_CHARACTER_BUFFER_SIZE,menuTextFormat,
              (char*)((OSC_Settings_Option_Type*)menuElement->settingsDataPtr)->name,
              (char*)((OSC_Settings_Option_Type*)menuElement->settingsDataPtr)->nameOfOptions
              [((OSC_Settings_Option_Type*)menuElement->settingsDataPtr)->optionID]);
      break;
  }
}
