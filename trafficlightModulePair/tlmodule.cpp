/* TRAFFIC LIGHT MODULE MODULE */

#include "tlmodule.h"
// To support NULL we need this header
#include <stddef.h>

void tlControlReset(tlModule *userTlModule) {
  userTlModule->tlState = Reset;
}

void tlControlInit(tlModule *userTlModule) {
  // Put state machine in reset
  userTlModule->tlState = Reset;

  // Init all function pointers to NULL
  userTlModule->tlLampControl = NULL;
  userTlModule->tlWait = NULL;

  // Set phase timings to defaults
  userTlModule->tlPhaseTiming.timePhaseOne = 3000;
  userTlModule->tlPhaseTiming.timePhaseTwo = 750;
  userTlModule->tlPhaseTiming.timePhaseThree = 3000;
  userTlModule->tlPhaseTiming.timePhaseFour = 1000;
}

/* Core traffic light control module */
void tlControl(tlModule *userTlModule) {
  switch (userTlModule->tlState) {
  case Reset:
    userTlModule->tlLampControl(tlRed, false);
    userTlModule->tlLampControl(tlAmber, false);
    userTlModule->tlLampControl(tlGreen, false);
    userTlModule->tlState = Phase_One;
    break;
      
  case Phase_One:
    userTlModule->tlLampControl(tlAmber, false);
    userTlModule->tlLampControl(tlRed, true);
    userTlModule->tlWait(userTlModule->tlPhaseTiming.timePhaseOne);
    userTlModule->tlState = Phase_Two;
    break;
      
  case Phase_Two:
    userTlModule->tlLampControl(tlAmber, true);
    userTlModule->tlWait(userTlModule->tlPhaseTiming.timePhaseTwo);
    userTlModule->tlState = Phase_Three;
    break;
      
  case Phase_Three:
    userTlModule->tlLampControl(tlRed, false);
    userTlModule->tlLampControl(tlAmber, false);
    userTlModule->tlLampControl(tlGreen, true);
    userTlModule->tlWait(userTlModule->tlPhaseTiming.timePhaseThree);
    userTlModule->tlState = Phase_Four;
    break;
      
  case Phase_Four:
    userTlModule->tlLampControl(tlGreen, false);
    userTlModule->tlLampControl(tlAmber, true);
    userTlModule->tlWait(userTlModule->tlPhaseTiming.timePhaseFour);
    userTlModule->tlState = Phase_One;
    break;
      
  default:
    break;
  }
}
