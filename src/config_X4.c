/* 
Copyright 2014 Goebish

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bradwii.h"
#include "config_X4.h"

extern usersettingsstruct usersettings;

/* The Hubsan X4 does not have a serial port to connect it
   to a GUI such as MultiwiiConfig GUI, settings are configured
   from here until a better solution is found */
void x4_set_usersettings()
{
    // set acro mode rotation rates
    usersettings.maxyawrate = 600L << FIXEDPOINTSHIFT;  // degrees per second
    usersettings.maxpitchandrollrate = 400L << FIXEDPOINTSHIFT; // degrees per second
    
    // pitch PIDs
    usersettings.pid_pgain[PITCHINDEX] = 15L << 3;   // 1.5 on configurator
    usersettings.pid_igain[PITCHINDEX] = 8L; // .008 on configurator
    usersettings.pid_dgain[PITCHINDEX] = 8L << 2;    // 8 on configurator

    // roll PIDs
    usersettings.pid_pgain[ROLLINDEX] = 15L << 3;   // 1.5 on configurator
    usersettings.pid_igain[ROLLINDEX] = 8L; // .008 on configurator
    usersettings.pid_dgain[ROLLINDEX] = 8L << 2;    // 8 on configurator

    // yaw PIDs
    usersettings.pid_pgain[YAWINDEX] = 30L << 3;   // 3.0 on configurator
    usersettings.pid_igain[YAWINDEX] = 8L; // .008 on configurator
    usersettings.pid_dgain[YAWINDEX] = 8L << 2;    // 8 on configurator

    for (int x = 0; x < NUMPOSSIBLECHECKBOXES; ++x) {
        usersettings.checkboxconfiguration[x] = 0;
    }
    
    // flight modes, see checkboxes.h for a complete list
    
    // set fullacro flight mode (gyro only) for  AUX1 high (LEDs on/off channel on stock TX)
    // default for H107L, H107C & H107D stock TXs
    usersettings.checkboxconfiguration[CHECKBOXFULLACRO] = CHECKBOXMASKAUX1HIGH; // rate mode (gyro only)
    //usersettings.checkboxconfiguration[CHECKBOXHIGHRATES] = CHECKBOXMASKAUX1HIGH; // uncommentr for high rates
    
    // set semiacro flight mode for AUX1 low
    // default for H107 stock TX 
    usersettings.checkboxconfiguration[CHECKBOXSEMIACRO] = CHECKBOXMASKAUX1LOW;
    //usersettings.checkboxconfiguration[CHECKBOXHIGHANGLE] = CHECKBOXMASKAUX1LOW; // uncomment for high angle
}

void x4_init_leds()
{
    lib_digitalio_initpin(LED1_OUTPUT, DIGITALOUTPUT);	
    lib_digitalio_initpin(LED2_OUTPUT, DIGITALOUTPUT);
    lib_digitalio_initpin(LED5_OUTPUT, DIGITALOUTPUT);
    lib_digitalio_initpin(LED6_OUTPUT, DIGITALOUTPUT);
}

void x4_set_leds(unsigned char state)
{
    lib_digitalio_setoutput( LED1_OUTPUT , state ? LED1_ON : !LED1_ON);
	lib_digitalio_setoutput( LED2_OUTPUT , state ? LED2_ON : !LED2_ON);
	lib_digitalio_setoutput( LED5_OUTPUT , state ? LED5_ON : !LED5_ON);
 	lib_digitalio_setoutput( LED6_OUTPUT , state ? LED6_ON : !LED6_ON);
}

