/* TRAFFIC LIGHT MODULE MODULE STARTS */
#ifndef __TRAFFICLIGHTMODULE_PRESENT__
#define __TRAFFICLIGHTMODULE_PRESENT__

// Definitions of all the bits of the module

// Traffic light phases for state machine
typedef enum {
    Reset,
    Phase_One,
    Phase_Two,
    Phase_Three,
    Phase_Four
} trafficLightState;

// Traffic light phase timing
typedef struct tlPhaseTiming {
   int timePhaseOne;
   int timePhaseTwo;
   int timePhaseThree;
   int timePhaseFour;
} tlPhaseTime;

//LED Decoupling
typedef enum {
    tlRed,
    tlAmber,
    tlGreen
} tlLamps;

// Variable definition to store state of an entire traffic light
typedef struct tlModuleTag {
  // Unique state of user's traffic light
  trafficLightState tlState;
  // Unique phase timing for user's traffic lights
  tlPhaseTime tlPhaseTiming;
  // Pointer to user's "LED control" function
  void (*tlLampControl)(int, bool);
  // Pointer to user's "delay" function
  void (*tlWait)(int);
} tlModule;

// Interface for the user
void tlControl(tlModule *userTlModule);
void tlControlReset(tlModule *userTlModule);
void tlControlInit(tlModule *userTlModule);

/* TRAFFIC LIGHT MODULE MODULE ENDS */
#endif
