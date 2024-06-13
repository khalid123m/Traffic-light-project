/**
 * @file rc_test_buttons.c
 * @example    rc_test_buttons
 *
 * This is a very basic test of button functionality. It simply prints to the
 * screen when a button has been pressed or released.
 **/
#include <stdio.h>
#include <signal.h>
#include <rc/button.h>
#include <rc/time.h>
#include <robotcontrol.h>
//static int running = 0;
//
static int i=0;
static int j=0;
static int k=0;
//defining what needs to be done when pause button is pressed 
static void __on_pause_press(void)
{      
    rc_set_state(RUNNING); //when pause button is pressed it will set to runing state
    printf("RUNNING\n");// print running
    return;    
     
}

//defining what needs to be done when mode button is pressed
static void __on_mode_press(void)
{
        //Basically we are saying that when mode button is pressed it should stop 
        //--continued all the running led's other stuff from while loop to stop and exit the program
                if(rc_get_state()==RUNNING){ //if the status is running?
                rc_set_state(PAUSED);// change it to pause,to check what happens when you set it to pause (refer to while loop in the main function)
                printf("exiting\n");//print exiting
        }
        
        fflush(stdout);
        return;	

}


int main()
{
        static long int usleep;
    // make sure another instance isn't running
        // if return value is -3 then a background process is running with
        // higher privaledges and we couldn't kill it, in which case we should
        // not continue or there may be hardware conflicts. If it returned -4
        // then there was an invalid argument that needs to be fixed.
        if(rc_kill_existing_process(2.0)<-2) return -1;
        // start signal handler so we can exit cleanly
        if(rc_enable_signal_handler()<0){
                fprintf(stderr,"ERROR: failed to complete rc_enable_signal_handler\n");
                return -1;
        }
        // initialize pause and mode buttons
        if(rc_button_init(RC_BTN_PIN_PAUSE, RC_BTN_POLARITY_NORM_HIGH,
                                                RC_BTN_DEBOUNCE_DEFAULT_US)){
                fprintf(stderr,"ERROR: failed to init buttons\n");
                return -1;
        }
        if(rc_button_init(RC_BTN_PIN_MODE, RC_BTN_POLARITY_NORM_HIGH,
                                                RC_BTN_DEBOUNCE_DEFAULT_US)){
                fprintf(stderr,"ERROR: failed to init buttons\n");
                return -1;
        }
       
        // Assign callback functions
        rc_button_set_callbacks(RC_BTN_PIN_PAUSE,__on_pause_press,NULL);
        rc_button_set_callbacks(RC_BTN_PIN_MODE, __on_mode_press,NULL);
        //start with all LEDs off so in our case it is red,green,user0,user1,user2,user3;
        printf("Press buttons to see response\n");
if(rc_led_set(RC_LED_RED, 0)==-1){
                fprintf(stderr, "ERROR in rc_blink, failed to set RC_LED_RED\n");
                return -1;
        }
if(rc_led_set(RC_LED_GREEN, 0)==-1){
                fprintf(stderr, "ERROR in rc_blink, failed to set RC_LED_GREEN\n");
                return -1;
        }
if(rc_led_set(RC_LED_USR0, 0)==-1){
                fprintf(stderr, "ERROR in rc_blink, failed to set RC_LED_GREEN\n");
                return -1;
        } 
if(rc_led_set(RC_LED_USR1, 0)==-1){
                fprintf(stderr, "ERROR in rc_blink, failed to set RC_LED_GREEN\n");
                return -1;
        }
if(rc_led_set(RC_LED_USR2, 0)==-1){
                fprintf(stderr, "ERROR in rc_blink, failed to set RC_LED_GREEN\n");
                return -1;
        }
if(rc_led_set(RC_LED_USR3, 0)==-1){
                fprintf(stderr, "ERROR in rc_blink, failed to set RC_LED_GREEN\n");
                return -1;
        } 
 //Initialize all GPIO pins or LEDs if you want to show led is glowing on breadboard it should be set to "GPIOHANDLE_REQUEST_OUTPUT"                                        
rc_gpio_init(3,1,GPIOHANDLE_REQUEST_OUTPUT);
rc_gpio_init(3,17,GPIOHANDLE_REQUEST_OUTPUT);
rc_gpio_init(3,20,GPIOHANDLE_REQUEST_OUTPUT);
rc_gpio_init(1,17,GPIOHANDLE_REQUEST_OUTPUT);
// make PID file to indicate your project is running
        // due to the check made on the call to rc_kill_existing_process() above
        // we can be fairly confident there is no PID file already and we can
        // make our own safely.
        rc_make_pid_file();
        
printf("Press buttons to see response\n");
        while(rc_get_state()!=EXITING){
                // if the state is RUNNING (instead of PAUSED) then blink!
                if(rc_get_state()==RUNNING)// "set rc_get_state" to "running" so the program can start
                {
                   
              for(k=0;k<2;k++)     //initialize 'for-loop' using 'k' for changing one traffic signal(pair of three leds ) to another traffic signal 
                   { 
                           
                   if (k==0){       // first signal lets say for North-south direction
                   for(j=0;j<3;j++){ //start a 'for-loop' for 'Green-10seconds', 'yellow-4seconds','red-2seconds'
                    if(j==0)  //first state nothing but for 'green-10seconds' 
                    {
                        
                       for(i=0;i<10;i++) //initialize this 'for-loop'using 'i' for number of seconds because we can not exceet more than a second(1000000) in 'rc_usleep' which is used for delay 
                       {
                        rc_led_set(RC_LED_GREEN,1);
                        rc_led_set(RC_LED_RED,0);
                        rc_gpio_set_value(3,1,0);
                        rc_gpio_set_value(3,17,1);
                        rc_gpio_set_value(3,20,0);
                        rc_gpio_set_value(1,17,0);
                        rc_led_set(RC_LED_USR0,0);
                        rc_led_set(RC_LED_USR1,0);
                        rc_led_set(RC_LED_USR2,0);
                        rc_led_set(RC_LED_USR3,1);
                        rc_usleep(1000000);
                       } 
                       j++;  //increment to next state i.e go to 'yellow-4seconds'
                          
                    }
                   if(j==1) //second state = 'yellow-4seconds' 
                   {
                       for(i=0;i<4;i++)
                       {
                        rc_led_set(RC_LED_GREEN,0);//set green led to off
                        rc_led_set(RC_LED_RED,0);//set red led to off
                        rc_gpio_set_value(3,1,1);//set chip-3,pin-1 led to on from 'gpio-1'
                        rc_gpio_set_value(3,17,1);//set chip-3,pin-17 led to on
                        rc_gpio_set_value(3,20,0);//set chip-3,pin-20 led to off
                        rc_gpio_set_value(1,17,0);//set chip-1,pin-17 led to off
                        rc_led_set(RC_LED_USR0,1);//set user0 led to off
                        rc_led_set(RC_LED_USR1,0);//set user1 led to off
                        rc_led_set(RC_LED_USR2,0);//set user2 led to off
                        rc_led_set(RC_LED_USR3,1);//set user3 led to on

                        rc_usleep(1000000);
                        
                        }
                        
                        j++;
                        
                    }
                    if(j==2)//state = 'red-2seconds'
                    {
                        
                       for(i=0;i<2;i++)
                       {
                        rc_led_set(RC_LED_GREEN,0);
                        rc_led_set(RC_LED_RED,1);
                        rc_gpio_set_value(3,1,0);
                        rc_gpio_set_value(3,17,1);
                        rc_gpio_set_value(3,20,0);
                        rc_gpio_set_value(1,17,0);
                        rc_led_set(RC_LED_USR0,0);
                        rc_led_set(RC_LED_USR1,0);
                        rc_led_set(RC_LED_USR2,0);
                        rc_led_set(RC_LED_USR3,1);
                        rc_usleep(1000000);
                        
                        }
                     
                    }
                   }
                           }k++;


                           if (k==1){ //// second signal let's say for west-east direction

                   for(j=0;j<3;j++){
                    if(j==0)
                    {
                        
                       for(i=0;i<10;i++)
                       {
                        rc_led_set(RC_LED_GREEN,0);
                        rc_led_set(RC_LED_RED,1);
                        rc_gpio_set_value(3,1,0);
                        rc_gpio_set_value(3,17,0);
                        rc_gpio_set_value(3,20,0);
                        rc_gpio_set_value(1,17,1);
                        rc_led_set(RC_LED_USR0,0);
                        rc_led_set(RC_LED_USR1,1);
                        rc_led_set(RC_LED_USR2,0);
                        rc_led_set(RC_LED_USR3,0);
                        rc_usleep(1000000);
                       } 
                       j++; 
                   
                   
                   
                   
                    }
                   if(j==1)
                   {
                       for(i=0;i<4;i++)
                       {
                        rc_led_set(RC_LED_GREEN,0);
                        rc_led_set(RC_LED_RED,1);
                        rc_gpio_set_value(3,1,0);
                        rc_gpio_set_value(3,17,0);
                        rc_gpio_set_value(3,20,1);
                        rc_gpio_set_value(1,17,0);
                        rc_led_set(RC_LED_USR0,0);
                        rc_led_set(RC_LED_USR1,0);
                        rc_led_set(RC_LED_USR2,1);
                        rc_led_set(RC_LED_USR3,0);
                        rc_usleep(1000000);
                        
                        }
                        
                        j++;
                        
                    }
                    if(j==2)
                    {
                        
                       for(i=0;i<2;i++)
                       {
                        rc_led_set(RC_LED_GREEN,0);
                        rc_led_set(RC_LED_RED,1);
                        rc_gpio_set_value(3,1,0);
                        rc_gpio_set_value(3,17,1);
                        rc_gpio_set_value(3,20,0);
                        rc_gpio_set_value(1,17,0);
                        rc_led_set(RC_LED_USR0,0);
                        rc_led_set(RC_LED_USR1,0);
                        rc_led_set(RC_LED_USR2,0);
                        rc_led_set(RC_LED_USR3,1);
                        rc_usleep(1000000);
                        
                        }
                     
                    }
                   }
                   }


                }  
                 // now that the while loop has exited, clean up neatly and exit compeltely.
                if(rc_get_state()==PAUSED)
                {
                    rc_led_set(RC_LED_GREEN, 0);
                    rc_led_set(RC_LED_RED, 0);
                    rc_gpio_set_value(3,1,0);
                    rc_gpio_set_value(3,17,0);
                    rc_gpio_set_value(3,20,0);
                    rc_gpio_set_value(1,17,0);
                    rc_led_set(RC_LED_USR0,0);
                    rc_led_set(RC_LED_USR1,0);
                    rc_led_set(RC_LED_USR2,0);
                    rc_led_set(RC_LED_USR3,0);
                    rc_led_cleanup();
                    rc_button_cleanup();
                    rc_remove_pid_file();
                    return 0;
                    
                } 
        
        }
        
        
       // rc_usleep(100000);
        }
       
       
        

}