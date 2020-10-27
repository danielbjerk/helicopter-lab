/*
 * heli_q8_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_q8".
 *
 * Model version              : 1.303
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Sun Oct 18 20:53:57 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "heli_q8.h"
#include "heli_q8_private.h"

/* Block parameters (auto storage) */
P_heli_q8_T heli_q8_P = {
  /*  Variable: A
   * Referenced by: '<S8>/Gain'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.61173902876295994, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Variable: B
   * Referenced by: '<S8>/Gain1'
   */
  { 0.0, 0.0, 0.0, 0.0813635421595687, 0.0, 0.0, 0.50560455693501671, 0.0, 0.0,
    0.0 },

  /*  Variable: C
   * Referenced by:
   *   '<S8>/Gain2'
   *   '<S8>/Gain4'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /*  Variable: F
   * Referenced by: '<S1>/Constant1'
   */
  { 3.7199377508807614E-16, 11.54865410119764, 27.898396876939284,
    3.4679526360371275E-16 },
  0.75,                                /* Variable: Joystick_gain_x
                                        * Referenced by: '<S12>/Joystick_gain_x'
                                        */
  0.25,                                /* Variable: Joystick_gain_y
                                        * Referenced by: '<S12>/Joystick_gain_y'
                                        */

  /*  Variable: K
   * Referenced by: '<S1>/Constant'
   */
  { 3.7199377508807614E-16, 11.54865410119764, 5.58074302613257E-17,
    7.4620744728929562, 27.898396876939284, 3.4679526360371275E-16,
    1.2276547616534095E-16, 2.2360679774997871, 31.622776601683817,
    -2.2217463799377925E-15 },

  /*  Variable: L
   * Referenced by: '<S8>/Gain3'
   */
  { 15.366318612134874, 8.871748187169624, 0.0, 0.0, 0.61173902876295994,
    -7.871748187169624, 15.366318612134874, 0.0, 0.0, 0.0, 0.0, 0.0,
    8.8717481871696275, 15.366318612134872, 0.0, 0.0, 0.0, -14.366318612134872,
    8.8717481871696275, 0.0, 0.0, 0.0, 0.0, 0.0, 17.743496374339252 },
  7.8394,                              /* Variable: Vs_offset
                                        * Referenced by: '<Root>/Vs_offset'
                                        */
  -322.2611,                           /* Variable: e_offset
                                        * Referenced by: '<S3>/Elevation offset'
                                        */
  10.0,                                /* Mask Parameter: HILInitialize_analog_input_maxi
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  -10.0,                               /* Mask Parameter: HILInitialize_analog_input_mini
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  10.0,                                /* Mask Parameter: HILInitialize_analog_output_max
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  -10.0,                               /* Mask Parameter: HILInitialize_analog_output_min
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_final_analog_outp
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_final_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_initial_analog_ou
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_initial_pwm_outpu
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  24305.934065934067,                  /* Mask Parameter: HILInitialize_pwm_frequency
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_pwm_leading_deadb
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_pwm_trailing_dead
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outpu_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outpu_k
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_set_other_outpu_j
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_watchdog_analog_o
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Mask Parameter: HILInitialize_watchdog_pwm_outp
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILReadEncoderTimebase_clock
                                        * Referenced by: '<S3>/HIL Read Encoder Timebase'
                                        */

  /*  Mask Parameter: HILInitialize_hardware_clocks
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0, 1, 2 },
  0,                                   /* Mask Parameter: HILInitialize_initial_encoder_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_pwm_alignment
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_pwm_configuration
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_pwm_modes
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_pwm_polarity
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_watchdog_digital_
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */

  /*  Mask Parameter: HILInitialize_analog_input_chan
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Mask Parameter: HILInitialize_analog_output_cha
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Mask Parameter: HILReadEncoderTimebase_channels
   * Referenced by: '<S3>/HIL Read Encoder Timebase'
   */
  { 0U, 1U, 2U },

  /*  Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S3>/HIL Write Analog'
   */
  { 0U, 1U },

  /*  Mask Parameter: HILInitialize_encoder_channels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /*  Mask Parameter: HILInitialize_pwm_channels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },
  4U,                                  /* Mask Parameter: HILInitialize_quadrature
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  500U,                                /* Mask Parameter: HILReadEncoderTimebase_samples_
                                        * Referenced by: '<S3>/HIL Read Encoder Timebase'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_active
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_final_digital_out
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_initial_digital_o
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_input_
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_inpu_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_output
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_b
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_outp_e
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_j
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_analog_out_ex
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_analog_outp_p
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_frequen
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_frequ_e
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_params_
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_clock_param_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_outpu
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_out_b
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_digital_out_c
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_ou_c1
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_out_a
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_digital_out_j
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_digital_out_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_encoder_count
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_encoder_cou_k
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_encoder_param
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_encoder_par_m
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_other_outpu_l
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_a
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_g
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_p
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_pwm_output_ap
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_outputs_o
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  1,                                   /* Mask Parameter: HILInitialize_set_pwm_params_at
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0,                                   /* Mask Parameter: HILInitialize_set_pwm_params__f
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S9>/Constant'
                                        */
  65.0,                                /* Expression: 65
                                        * Referenced by: '<S9>/Constant1'
                                        */

  /*  Expression: [0 0 0 0 0 0 0 0 0 0]
   * Referenced by: '<S9>/Memory'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Expression: [ 0, 0, 1; 0, 1, 0; -1, 0, 0]
   * Referenced by: '<S9>/Gain1'
   */
  { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0 },

  /*  Expression: [ 0, 0, 1; 0, 1, 0; -1, 0, 0]
   * Referenced by: '<S9>/Gain2'
   */
  { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Memory2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Data Store Memory'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  -50.0,                               /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<S7>/Transfer Fcn'
                                        */
  50.0,                                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<S7>/Transfer Fcn'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Rate Transition: y'
                                        */
  -0.12,                               /* Expression: -0.12
                                        * Referenced by: '<S12>/Dead Zone: y'
                                        */
  0.12,                                /* Expression: 0.12
                                        * Referenced by: '<S12>/Dead Zone: y'
                                        */
  1.1111111111111112,                  /* Expression: 10/9
                                        * Referenced by: '<S12>/Gain: y'
                                        */
  -0.0015339807878856412,              /* Expression: -2*pi /4096
                                        * Referenced by: '<S3>/Pitch: Count to rad'
                                        */
  -50.0,                               /* Computed Parameter: PitchTransferFcn_A
                                        * Referenced by: '<S3>/Pitch: Transfer Fcn'
                                        */
  -2500.0,                             /* Computed Parameter: PitchTransferFcn_C
                                        * Referenced by: '<S3>/Pitch: Transfer Fcn'
                                        */
  50.0,                                /* Computed Parameter: PitchTransferFcn_D
                                        * Referenced by: '<S3>/Pitch: Transfer Fcn'
                                        */
  -0.0015339807878856412,              /* Expression: -2 * pi /4096
                                        * Referenced by: '<S3>/Elevation: Count to rad'
                                        */
  -50.0,                               /* Computed Parameter: ElevationTransferFcn_A
                                        * Referenced by: '<S3>/Elevation: Transfer Fcn'
                                        */
  -2500.0,                             /* Computed Parameter: ElevationTransferFcn_C
                                        * Referenced by: '<S3>/Elevation: Transfer Fcn'
                                        */
  50.0,                                /* Computed Parameter: ElevationTransferFcn_D
                                        * Referenced by: '<S3>/Elevation: Transfer Fcn'
                                        */
  0.00076699039394282058,              /* Expression: 2*pi/8192
                                        * Referenced by: '<S3>/Travel: Count to rad'
                                        */
  -50.0,                               /* Computed Parameter: TravelTransferFcn_A
                                        * Referenced by: '<S3>/Travel: Transfer Fcn'
                                        */
  -2500.0,                             /* Computed Parameter: TravelTransferFcn_C
                                        * Referenced by: '<S3>/Travel: Transfer Fcn'
                                        */
  50.0,                                /* Computed Parameter: TravelTransferFcn_D
                                        * Referenced by: '<S3>/Travel: Transfer Fcn'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Integrator2'
                                        */
  -10.0,                               /* Computed Parameter: TransferFcn_A_p
                                        * Referenced by: '<S1>/Transfer Fcn'
                                        */
  10.0,                                /* Computed Parameter: TransferFcn_C_d
                                        * Referenced by: '<S1>/Transfer Fcn'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S2>/Back gain'
                                        */
  0.5,                                 /* Expression: 0.5
                                        * Referenced by: '<S2>/Front gain'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S3>/Front motor: Saturation'
                                        */
  -5.0,                                /* Expression: -5
                                        * Referenced by: '<S3>/Front motor: Saturation'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S3>/Back motor: Saturation'
                                        */
  -5.0,                                /* Expression: -5
                                        * Referenced by: '<S3>/Back motor: Saturation'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Rate Transition: x'
                                        */
  -0.1,                                /* Expression: -0.1
                                        * Referenced by: '<S12>/Dead Zone: x'
                                        */
  0.1,                                 /* Expression: 0.1
                                        * Referenced by: '<S12>/Dead Zone: x'
                                        */
  1.1111111111111112,                  /* Expression: 10/9
                                        * Referenced by: '<S12>/Gain: x'
                                        */
  8000,                                /* Computed Parameter: StreamCall1_SendBufferSize
                                        * Referenced by: '<S9>/Stream Call1'
                                        */
  8000,                                /* Computed Parameter: StreamCall1_ReceiveBufferSize
                                        * Referenced by: '<S9>/Stream Call1'
                                        */
  80U,                                 /* Computed Parameter: StreamFormattedWrite_MaxUnits
                                        * Referenced by: '<S9>/Stream Formatted Write'
                                        */
  12U,                                 /* Computed Parameter: GameController_BufferSize
                                        * Referenced by: '<S12>/Game Controller'
                                        */

  /*  Expression: value
   * Referenced by: '<S9>/String Constant'
   */
  { 115U, 101U, 114U, 105U, 97U, 108U, 58U, 47U, 47U, 73U, 77U, 85U, 58U, 49U,
    50U, 63U, 98U, 97U, 117U, 100U, 61U, 49U, 49U, 53U, 50U, 48U, 48U, 44U, 119U,
    111U, 114U, 100U, 61U, 56U, 44U, 112U, 97U, 114U, 105U, 116U, 121U, 61U,
    110U, 111U, 110U, 101U, 44U, 115U, 116U, 111U, 112U, 61U, 49U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U },
  0U,                                  /* Expression: uri_argument
                                        * Referenced by: '<S9>/Stream Call1'
                                        */
  1U,                                  /* Computed Parameter: StreamCall1_Endian
                                        * Referenced by: '<S9>/Stream Call1'
                                        */
  1U,                                  /* Computed Parameter: GameController_ControllerNumber
                                        * Referenced by: '<S12>/Game Controller'
                                        */
  1,                                   /* Computed Parameter: HILReadEncoderTimebase_Active
                                        * Referenced by: '<S3>/HIL Read Encoder Timebase'
                                        */
  0,                                   /* Computed Parameter: StreamCall1_Active
                                        * Referenced by: '<S9>/Stream Call1'
                                        */
  0,                                   /* Computed Parameter: HILWriteAnalog_Active
                                        * Referenced by: '<S3>/HIL Write Analog'
                                        */
  0,                                   /* Computed Parameter: GameController_AutoCenter
                                        * Referenced by: '<S12>/Game Controller'
                                        */
  1                                    /* Computed Parameter: GameController_Enabled
                                        * Referenced by: '<S12>/Game Controller'
                                        */
};
