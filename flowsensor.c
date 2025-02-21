#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//flowsensor.c
// This C code is a complete line-by-line translation of the provided Python code.

#define FLOW_SENSOR 23

volatile int count = 0;
volatile int start_counter = 0;

void countPulse(void) {
   // global count is used similarly to the Python version
   if (start_counter == 1) {
      count = count + 1;
      //      printf("%d\n", count);
      //      float flow = count / (60.0 * 7.5);
      //      printf("%f\n", flow);
   }
}

void sig_handler(int signum) {
   // Catch KeyboardInterrupt equivalent, print message and exit
   printf("\ncaught keyboard interrupt!, bye\n");
   // In wiringPi, no explicit GPIO cleanup is needed as in RPi.GPIO
   exit(0);
}

int main(void) {
   // Set up signal handler for SIGINT to mimic KeyboardInterrupt handling
   signal(SIGINT, sig_handler);

   // Set the GPIO numbering to BCM equivalent using wiringPiSetupGpio()
   if (wiringPiSetupGpio() == -1) {
      printf("Unable to start wiringPi\n");
      exit(1);
   }
   
   // Setup FLOW_SENSOR pin as input with pull-up resistor to mimic GPIO.setup(FLOW_SENSOR, GPIO.IN, pull_up_down = GPIO.PUD_UP)
   pinMode(FLOW_SENSOR, INPUT);
   pullUpDnControl(FLOW_SENSOR, PUD_UP);
   
   // Set up event detection on FLOW_SENSOR pin for falling edge to call countPulse (mimicking GPIO.add_event_detect)
   if (wiringPiISR(FLOW_SENSOR, INT_EDGE_FALLING, &countPulse) < 0) {
      printf("Unable to setup ISR\n");
      exit(1);
   }
   
   while (1) {
      // Mimic try block in Python
      start_counter = 1;
      sleep(1);
      start_counter = 0;
      float flow = (count * 60 * 2.25) / 1000.0;
      printf("The flow is: %.3f Liter/min\n", flow);
      count = 0;
      sleep(5);
   }
   
   return 0;
}
