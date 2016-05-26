#ifndef CAN_MESSAGE_DEF_H
#define CAN_MESSAGE_DEF_H

/*
 * Message ID format (11 bits)
 *  Bit [2-0] store the message data type
 *  Bit [4-3] device id
 *  Bit [8-5] message id
 *  Bit [10-9] priority level
 *    0 - mission critical
 *    1 - important
 *    2 - information
 *    3 - logging
 */

namespace can_msg {
  /*
   * message type
   */
  typedef enum {
    BOOL = 0,
    INT8 = 1,
    UINT8 = 2,
    INT16 = 3,
    UINT16 = 4,
    INT32 = 5,
		UINT32 = 6,
  } format_t;

  /*
   * device ids
   */
  typedef enum {
    FUEL_CELL = 0,
    MOTOR = 1,
    AUX = 2,
		OTHER = 3
  } device_t;

  /*
   * priority
   */
  typedef enum {
    CRITICAL = 0,
    IMPORTANT = 1,
    INFORMATION = 2,
    LOGGING = 3
  } priority_t;

  /*
   * Fuel cell
   */
   //to do: reorder so that levels have higher priority
  typedef enum {
    //purge data
    FC_ERROR = 0,                       //len 1 [fc_errors_t] BOOL
    FC_STATE = 1,                       //len 1 [fc_state]    UINT8
    FC_PURGE_COUNT = 2,                 //len 1               UINT8
    FC_TIME_BETWEEN_LAST_PURGES = 3,    //len 1               UINT32
    FC_ENERGY = 4,	                    //len 2               UINT32
    FC_CHARGE = 5,	                    //len 2               UINT32
    //FC levels
    FC_VOLT = 6,                        //len 1               INT32
    FC_CURR = 7,                        //len 1               INT32
    FC_TEMP = 8,                        //len 1               INT32
    FC_PRES = 9,                        //len 1               INT32
    FC_CAPVOLT = 10,                    //len 1               INT32
    FC_FAN_SPEED = 11,                  //len 1               INT32 (should change to UINT16)
    //output states
    FC_OUTPUTS = 12                     //len 6 [fc_outputs_t] BOOL
  } fuel_cell_t;
    //each error has it's own bit
  typedef enum {
    FC_ERR_CAP_DISC = 0,
    FC_ERR_FC_DISC = 1,
    FC_ERR_RES_DISC = 2,
    FC_ERR_H2OK_LOW = 3,
    FC_ERR_TEMP_LOW = 4,
    FC_ERR_TEMP_H = 5,
    FC_ERR_PRES_H = 6,
    FC_ERR_PRES_L = 7,
    FC_ERR_OVER_CUR = 8,
    FC_ERR_UND_CUR = 9,
    FC_ERR_OVER_VOLT = 10,
    FC_ERR_CAP_VOLT_LOW = 11,
    FC_ERR_WDT = 12,
    FC_ERR_BOD = 13,
    FC_ERR_PWR_BAD = 14
  } fc_errors_t;
  //fc_state is a number not BOOL
  typedef enum {
    FC_STATE_STANDBY = 0,
    FC_STATE_SHUTDOWN = 1,
    FC_STATE_STARTUP_FANS = 2,
    FC_STATE_STARTUP_H2 = 3,
    FC_STATE_STARTUP_PURGE = 4,
    FC_STATE_STARTUP_CHARGE = 5,
    FC_STATE_RUN = 6,
    FC_STATE_ALARM = 8
  } fc_state_t;
  //FC_ENERGY and FC_CHARGE send two values:
  //TOTAL ENERGY/CHARGE and ENERGY/CHARGE since last purge
  typedef enum {
    FC_TOTAL_CHARGE = 0,
    FC_CHARGE_SINCE_LAST_PURGE = 32
  } fc_charge;
  typedef enum {
    FC_TOTAL_ENERGY = 0,
    FC_ENERGY_SINCE_LAST_PURGE = 32
  } dc_energy;
  //fc_outputs bits
  typedef enum {
	FC_START_RELAY = 0,
	FC_RES_RELAY = 1,
	FC_CAP_RELAY = 2,
	FC_MOTOR_RELAY = 3,
	FC_PURGE_VALVE = 4,
	FC_H2_VALVE = 5
  } fc_outputs_t;



  /*
  * Auxiliaries system
  */
  typedef enum {
    SIGNAL = 0,         //len:3 [signal_t]
    HORN = 1,           //len:1
    WIPERS = 2,         //len:1
		HEADLIGHTS = 3,     //len:1
    AUX_STATUS = 4      //len:1             BOOL
  } aux_t;
  //define signal bits
  typedef enum {
    LEFT_SIGNAL = 0,
    RIGHT_SIGNAL = 1,
    HAZARD_LIGHTS = 2
  } signal_t;



  /*
   * Motor system
   */
  typedef enum {
    THROTTLE = 0, // len:1
    BRAKE = 1,    // len:1
    MERROR = 3,   // len:2  [motor_error_t]
    MCURRENT = 4, // len:1
    MSPEED = 6,   // len:1
		MRPM = 7			// len:1
  } motor_t;
  typedef enum {
    MERROR_STALL = 0,
    MERROR_OVERCURRENT = 1
  } motor_error_t;

   /*
  * Other systems
  */
  typedef enum {
      TIME = 0  // len:6 [time_t]
  } other_t;

  typedef enum {
      YEAR = 0,
      MONTH = 1,
      DAY = 2,
      HOUR = 3,
      MINUTE = 4,
      SECOND = 5
  } date_t;


};


#endif
