/* model.c -- actual clock part of the clock project
 *
 * Darren Provine, 17 July 2009
 */

#include "clock.h"

/* MODEL */

/* Set up an interval timer for our clock.
 * This is the "Model" of "Model-View-Controller"; it's what
 * ctually measures real time passing.
 *
 * When the interval is over, the tick() function will be executed,
 * which is part of the Controller for this program.
 */
void start_timer()
{
    struct itimerval interval; // interval object
    struct sigaction new_action, old_action;  // signal actions

    // See the manual entry for signal.h(0P) for a list of all signals.

    // blank out the signal mask
    sigemptyset( &new_action.sa_mask );
    // clear flags (our application is pretty simple)
    new_action.sa_flags = 0;
    // set tick() as the signal handler when we get the timer signal.
    new_action.sa_handler = tick;
 
    // sigaction takes a pointer as an argument, so you have to
    // allocate space.  The declaration of new_action and old_action
    // up above have no stars - those are objects, not just pointers.
    if ( sigaction(SIGALRM, &new_action, &old_action) == -1 ) {
        perror("Could not set new handler for SIGALRM");
        exit(1);
    }

    // set interval to 1.000 seconds.
    interval.it_value.tv_sec  = 1;   // seconds
    interval.it_value.tv_usec = 0;   // microseconds
    interval.it_interval = interval.it_value;

    // set a timer for the real time clock using the interval object
    // NOTE: takes a pointer, so no * in our declaration of "interval"
    setitimer(ITIMER_REAL, &interval, NULL);
}
