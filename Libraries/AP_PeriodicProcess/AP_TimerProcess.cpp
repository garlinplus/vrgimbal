/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include "AP_TimerProcess.h"
#include <wirish.h>

extern "C" {
#include <inttypes.h>
#include <stdint.h>
//#include "WConstants.h"
//#include <avr/interrupt.h>
}

uint8_t AP_TimerProcess::_period;
ap_procedure AP_TimerProcess::_proc[AP_TIMERPROCESS_MAX_PROCS];
ap_procedure AP_TimerProcess::_failsafe;
bool AP_TimerProcess::_in_timer_call;
uint8_t AP_TimerProcess::_pidx = 0;
bool AP_TimerProcess::_suspended;

AP_TimerProcess::AP_TimerProcess(uint8_t period)
{
    _period = period;
}

void AP_TimerProcess::init( Arduino_Mega_ISR_Registry * isr_reg )
{

    Timer2.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer2.setPeriod(_period); // in microseconds
    Timer2.setCompare1(1);      // overflow might be small
    Timer2.attachCompare1Interrupt(&(isr_reg->ISR_TIMER2_OVF_vect));

    _failsafe = NULL;
    _suspended = false;
	_in_timer_call = false;

	for (uint8_t i = 0; i < AP_TIMERPROCESS_MAX_PROCS; i++)
		_proc[i] = NULL;

	isr_reg->register_signal( ISR_REGISTRY_TIMER2_OVF, AP_TimerProcess::run);
}

/*
  register a process to be called at the timer interrupt rate
 */
void AP_TimerProcess::register_process(ap_procedure proc)
{
    // see if its already registered (due to double initialisation
    // of a driver)
    for (uint8_t i=0; i<_pidx; i++) {
        if (_proc[i] == proc) return;
    }
    noInterrupts();
    if (_pidx < AP_TIMERPROCESS_MAX_PROCS)
        _proc[_pidx++] = proc;
    interrupts();
}

void AP_TimerProcess::set_failsafe(ap_procedure proc)
{
	_failsafe = proc;
}

void AP_TimerProcess::suspend_timer(void)
{
	_suspended = true;
}

void AP_TimerProcess::resume_timer(void)
{
	_suspended = false;
}

void AP_TimerProcess::run(void)
{
	// we enable the interrupt again immediately and also enable
	// interrupts. This allows other time critical interrupts to
	// run (such as the serial receive interrupt). We catch the
	// timer calls taking too long using _in_timer_call. 
	// This approach also gives us a nice uniform spacing between
	// timer calls

	Timer2.pause();
	Timer2.setPeriod(_period); // in microseconds
	Timer2.resume();

	uint32_t tnow = micros();

	if (_in_timer_call) {
		// the timer calls took longer than the period of the
		// timer. This is bad, and may indicate a serious
		// driver failure. We can't just call the drivers
		// again, as we could run out of stack. So we only
		// call the _failsafe call. It's job is to detect if
		// the drivers or the main loop are indeed dead and to
		// activate whatever failsafe it thinks may help if
		// need be.  We assume the failsafe code can't
		// block. If it does then we will recurse and die when
		// we run out of stack
		if (_failsafe != NULL) {
			_failsafe(tnow);
		}
		return;
	}
	_in_timer_call = true;

    if (!_suspended) {
	// now call the timer based drivers
	for (int i = 0; i < _pidx; i++) {
		if (_proc[i] != NULL) {
			_proc[i](tnow);
            }
		}
	}

	// and the failsafe, if one is setup
	if (_failsafe != NULL) {
		_failsafe(tnow);
	}

	_in_timer_call = false;
}
