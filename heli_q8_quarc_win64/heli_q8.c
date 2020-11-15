/*
 * heli_q8.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_q8".
 *
 * Model version              : 1.405
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Sun Nov 15 11:30:31 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "heli_q8.h"
#include "heli_q8_private.h"
#include "heli_q8_dt.h"

t_stream heli_q8_rtZt_stream = NULL;

/* Block signals (auto storage) */
B_heli_q8_T heli_q8_B;

/* Continuous states */
X_heli_q8_T heli_q8_X;

/* Block states (auto storage) */
DW_heli_q8_T heli_q8_DW;

/* Real-time model */
RT_MODEL_heli_q8_T heli_q8_M_;
RT_MODEL_heli_q8_T *const heli_q8_M = &heli_q8_M_;

/* Forward declaration for local functions */
static void heli_q8_invNxN(const real_T x[25], real_T y[25]);
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(heli_q8_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(heli_q8_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (heli_q8_M->Timing.TaskCounters.TID[1] == 0) {
    heli_q8_M->Timing.RateInteraction.TID1_2 =
      (heli_q8_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    heli_q8_M->Timing.perTaskSampleHits[5] =
      heli_q8_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (heli_q8_M->Timing.TaskCounters.TID[2])++;
  if ((heli_q8_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    heli_q8_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  heli_q8_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<S5>/Update weighting' */
static void heli_q8_invNxN(const real_T x[25], real_T y[25])
{
  int8_T p[5];
  real_T A[25];
  int8_T ipiv[5];
  int32_T b_j;
  real_T smax;
  real_T s;
  int32_T iy;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  int32_T jBcol;
  int32_T kAcol;
  int32_T c_i;
  for (b_j = 0; b_j < 25; b_j++) {
    y[b_j] = 0.0;
    A[b_j] = x[b_j];
  }

  for (b_j = 0; b_j < 5; b_j++) {
    ipiv[b_j] = (int8_T)(1 + b_j);
  }

  for (b_j = 0; b_j < 4; b_j++) {
    jBcol = b_j * 6;
    iy = 0;
    kAcol = jBcol;
    smax = fabs(A[jBcol]);
    for (c_i = 2; c_i <= 5 - b_j; c_i++) {
      kAcol++;
      s = fabs(A[kAcol]);
      if (s > smax) {
        iy = c_i - 1;
        smax = s;
      }
    }

    if (A[jBcol + iy] != 0.0) {
      if (iy != 0) {
        ipiv[b_j] = (int8_T)((b_j + iy) + 1);
        kAcol = b_j;
        iy += b_j;
        for (c_i = 0; c_i < 5; c_i++) {
          smax = A[kAcol];
          A[kAcol] = A[iy];
          A[iy] = smax;
          kAcol += 5;
          iy += 5;
        }
      }

      iy = (jBcol - b_j) + 5;
      for (kAcol = jBcol + 1; kAcol + 1 <= iy; kAcol++) {
        A[kAcol] /= A[jBcol];
      }
    }

    iy = jBcol;
    kAcol = jBcol + 5;
    for (c_i = 1; c_i <= 4 - b_j; c_i++) {
      smax = A[kAcol];
      if (A[kAcol] != 0.0) {
        c_ix = jBcol + 1;
        d = (iy - b_j) + 10;
        for (ijA = 6 + iy; ijA + 1 <= d; ijA++) {
          A[ijA] += A[c_ix] * -smax;
          c_ix++;
        }
      }

      kAcol += 5;
      iy += 5;
    }
  }

  for (b_j = 0; b_j < 5; b_j++) {
    p[b_j] = (int8_T)(1 + b_j);
  }

  if (ipiv[0] > 1) {
    jBcol = p[ipiv[0] - 1];
    p[ipiv[0] - 1] = p[0];
    p[0] = (int8_T)jBcol;
  }

  if (ipiv[1] > 2) {
    jBcol = p[ipiv[1] - 1];
    p[ipiv[1] - 1] = p[1];
    p[1] = (int8_T)jBcol;
  }

  if (ipiv[2] > 3) {
    jBcol = p[ipiv[2] - 1];
    p[ipiv[2] - 1] = p[2];
    p[2] = (int8_T)jBcol;
  }

  if (ipiv[3] > 4) {
    jBcol = p[ipiv[3] - 1];
    p[ipiv[3] - 1] = p[3];
    p[3] = (int8_T)jBcol;
  }

  for (b_j = 0; b_j < 5; b_j++) {
    jBcol = p[b_j] - 1;
    y[b_j + 5 * (p[b_j] - 1)] = 1.0;
    for (iy = b_j; iy + 1 < 6; iy++) {
      if (y[5 * jBcol + iy] != 0.0) {
        for (kAcol = iy + 1; kAcol + 1 < 6; kAcol++) {
          y[kAcol + 5 * jBcol] -= y[5 * jBcol + iy] * A[5 * iy + kAcol];
        }
      }
    }
  }

  for (b_j = 0; b_j < 5; b_j++) {
    jBcol = 5 * b_j;
    for (iy = 4; iy >= 0; iy += -1) {
      kAcol = 5 * iy;
      if (y[iy + jBcol] != 0.0) {
        y[iy + jBcol] /= A[iy + kAcol];
        for (c_i = 0; c_i + 1 <= iy; c_i++) {
          y[c_i + jBcol] -= y[iy + jBcol] * A[c_i + kAcol];
        }
      }
    }
  }
}

/* Model output function for TID0 */
void heli_q8_output0(void)             /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_DeadZonex;
  t_stream_ptr rtb_StreamCall1_o1;
  t_stream_ptr rtb_StreamFormattedWrite_o1;
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  int32_T rtb_StreamRead1_o5;
  boolean_T rtb_StreamRead1_o3;
  real_T a_c;
  real_T x_out;
  real_T a;
  real_T temp[36];
  int8_T I[36];
  real_T rtb_euler_rates[3];
  real_T rtb_Sum1_m[2];
  real_T rtb_P_k[36];
  real_T rtb_P_est_k[36];
  int32_T i;
  real_T tmp[25];
  real_T tmp_0[25];
  real_T tmp_1[9];
  real_T tmp_2[30];
  real_T tmp_3[5];
  real_T tmp_4[5];
  real_T tmp_5[5];
  int32_T i_0;
  real_T tmp_6[5];
  real_T tmp_7[2];
  real_T tmp_8[2];
  real_T tmp_9[36];
  int32_T i_1;
  real_T tmp_a[6];
  real_T tmp_b[6];
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* set solver stop time */
    if (!(heli_q8_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&heli_q8_M->solverInfo,
                            ((heli_q8_M->Timing.clockTickH0 + 1) *
        heli_q8_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&heli_q8_M->solverInfo,
                            ((heli_q8_M->Timing.clockTick0 + 1) *
        heli_q8_M->Timing.stepSize0 + heli_q8_M->Timing.clockTickH0 *
        heli_q8_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(heli_q8_M)) {
    heli_q8_M->Timing.t[0] = rtsiGetT(&heli_q8_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: heli_q8/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(heli_q8_DW.HILReadEncoderTimebase_Task, 1,
        &heli_q8_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          heli_q8_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          heli_q8_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZonex = heli_q8_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* S-Function (stream_call_block): '<S8>/Stream Call1' */

    /* S-Function Block: heli_q8/IMU/IMU/Stream Call1 (stream_call_block) */
    {
      t_error result = 0;
      t_boolean close_flag = (heli_q8_P.Constant_Value != 0);
      rtb_StreamCall1_o1 = NULL;
      switch (heli_q8_DW.StreamCall1_State) {
       case STREAM_CALL_STATE_NOT_CONNECTED:
        {
          if (!close_flag) {
            /* Make sure URI is null-terminated */
            if (string_length((char *) heli_q8_P.StringConstant_Value, 255) ==
                255) {
              rtmSetErrorStatus(heli_q8_M,
                                "URI passed to Stream Call block is not null-terminated!");
              result = -QERR_STRING_NOT_TERMINATED;
            } else {
              result = stream_connect((char *) heli_q8_P.StringConstant_Value,
                true, heli_q8_P.StreamCall1_SendBufferSize,
                heli_q8_P.StreamCall1_ReceiveBufferSize,
                &heli_q8_DW.StreamCall1_Stream);
              if (result == 0) {
                heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
                stream_set_byte_order(heli_q8_DW.StreamCall1_Stream,
                                      (t_stream_byte_order)
                                      heli_q8_P.StreamCall1_Endian);
                rtb_StreamCall1_o1 = &heli_q8_DW.StreamCall1_Stream;
              } else if (result == -QERR_WOULD_BLOCK) {
                heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTING;
                result = 0;
              }
            }
          }
          break;
        }

       case STREAM_CALL_STATE_CONNECTING:
        {
          if (!close_flag) {
            const t_timeout timeout = { 0, 0, false };/* zero seconds */

            result = stream_poll(heli_q8_DW.StreamCall1_Stream, &timeout,
                                 STREAM_POLL_CONNECT);
            if (result > 0) {
              heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(heli_q8_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    heli_q8_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &heli_q8_DW.StreamCall1_Stream;
              result = 0;
              break;
            } else if (result == 0) {
              break;
            }
          }

          /* Fall through deliberately */
        }

       case STREAM_CALL_STATE_CONNECTED:
        {
          rtb_StreamCall1_o1 = &heli_q8_DW.StreamCall1_Stream;
          if (!close_flag) {
            break;
          }

          /* Fall through deliberately */
        }

       default:
        {
          t_error close_result = stream_close(heli_q8_DW.StreamCall1_Stream);
          if (close_result == 0) {
            heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
            heli_q8_DW.StreamCall1_Stream = NULL;
            rtb_StreamCall1_o1 = NULL;
          } else if (result == 0) {
            result = close_result;
          }
          break;
        }
      }

      heli_q8_B.StreamCall1_o2 = heli_q8_DW.StreamCall1_State;
      rtb_StreamCall1_o3 = (int32_T) result;
    }

    /* S-Function (stream_formatted_write_block): '<S8>/Stream Formatted Write' */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          heli_q8_P.StreamFormattedWrite_MaxUnits, &rtb_StreamFormattedWrite_o2,
          "%c\n"
          , (char) heli_q8_P.Constant1_Value_c
          );
        if (result > 0) {
          result = stream_flush(*rtb_StreamCall1_o1);
        }

        if (result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      }

      rtb_StreamFormattedWrite_o1 = rtb_StreamCall1_o1;
    }

    /* S-Function (stream_read_block): '<S8>/Stream Read1' */
    /* S-Function Block: heli_q8/IMU/IMU/Stream Read1 (stream_read_block) */
    {
      t_error result;
      memset(&rtb_StreamRead1_o2[0], 0, 10 * sizeof(real32_T));
      if (rtb_StreamFormattedWrite_o1 != NULL) {
        result = stream_receive_unit_array(*rtb_StreamFormattedWrite_o1,
          &rtb_StreamRead1_o2[0], sizeof(real32_T), 10);
        rtb_StreamRead1_o3 = (result > 0);
        if (result > 0 || result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      } else {
        rtb_StreamRead1_o3 = false;
        result = 0;
      }

      rtb_StreamRead1_o5 = (int32_T) result;
    }

    /* Switch: '<S8>/Switch' incorporates:
     *  DataTypeConversion: '<S8>/Data Type Conversion'
     *  Memory: '<S8>/Memory'
     */
    for (i = 0; i < 10; i++) {
      if (rtb_StreamRead1_o3) {
        heli_q8_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        heli_q8_B.Switch[i] = heli_q8_DW.Memory_PreviousInput[i];
      }
    }

    /* End of Switch: '<S8>/Switch' */
    for (i = 0; i < 3; i++) {
      /* Gain: '<S8>/Gain1' */
      heli_q8_B.Gain1[i] = 0.0;

      /* Gain: '<S8>/Gain2' */
      heli_q8_B.Gain2[i] = 0.0;

      /* Gain: '<S8>/Gain1' */
      heli_q8_B.Gain1[i] += heli_q8_P.Gain1_Gain[i] * heli_q8_B.Switch[3];

      /* Gain: '<S8>/Gain2' */
      heli_q8_B.Gain2[i] += heli_q8_P.Gain2_Gain[i] * heli_q8_B.Switch[0];

      /* Gain: '<S8>/Gain1' */
      heli_q8_B.Gain1[i] += heli_q8_P.Gain1_Gain[i + 3] * heli_q8_B.Switch[4];

      /* Gain: '<S8>/Gain2' */
      heli_q8_B.Gain2[i] += heli_q8_P.Gain2_Gain[i + 3] * heli_q8_B.Switch[1];

      /* Gain: '<S8>/Gain1' */
      heli_q8_B.Gain1[i] += heli_q8_P.Gain1_Gain[i + 6] * heli_q8_B.Switch[5];

      /* Gain: '<S8>/Gain2' */
      heli_q8_B.Gain2[i] += heli_q8_P.Gain2_Gain[i + 6] * heli_q8_B.Switch[2];
    }

    /* Memory: '<S6>/Memory2' */
    heli_q8_B.Memory2 = heli_q8_DW.Memory2_PreviousInput;
  }

  /* MATLAB Function: '<S6>/Accelerometer values to euler angles corrected' incorporates:
   *  DataStoreRead: '<S6>/Data Store Read'
   */
  /* MATLAB Function 'Measurement transformations/Accelerometer values to euler angles corrected': '<S15>:1' */
  /* '<S15>:1:3' */
  /* '<S15>:1:4' */
  /* '<S15>:1:5' */
  /* '<S15>:1:7' */
  /* '<S15>:1:8' */
  a_c = heli_q8_DW.l_dot * heli_q8_DW.l_dot * 0.66;
  if (heli_q8_B.Gain2[2] == 0.0) {
    /* '<S15>:1:10' */
    /* '<S15>:1:11' */
    x_out = 0.0;
  } else {
    /* '<S15>:1:13' */
    x_out = atan(heli_q8_B.Gain2[1] / heli_q8_B.Gain2[2]);
  }

  if ((a_c * sin(heli_q8_B.Memory2) + heli_q8_B.Gain2[2]) + heli_q8_B.Gain2[1] *
      heli_q8_B.Gain2[1] == 0.0) {
    /* '<S15>:1:16' */
    /* '<S15>:1:17' */
    a_c = 0.0;
  } else {
    /*  y_out = atan(x/sqrt(y.^2 + z.^2));     % old implementation */
    /* '<S15>:1:20' */
    a = a_c * sin(heli_q8_B.Memory2) + heli_q8_B.Gain2[2];
    a_c = atan((a_c * cos(heli_q8_B.Memory2) + heli_q8_B.Gain2[0]) / sqrt
               (heli_q8_B.Gain2[1] * heli_q8_B.Gain2[1] + a * a));
  }

  /* '<S15>:1:23' */
  heli_q8_B.euler_angles[0] = x_out;
  heli_q8_B.euler_angles[1] = a_c;
  heli_q8_B.euler_angles[2] = 0.0;

  /* End of MATLAB Function: '<S6>/Accelerometer values to euler angles corrected' */

  /* MATLAB Function: '<S6>/Gyro vector to [pitch rate, elevation rate, travle rate]' */
  /* MATLAB Function 'Measurement transformations/Gyro vector to [pitch rate, elevation rate, travle rate]': '<S16>:1' */
  /* '<S16>:1:3' */
  /* '<S16>:1:4' */
  /* psi = euler_angles(3); */
  /* '<S16>:1:8' */
  /* '<S16>:1:11' */
  tmp_1[0] = 1.0;
  tmp_1[3] = sin(heli_q8_B.euler_angles[0]) * tan(heli_q8_B.euler_angles[1]);
  tmp_1[6] = cos(heli_q8_B.euler_angles[0]) * tan(heli_q8_B.euler_angles[1]);
  tmp_1[1] = 0.0;
  tmp_1[4] = cos(heli_q8_B.euler_angles[0]);
  tmp_1[7] = -sin(heli_q8_B.euler_angles[0]);
  tmp_1[2] = 0.0;
  tmp_1[5] = sin(heli_q8_B.euler_angles[0]) / cos(heli_q8_B.euler_angles[1]);
  tmp_1[8] = cos(heli_q8_B.euler_angles[0]) / cos(heli_q8_B.euler_angles[1]);
  for (i = 0; i < 3; i++) {
    rtb_euler_rates[i] = tmp_1[i + 6] * heli_q8_B.Gain1[2] + (tmp_1[i + 3] *
      heli_q8_B.Gain1[1] + tmp_1[i] * heli_q8_B.Gain1[0]);
  }

  /* End of MATLAB Function: '<S6>/Gyro vector to [pitch rate, elevation rate, travle rate]' */

  /* DataStoreWrite: '<S6>/Data Store Write' */
  heli_q8_DW.l_dot = rtb_euler_rates[2];
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Constant: '<S6>/Constant' */
    heli_q8_B.Constant = heli_q8_P.Constant_Value_a;

    /* Constant: '<S6>/Constant1' */
    heli_q8_B.Constant1 = heli_q8_P.Constant1_Value_a;

    /* Constant: '<S6>/Constant2' */
    heli_q8_B.Constant2 = heli_q8_P.Constant2_Value;

    /* Gain: '<S3>/Elevation: Count to rad' incorporates:
     *  Constant: '<S3>/Elevation offset'
     *  Sum: '<S3>/Sum'
     */
    heli_q8_B.ElevationCounttorad = (rtb_DeadZonex - heli_q8_P.e_offset) *
      heli_q8_P.ElevationCounttorad_Gain;

    /* UnitDelay: '<S5>/Unit Delay' */
    for (i = 0; i < 6; i++) {
      heli_q8_B.x_k[i] = heli_q8_DW.UnitDelay_DSTATE[i];
    }

    /* End of UnitDelay: '<S5>/Unit Delay' */

    /* UnitDelay: '<S5>/Unit Delay1' */
    memcpy(&rtb_P_k[0], &heli_q8_DW.UnitDelay1_DSTATE[0], 36U * sizeof(real_T));

    /* MATLAB Function: '<S5>/Update weighting' incorporates:
     *  Constant: '<S5>/Constant3'
     *  Constant: '<S5>/Constant4'
     *  UnitDelay: '<S5>/Unit Delay1'
     */
    /* MATLAB Function 'Kalman filter/Update weighting': '<S14>:1' */
    /* '<S14>:1:2' */
    for (i = 0; i < 5; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        tmp_2[i + 5 * i_0] = 0.0;
        for (i_1 = 0; i_1 < 6; i_1++) {
          tmp_2[i + 5 * i_0] += heli_q8_P.C_d[5 * i_1 + i] *
            heli_q8_DW.UnitDelay1_DSTATE[6 * i_0 + i_1];
        }
      }
    }

    for (i = 0; i < 5; i++) {
      for (i_0 = 0; i_0 < 5; i_0++) {
        x_out = 0.0;
        for (i_1 = 0; i_1 < 6; i_1++) {
          x_out += tmp_2[5 * i_1 + i] * heli_q8_P.C_d[5 * i_1 + i_0];
        }

        tmp[i + 5 * i_0] = heli_q8_P.R_d[5 * i_0 + i] + x_out;
      }
    }

    heli_q8_invNxN(tmp, tmp_0);
    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 5; i_0++) {
        tmp_2[i + 6 * i_0] = 0.0;
        for (i_1 = 0; i_1 < 6; i_1++) {
          tmp_2[i + 6 * i_0] += heli_q8_DW.UnitDelay1_DSTATE[6 * i_1 + i] *
            heli_q8_P.C_d[5 * i_1 + i_0];
        }
      }
    }

    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 5; i_0++) {
        heli_q8_B.K_k[i + 6 * i_0] = 0.0;
        for (i_1 = 0; i_1 < 5; i_1++) {
          heli_q8_B.K_k[i + 6 * i_0] += tmp_2[6 * i_1 + i] * tmp_0[5 * i_0 + i_1];
        }
      }
    }

    /* End of MATLAB Function: '<S5>/Update weighting' */

    /* ManualSwitch: '<Root>/Manual Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    if (heli_q8_P.ManualSwitch_CurrentSetting == 1) {
      heli_q8_B.ManualSwitch = rtb_StreamRead1_o3;
    } else {
      heli_q8_B.ManualSwitch = heli_q8_P.Constant1_Value;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch' */

    /* Constant: '<S5>/Constant5' */
    memcpy(&heli_q8_B.Constant5[0], &heli_q8_P.C_d[0], 30U * sizeof(real_T));
  }

  /* MATLAB Function: '<S5>/Correction step' */
  /* MATLAB Function 'Kalman filter/Correction step': '<S10>:1' */
  if (!(heli_q8_B.ManualSwitch != 0.0)) {
    /* '<S10>:1:3' */
    /* '<S10>:1:4' */
    for (i = 0; i < 6; i++) {
      heli_q8_B.x_est_k[i] = heli_q8_B.x_k[i];
    }
  } else {
    /* SignalConversion: '<S10>/TmpSignal ConversionAt SFunction Inport3' incorporates:
     *  Sum: '<S6>/Sum'
     *  Sum: '<S6>/Sum1'
     *  Sum: '<S6>/Sum2'
     */
    /* '<S10>:1:6' */
    tmp_3[0] = heli_q8_B.euler_angles[0] + heli_q8_B.Constant1;
    tmp_3[1] = rtb_euler_rates[0];
    tmp_3[2] = heli_q8_B.euler_angles[1] + heli_q8_B.Constant;
    tmp_3[3] = rtb_euler_rates[1] - heli_q8_B.Constant2;
    tmp_3[4] = rtb_euler_rates[2];
    for (i = 0; i < 5; i++) {
      tmp_4[i] = 0.0;
      for (i_0 = 0; i_0 < 6; i_0++) {
        tmp_4[i] += heli_q8_B.Constant5[5 * i_0 + i] * heli_q8_B.x_k[i_0];
      }

      tmp_5[i] = tmp_3[i] - tmp_4[i];
    }

    for (i = 0; i < 6; i++) {
      x_out = 0.0;
      for (i_0 = 0; i_0 < 5; i_0++) {
        x_out += heli_q8_B.K_k[6 * i_0 + i] * tmp_5[i_0];
      }

      heli_q8_B.x_est_k[i] = heli_q8_B.x_k[i] + x_out;
    }
  }

  /* End of MATLAB Function: '<S5>/Correction step' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo FileInport1' */
    heli_q8_B.TmpSignalConversionAtToFileInpo[0] = heli_q8_B.ElevationCounttorad;
    heli_q8_B.TmpSignalConversionAtToFileInpo[1] = heli_q8_B.x_est_k[2];

    /* ToFile: '<Root>/To File' */
    if (rtmIsMajorTimeStep(heli_q8_M)) {
      {
        if (!(++heli_q8_DW.ToFile_IWORK.Decimation % 1) &&
            (heli_q8_DW.ToFile_IWORK.Count*3)+1 < 100000000 ) {
          FILE *fp = (FILE *) heli_q8_DW.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[3];
            heli_q8_DW.ToFile_IWORK.Decimation = 0;
            u[0] = heli_q8_M->Timing.t[1];
            u[1] = heli_q8_B.TmpSignalConversionAtToFileInpo[0];
            u[2] = heli_q8_B.TmpSignalConversionAtToFileInpo[1];
            if (fwrite(u, sizeof(real_T), 3, fp) != 3) {
              rtmSetErrorStatus(heli_q8_M,
                                "Error writing to MAT-file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
              return;
            }

            if (((++heli_q8_DW.ToFile_IWORK.Count)*3)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file p4tx_kalman-wrong-initialization-of-e-offset_e.mat.\n");
            }
          }
        }
      }
    }
  }

  /* TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  heli_q8_B.ElevationTransferFcn = 0.0;
  heli_q8_B.ElevationTransferFcn += heli_q8_P.ElevationTransferFcn_C *
    heli_q8_X.ElevationTransferFcn_CSTATE;
  heli_q8_B.ElevationTransferFcn += heli_q8_P.ElevationTransferFcn_D *
    heli_q8_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* RateTransition: '<S17>/Rate Transition: y' */
    if (heli_q8_M->Timing.RateInteraction.TID1_2) {
      heli_q8_B.RateTransitiony = heli_q8_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S17>/Rate Transition: y' */

    /* DeadZone: '<S17>/Dead Zone: y' */
    if (heli_q8_B.RateTransitiony > heli_q8_P.DeadZoney_End) {
      rtb_DeadZonex = heli_q8_B.RateTransitiony - heli_q8_P.DeadZoney_End;
    } else if (heli_q8_B.RateTransitiony >= heli_q8_P.DeadZoney_Start) {
      rtb_DeadZonex = 0.0;
    } else {
      rtb_DeadZonex = heli_q8_B.RateTransitiony - heli_q8_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S17>/Dead Zone: y' */

    /* Gain: '<S17>/Joystick_gain_y' incorporates:
     *  Gain: '<S17>/Gain: y'
     */
    heli_q8_B.Joystick_gain_y = heli_q8_P.Gainy_Gain * rtb_DeadZonex *
      heli_q8_P.Joystick_gain_y;

    /* Gain: '<S3>/Pitch: Count to rad' */
    heli_q8_B.PitchCounttorad = heli_q8_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;
  }

  /* TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  heli_q8_B.PitchTransferFcn = 0.0;
  heli_q8_B.PitchTransferFcn += heli_q8_P.PitchTransferFcn_C *
    heli_q8_X.PitchTransferFcn_CSTATE;
  heli_q8_B.PitchTransferFcn += heli_q8_P.PitchTransferFcn_D *
    heli_q8_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
  }

  /* TransferFcn: '<S7>/Transfer Fcn' */
  heli_q8_B.TransferFcn = 0.0;
  heli_q8_B.TransferFcn += heli_q8_P.TransferFcn_C *
    heli_q8_X.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Gain: '<S3>/Travel: Count to rad' */
    heli_q8_B.TravelCounttorad = heli_q8_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<S3>/Travel: Transfer Fcn' */
  heli_q8_B.TravelTransferFcn = 0.0;
  heli_q8_B.TravelTransferFcn += heli_q8_P.TravelTransferFcn_C *
    heli_q8_X.TravelTransferFcn_CSTATE;
  heli_q8_B.TravelTransferFcn += heli_q8_P.TravelTransferFcn_D *
    heli_q8_B.TravelCounttorad;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
  }

  /* Integrator: '<S1>/Integrator2' */
  heli_q8_B.Integrator2[0] = heli_q8_X.Integrator2_CSTATE[0];
  heli_q8_B.Integrator2[1] = heli_q8_X.Integrator2_CSTATE[1];
  if (rtmIsMajorTimeStep(heli_q8_M)) {
  }

  /* TransferFcn: '<S1>/Transfer Fcn' */
  heli_q8_B.TransferFcn_m = 0.0;
  heli_q8_B.TransferFcn_m += heli_q8_P.TransferFcn_C_d *
    heli_q8_X.TransferFcn_CSTATE_p;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Constant: '<S1>/Constant' */
    memcpy(&heli_q8_B.Constant_e[0], &heli_q8_P.K[0], 10U * sizeof(real_T));

    /* Constant: '<S1>/Constant1' */
    heli_q8_B.Constant1_j[0] = heli_q8_P.F[0];
    heli_q8_B.Constant1_j[1] = heli_q8_P.F[1];
    heli_q8_B.Constant1_j[2] = heli_q8_P.F[2];
    heli_q8_B.Constant1_j[3] = heli_q8_P.F[3];
  }

  /* Sum: '<S1>/Sum' */
  heli_q8_B.Sum = heli_q8_B.x_est_k[3] - heli_q8_B.Joystick_gain_y;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtProductInport2' incorporates:
   *  Integrator: '<S1>/Integrator'
   *  Integrator: '<S1>/Integrator1'
   *  Product: '<S1>/Product'
   */
  tmp_6[2] = heli_q8_B.x_est_k[3];
  tmp_6[3] = heli_q8_X.Integrator_CSTATE;
  tmp_6[4] = heli_q8_X.Integrator1_CSTATE;
  tmp_6[0] = heli_q8_B.x_est_k[0];

  /* Product: '<S1>/Product1' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct1Inport2'
   *  Sum: '<S1>/Sum1'
   */
  tmp_7[0] = heli_q8_B.Constant1_j[0] * heli_q8_B.TransferFcn +
    heli_q8_B.Constant1_j[2] * heli_q8_B.Joystick_gain_y;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtProductInport2' incorporates:
   *  Product: '<S1>/Product'
   */
  tmp_6[1] = heli_q8_B.x_est_k[1];

  /* Product: '<S1>/Product1' incorporates:
   *  SignalConversion: '<S1>/TmpSignal ConversionAtProduct1Inport2'
   *  Sum: '<S1>/Sum1'
   */
  tmp_7[1] = heli_q8_B.Constant1_j[1] * heli_q8_B.TransferFcn;
  tmp_7[1] += heli_q8_B.Constant1_j[3] * heli_q8_B.Joystick_gain_y;
  for (i = 0; i < 2; i++) {
    /* Product: '<S1>/Product' incorporates:
     *  Sum: '<S1>/Sum1'
     */
    tmp_8[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp_8[i] += heli_q8_B.Constant_e[(i_0 << 1) + i] * tmp_6[i_0];
    }

    /* Sum: '<S1>/Sum1' */
    rtb_Sum1_m[i] = tmp_7[i] - tmp_8[i];
  }

  /* Sum: '<S1>/Sum2' */
  heli_q8_B.Sum2 = heli_q8_B.x_est_k[0] - heli_q8_B.TransferFcn;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Constant: '<Root>/Vs_offset' */
    heli_q8_B.Vs_offset = heli_q8_P.Vs_offset;
  }

  /* Sum: '<Root>/Sum' */
  x_out = heli_q8_B.Vs_offset + rtb_Sum1_m[0];
  if (rtmIsMajorTimeStep(heli_q8_M)) {
  }

  /* Gain: '<S2>/Front gain' incorporates:
   *  Sum: '<S2>/Add'
   */
  a_c = (x_out - rtb_Sum1_m[1]) * heli_q8_P.Frontgain_Gain;

  /* Saturate: '<S3>/Front motor: Saturation' */
  if (a_c > heli_q8_P.FrontmotorSaturation_UpperSat) {
    heli_q8_B.FrontmotorSaturation = heli_q8_P.FrontmotorSaturation_UpperSat;
  } else if (a_c < heli_q8_P.FrontmotorSaturation_LowerSat) {
    heli_q8_B.FrontmotorSaturation = heli_q8_P.FrontmotorSaturation_LowerSat;
  } else {
    heli_q8_B.FrontmotorSaturation = a_c;
  }

  /* End of Saturate: '<S3>/Front motor: Saturation' */

  /* Gain: '<S2>/Back gain' incorporates:
   *  Sum: '<S2>/Subtract'
   */
  a_c = (x_out + rtb_Sum1_m[1]) * heli_q8_P.Backgain_Gain;

  /* Saturate: '<S3>/Back motor: Saturation' */
  if (a_c > heli_q8_P.BackmotorSaturation_UpperSat) {
    heli_q8_B.BackmotorSaturation = heli_q8_P.BackmotorSaturation_UpperSat;
  } else if (a_c < heli_q8_P.BackmotorSaturation_LowerSat) {
    heli_q8_B.BackmotorSaturation = heli_q8_P.BackmotorSaturation_LowerSat;
  } else {
    heli_q8_B.BackmotorSaturation = a_c;
  }

  /* End of Saturate: '<S3>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: heli_q8/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      heli_q8_DW.HILWriteAnalog_Buffer[0] = heli_q8_B.FrontmotorSaturation;
      heli_q8_DW.HILWriteAnalog_Buffer[1] = heli_q8_B.BackmotorSaturation;
      result = hil_write_analog(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILWriteAnalog_channels, 2, &heli_q8_DW.HILWriteAnalog_Buffer
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      }
    }

    /* S-Function (stop_with_error_block): '<S8>/Stop with Call Error' */

    /* S-Function Block: heli_q8/IMU/IMU/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    /* S-Function (stop_with_error_block): '<S8>/Stop with Read Error' */

    /* S-Function Block: heli_q8/IMU/IMU/Stop with Read Error (stop_with_error_block) */
    {
      if (rtb_StreamRead1_o5 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamRead1_o5, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    /* MATLAB Function: '<S5>/Update estimate variance' incorporates:
     *  Constant: '<S5>/Constant2'
     *  Constant: '<S5>/Constant8'
     */
    /* MATLAB Function 'Kalman filter/Update estimate variance': '<S12>:1' */
    if (!(heli_q8_B.ManualSwitch != 0.0)) {
      /* '<S12>:1:3' */
      /* '<S12>:1:4' */
      memcpy(&rtb_P_est_k[0], &rtb_P_k[0], 36U * sizeof(real_T));
    } else {
      /* '<S12>:1:6' */
      for (i = 0; i < 36; i++) {
        I[i] = 0;
      }

      for (i = 0; i < 6; i++) {
        I[i + 6 * i] = 1;
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          x_out = 0.0;
          for (i_1 = 0; i_1 < 5; i_1++) {
            x_out += heli_q8_B.K_k[6 * i_1 + i] * heli_q8_P.C_d[5 * i_0 + i_1];
          }

          temp[i + 6 * i_0] = (real_T)I[6 * i_0 + i] - x_out;
        }
      }

      /* '<S12>:1:7' */
      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_P_est_k[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_P_est_k[i + 6 * i_0] += temp[6 * i_1 + i] * rtb_P_k[6 * i_0 +
              i_1];
          }
        }

        for (i_0 = 0; i_0 < 5; i_0++) {
          tmp_2[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 5; i_1++) {
            tmp_2[i + 6 * i_0] += heli_q8_B.K_k[6 * i_1 + i] * heli_q8_P.R_d[5 *
              i_0 + i_1];
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_P_k[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 6; i_1++) {
            rtb_P_k[i + 6 * i_0] += rtb_P_est_k[6 * i_1 + i] * temp[6 * i_1 +
              i_0];
          }

          tmp_9[i + 6 * i_0] = 0.0;
          for (i_1 = 0; i_1 < 5; i_1++) {
            tmp_9[i + 6 * i_0] += tmp_2[6 * i_1 + i] * heli_q8_B.K_k[6 * i_1 +
              i_0];
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (i_0 = 0; i_0 < 6; i_0++) {
          rtb_P_est_k[i_0 + 6 * i] = rtb_P_k[6 * i + i_0] + tmp_9[6 * i + i_0];
        }
      }
    }

    /* End of MATLAB Function: '<S5>/Update estimate variance' */

    /* MATLAB Function: '<S5>/Access diagonal elements' */
    /* MATLAB Function 'Kalman filter/Access diagonal elements': '<S9>:1' */
    /* '<S9>:1:3' */
    heli_q8_B.P_est_k_diag[0] = rtb_P_est_k[0];
    heli_q8_B.P_est_k_diag[1] = rtb_P_est_k[7];
    heli_q8_B.P_est_k_diag[2] = rtb_P_est_k[14];
    heli_q8_B.P_est_k_diag[3] = rtb_P_est_k[21];
    heli_q8_B.P_est_k_diag[4] = rtb_P_est_k[28];
    heli_q8_B.P_est_k_diag[5] = rtb_P_est_k[35];

    /* Constant: '<S5>/Constant6' */
    memcpy(&heli_q8_B.Constant6[0], &heli_q8_P.A_d[0], 36U * sizeof(real_T));

    /* Constant: '<S5>/Constant7' */
    memcpy(&heli_q8_B.Constant7[0], &heli_q8_P.B_d[0], 12U * sizeof(real_T));
  }

  /* MATLAB Function: '<S5>/Prediction step' */
  /* MATLAB Function 'Kalman filter/Prediction step': '<S11>:1' */
  /* '<S11>:1:3' */
  for (i = 0; i < 6; i++) {
    tmp_a[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      tmp_a[i] += heli_q8_B.Constant6[6 * i_0 + i] * heli_q8_B.x_est_k[i_0];
    }

    tmp_b[i] = 0.0;
    tmp_b[i] += heli_q8_B.Constant7[i] * rtb_Sum1_m[0];
    tmp_b[i] += heli_q8_B.Constant7[i + 6] * rtb_Sum1_m[1];
    heli_q8_B.x_pred_k_plus_1[i] = tmp_a[i] + tmp_b[i];
  }

  /* End of MATLAB Function: '<S5>/Prediction step' */
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* MATLAB Function: '<S5>/Update prediction variance' incorporates:
     *  Constant: '<S5>/Constant'
     *  Constant: '<S5>/Constant1'
     */
    /* MATLAB Function 'Kalman filter/Update prediction variance': '<S13>:1' */
    /* '<S13>:1:3' */
    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        tmp_9[i + 6 * i_0] = 0.0;
        for (i_1 = 0; i_1 < 6; i_1++) {
          tmp_9[i + 6 * i_0] += heli_q8_P.A_d[6 * i_1 + i] * rtb_P_est_k[6 * i_0
            + i_1];
        }
      }
    }

    for (i = 0; i < 6; i++) {
      for (i_0 = 0; i_0 < 6; i_0++) {
        x_out = 0.0;
        for (i_1 = 0; i_1 < 6; i_1++) {
          x_out += tmp_9[6 * i_1 + i] * heli_q8_P.A_d[6 * i_1 + i_0];
        }

        heli_q8_B.P_pred_k_plus_1[i + 6 * i_0] = heli_q8_P.Q_d[6 * i_0 + i] +
          x_out;
      }
    }

    /* End of MATLAB Function: '<S5>/Update prediction variance' */

    /* RateTransition: '<S17>/Rate Transition: x' */
    if (heli_q8_M->Timing.RateInteraction.TID1_2) {
      heli_q8_B.RateTransitionx = heli_q8_DW.RateTransitionx_Buffer0;
    }

    /* End of RateTransition: '<S17>/Rate Transition: x' */

    /* DeadZone: '<S17>/Dead Zone: x' */
    if (heli_q8_B.RateTransitionx > heli_q8_P.DeadZonex_End) {
      rtb_DeadZonex = heli_q8_B.RateTransitionx - heli_q8_P.DeadZonex_End;
    } else if (heli_q8_B.RateTransitionx >= heli_q8_P.DeadZonex_Start) {
      rtb_DeadZonex = 0.0;
    } else {
      rtb_DeadZonex = heli_q8_B.RateTransitionx - heli_q8_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S17>/Dead Zone: x' */

    /* Gain: '<S17>/Joystick_gain_x' incorporates:
     *  Gain: '<S17>/Gain: x'
     */
    heli_q8_B.Joystick_gain_x = heli_q8_P.Gainx_Gain * rtb_DeadZonex *
      heli_q8_P.Joystick_gain_x;
  }
}

/* Model update function for TID0 */
void heli_q8_update0(void)             /* Sample time: [0.0s, 0.0s] */
{
  int32_T i;
  if (rtmIsMajorTimeStep(heli_q8_M)) {
    /* Update for Memory: '<S8>/Memory' */
    memcpy(&heli_q8_DW.Memory_PreviousInput[0], &heli_q8_B.Switch[0], 10U *
           sizeof(real_T));

    /* Update for Memory: '<S6>/Memory2' */
    heli_q8_DW.Memory2_PreviousInput = heli_q8_B.euler_angles[1];

    /* Update for UnitDelay: '<S5>/Unit Delay' */
    for (i = 0; i < 6; i++) {
      heli_q8_DW.UnitDelay_DSTATE[i] = heli_q8_B.x_pred_k_plus_1[i];
    }

    /* End of Update for UnitDelay: '<S5>/Unit Delay' */

    /* Update for UnitDelay: '<S5>/Unit Delay1' */
    memcpy(&heli_q8_DW.UnitDelay1_DSTATE[0], &heli_q8_B.P_pred_k_plus_1[0], 36U *
           sizeof(real_T));
  }

  if (rtmIsMajorTimeStep(heli_q8_M)) {
    rt_ertODEUpdateContinuousStates(&heli_q8_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_M->Timing.clockTick0)) {
    ++heli_q8_M->Timing.clockTickH0;
  }

  heli_q8_M->Timing.t[0] = rtsiGetSolverStopTime(&heli_q8_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_M->Timing.clockTick1)) {
    ++heli_q8_M->Timing.clockTickH1;
  }

  heli_q8_M->Timing.t[1] = heli_q8_M->Timing.clockTick1 *
    heli_q8_M->Timing.stepSize1 + heli_q8_M->Timing.clockTickH1 *
    heli_q8_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void heli_q8_derivatives(void)
{
  XDot_heli_q8_T *_rtXdot;
  _rtXdot = ((XDot_heli_q8_T *) heli_q8_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_q8_P.ElevationTransferFcn_A *
    heli_q8_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_q8_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += heli_q8_P.PitchTransferFcn_A *
    heli_q8_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += heli_q8_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S7>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += heli_q8_P.TransferFcn_A *
    heli_q8_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += heli_q8_B.Joystick_gain_x;

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += heli_q8_P.TravelTransferFcn_A *
    heli_q8_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += heli_q8_B.TravelCounttorad;

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  _rtXdot->Integrator2_CSTATE[0] = heli_q8_B.Joystick_gain_y;
  _rtXdot->Integrator2_CSTATE[1] = heli_q8_B.TransferFcn_m;

  /* Derivatives for TransferFcn: '<S1>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE_p = 0.0;
  _rtXdot->TransferFcn_CSTATE_p += heli_q8_P.TransferFcn_A_p *
    heli_q8_X.TransferFcn_CSTATE_p;
  _rtXdot->TransferFcn_CSTATE_p += heli_q8_B.x_est_k[3];

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE = heli_q8_B.Sum2;

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = heli_q8_B.Sum;
}

/* Model output function for TID2 */
void heli_q8_output2(void)             /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S17>/Game Controller' */

  /* S-Function Block: heli_q8/Reference values/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(heli_q8_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        heli_q8_B.GameController_o4 = state.x;
        heli_q8_B.GameController_o5 = state.y;
      }
    } else {
      heli_q8_B.GameController_o4 = 0;
      heli_q8_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void heli_q8_update2(void)             /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S17>/Rate Transition: y' */
  heli_q8_DW.RateTransitiony_Buffer0 = heli_q8_B.GameController_o5;

  /* Update for RateTransition: '<S17>/Rate Transition: x' */
  heli_q8_DW.RateTransitionx_Buffer0 = heli_q8_B.GameController_o4;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_M->Timing.clockTick2)) {
    ++heli_q8_M->Timing.clockTickH2;
  }

  heli_q8_M->Timing.t[2] = heli_q8_M->Timing.clockTick2 *
    heli_q8_M->Timing.stepSize2 + heli_q8_M->Timing.clockTickH2 *
    heli_q8_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void heli_q8_output(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_q8_output0();
    break;

   case 2 :
    heli_q8_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void heli_q8_update(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_q8_update0();
    break;

   case 2 :
    heli_q8_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void heli_q8_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_q8/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &heli_q8_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(heli_q8_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(heli_q8_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      return;
    }

    if ((heli_q8_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &heli_q8_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = heli_q8_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &heli_q8_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = heli_q8_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_analog_input_chan, 8U,
        &heli_q8_DW.HILInitialize_AIMinimums[0],
        &heli_q8_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_analog_output && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &heli_q8_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = heli_q8_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &heli_q8_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = heli_q8_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_analog_output_cha, 8U,
        &heli_q8_DW.HILInitialize_AOMinimums[0],
        &heli_q8_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_analog_output_cha, 8U,
        &heli_q8_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if (heli_q8_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (heli_q8_DW.HILInitialize_Card,
         heli_q8_P.HILInitialize_analog_output_cha, 8U,
         &heli_q8_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_encoder_param && !is_switching) ||
        (heli_q8_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &heli_q8_DW.HILInitialize_QuadratureModes
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = heli_q8_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode
        *) &heli_q8_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_encoder_count && !is_switching) ||
        (heli_q8_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &heli_q8_DW.HILInitialize_InitialEICounts
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = heli_q8_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_encoder_channels, 8U,
        &heli_q8_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (heli_q8_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_q8_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_q8_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &heli_q8_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          heli_q8_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &heli_q8_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            heli_q8_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            heli_q8_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              heli_q8_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            heli_q8_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            heli_q8_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              heli_q8_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(heli_q8_DW.HILInitialize_Card,
          &heli_q8_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &heli_q8_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(heli_q8_DW.HILInitialize_Card,
          &heli_q8_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &heli_q8_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_q8_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_q8_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &heli_q8_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = heli_q8_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &heli_q8_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = heli_q8_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &heli_q8_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &heli_q8_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &heli_q8_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &heli_q8_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = heli_q8_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U,
        &heli_q8_DW.HILInitialize_POSortedFreqs[0],
        &heli_q8_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (heli_q8_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(heli_q8_DW.HILInitialize_Card,
        heli_q8_P.HILInitialize_pwm_channels, 8U,
        &heli_q8_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }

    if (heli_q8_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (heli_q8_DW.HILInitialize_Card, heli_q8_P.HILInitialize_pwm_channels, 8U,
         &heli_q8_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: heli_q8/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(heli_q8_DW.HILInitialize_Card,
      heli_q8_P.HILReadEncoderTimebase_samples_,
      heli_q8_P.HILReadEncoderTimebase_channels, 3,
      &heli_q8_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_M, _rt_error_message);
    }
  }

  /* Start for S-Function (stream_call_block): '<S8>/Stream Call1' */

  /* S-Function Block: heli_q8/IMU/IMU/Stream Call1 (stream_call_block) */
  {
    heli_q8_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    heli_q8_DW.StreamCall1_Stream = NULL;
  }

  /* Start for DataStoreMemory: '<S6>/Data Store Memory' */
  heli_q8_DW.l_dot = heli_q8_P.DataStoreMemory_InitialValue;

  /* Start for Constant: '<S5>/Constant5' */
  memcpy(&heli_q8_B.Constant5[0], &heli_q8_P.C_d[0], 30U * sizeof(real_T));

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "p4tx_kalman-wrong-initialization-of-e-offset_e.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error creating .mat file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,3,0,"ans")) {
      rtmSetErrorStatus(heli_q8_M,
                        "Error writing mat file header to file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
      return;
    }

    heli_q8_DW.ToFile_IWORK.Count = 0;
    heli_q8_DW.ToFile_IWORK.Decimation = -1;
    heli_q8_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S17>/Rate Transition: y' */
  heli_q8_B.RateTransitiony = heli_q8_P.RateTransitiony_X0;

  /* Start for Constant: '<S5>/Constant6' */
  memcpy(&heli_q8_B.Constant6[0], &heli_q8_P.A_d[0], 36U * sizeof(real_T));

  /* Start for Constant: '<S5>/Constant7' */
  memcpy(&heli_q8_B.Constant7[0], &heli_q8_P.B_d[0], 12U * sizeof(real_T));

  /* Start for RateTransition: '<S17>/Rate Transition: x' */
  heli_q8_B.RateTransitionx = heli_q8_P.RateTransitionx_X0;

  /* Start for S-Function (game_controller_block): '<S17>/Game Controller' */

  /* S-Function Block: heli_q8/Reference values/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open(heli_q8_P.GameController_ControllerNumber,
        heli_q8_P.GameController_BufferSize, deadzone, saturation,
        heli_q8_P.GameController_AutoCenter, 0, 1.0,
        &heli_q8_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_M, _rt_error_message);
      }
    }
  }

  {
    int32_T i;

    /* InitializeConditions for Memory: '<S8>/Memory' */
    memcpy(&heli_q8_DW.Memory_PreviousInput[0], &heli_q8_P.Memory_X0[0], 10U *
           sizeof(real_T));

    /* InitializeConditions for Memory: '<S6>/Memory2' */
    heli_q8_DW.Memory2_PreviousInput = heli_q8_P.Memory2_X0;

    /* InitializeConditions for UnitDelay: '<S5>/Unit Delay' */
    for (i = 0; i < 6; i++) {
      heli_q8_DW.UnitDelay_DSTATE[i] = heli_q8_P.UnitDelay_InitialCondition[i];
    }

    /* End of InitializeConditions for UnitDelay: '<S5>/Unit Delay' */

    /* InitializeConditions for UnitDelay: '<S5>/Unit Delay1' */
    for (i = 0; i < 36; i++) {
      heli_q8_DW.UnitDelay1_DSTATE[i] = heli_q8_P.UnitDelay1_InitialCondition;
    }

    /* End of InitializeConditions for UnitDelay: '<S5>/Unit Delay1' */

    /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
    heli_q8_X.ElevationTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for RateTransition: '<S17>/Rate Transition: y' */
    heli_q8_DW.RateTransitiony_Buffer0 = heli_q8_P.RateTransitiony_X0;

    /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
    heli_q8_X.PitchTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S7>/Transfer Fcn' */
    heli_q8_X.TransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
    heli_q8_X.TravelTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S1>/Integrator2' */
    heli_q8_X.Integrator2_CSTATE[0] = heli_q8_P.Integrator2_IC;
    heli_q8_X.Integrator2_CSTATE[1] = heli_q8_P.Integrator2_IC;

    /* InitializeConditions for TransferFcn: '<S1>/Transfer Fcn' */
    heli_q8_X.TransferFcn_CSTATE_p = 0.0;

    /* InitializeConditions for Integrator: '<S1>/Integrator' */
    heli_q8_X.Integrator_CSTATE = heli_q8_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S1>/Integrator1' */
    heli_q8_X.Integrator1_CSTATE = heli_q8_P.Integrator1_IC;

    /* InitializeConditions for RateTransition: '<S17>/Rate Transition: x' */
    heli_q8_DW.RateTransitionx_Buffer0 = heli_q8_P.RateTransitionx_X0;
  }
}

/* Model terminate function */
void heli_q8_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_q8/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(heli_q8_DW.HILInitialize_Card);
    hil_monitor_stop_all(heli_q8_DW.HILInitialize_Card);
    is_switching = false;
    if ((heli_q8_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (heli_q8_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((heli_q8_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (heli_q8_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(heli_q8_DW.HILInitialize_Card
                         , heli_q8_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , heli_q8_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &heli_q8_DW.HILInitialize_AOVoltages[0]
                         , &heli_q8_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(heli_q8_DW.HILInitialize_Card,
            heli_q8_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &heli_q8_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(heli_q8_DW.HILInitialize_Card,
            heli_q8_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &heli_q8_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(heli_q8_DW.HILInitialize_Card);
    hil_monitor_delete_all(heli_q8_DW.HILInitialize_Card);
    hil_close(heli_q8_DW.HILInitialize_Card);
    heli_q8_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (stream_call_block): '<S8>/Stream Call1' */

  /* S-Function Block: heli_q8/IMU/IMU/Stream Call1 (stream_call_block) */
  {
    if (heli_q8_DW.StreamCall1_Stream != NULL) {
      stream_close(heli_q8_DW.StreamCall1_Stream);
      heli_q8_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) heli_q8_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "p4tx_kalman-wrong-initialization-of-e-offset_e.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error closing MAT-file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error reopening MAT-file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 3, heli_q8_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error writing header for ans to MAT-file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_M,
                          "Error closing MAT-file p4tx_kalman-wrong-initialization-of-e-offset_e.mat");
        return;
      }

      heli_q8_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S17>/Game Controller' */

  /* S-Function Block: heli_q8/Reference values/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_q8_P.GameController_Enabled) {
      game_controller_close(heli_q8_DW.GameController_Controller);
      heli_q8_DW.GameController_Controller = NULL;
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  heli_q8_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  heli_q8_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  heli_q8_initialize();
}

void MdlTerminate(void)
{
  heli_q8_terminate();
}

/* Registration function */
RT_MODEL_heli_q8_T *heli_q8(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)heli_q8_M, 0,
                sizeof(RT_MODEL_heli_q8_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&heli_q8_M->solverInfo, &heli_q8_M->Timing.simTimeStep);
    rtsiSetTPtr(&heli_q8_M->solverInfo, &rtmGetTPtr(heli_q8_M));
    rtsiSetStepSizePtr(&heli_q8_M->solverInfo, &heli_q8_M->Timing.stepSize0);
    rtsiSetdXPtr(&heli_q8_M->solverInfo, &heli_q8_M->ModelData.derivs);
    rtsiSetContStatesPtr(&heli_q8_M->solverInfo, (real_T **)
                         &heli_q8_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&heli_q8_M->solverInfo,
      &heli_q8_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&heli_q8_M->solverInfo, (&rtmGetErrorStatus(heli_q8_M)));
    rtsiSetRTModelPtr(&heli_q8_M->solverInfo, heli_q8_M);
  }

  rtsiSetSimTimeStep(&heli_q8_M->solverInfo, MAJOR_TIME_STEP);
  heli_q8_M->ModelData.intgData.f[0] = heli_q8_M->ModelData.odeF[0];
  heli_q8_M->ModelData.contStates = ((real_T *) &heli_q8_X);
  rtsiSetSolverData(&heli_q8_M->solverInfo, (void *)
                    &heli_q8_M->ModelData.intgData);
  rtsiSetSolverName(&heli_q8_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = heli_q8_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    heli_q8_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    heli_q8_M->Timing.sampleTimes = (&heli_q8_M->Timing.sampleTimesArray[0]);
    heli_q8_M->Timing.offsetTimes = (&heli_q8_M->Timing.offsetTimesArray[0]);

    /* task periods */
    heli_q8_M->Timing.sampleTimes[0] = (0.0);
    heli_q8_M->Timing.sampleTimes[1] = (0.002);
    heli_q8_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    heli_q8_M->Timing.offsetTimes[0] = (0.0);
    heli_q8_M->Timing.offsetTimes[1] = (0.0);
    heli_q8_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(heli_q8_M, &heli_q8_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = heli_q8_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = heli_q8_M->Timing.perTaskSampleHitsArray;
    heli_q8_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    heli_q8_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(heli_q8_M, -1);
  heli_q8_M->Timing.stepSize0 = 0.002;
  heli_q8_M->Timing.stepSize1 = 0.002;
  heli_q8_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  heli_q8_M->Sizes.checksums[0] = (362425750U);
  heli_q8_M->Sizes.checksums[1] = (1278369170U);
  heli_q8_M->Sizes.checksums[2] = (1585400086U);
  heli_q8_M->Sizes.checksums[3] = (35240508U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[11];
    heli_q8_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(heli_q8_M->extModeInfo,
      &heli_q8_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(heli_q8_M->extModeInfo, heli_q8_M->Sizes.checksums);
    rteiSetTPtr(heli_q8_M->extModeInfo, rtmGetTPtr(heli_q8_M));
  }

  heli_q8_M->solverInfoPtr = (&heli_q8_M->solverInfo);
  heli_q8_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&heli_q8_M->solverInfo, 0.002);
  rtsiSetSolverMode(&heli_q8_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  heli_q8_M->ModelData.blockIO = ((void *) &heli_q8_B);
  (void) memset(((void *) &heli_q8_B), 0,
                sizeof(B_heli_q8_T));

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      heli_q8_B.Switch[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_B.x_k[i] = 0.0;
    }

    for (i = 0; i < 30; i++) {
      heli_q8_B.Constant5[i] = 0.0;
    }

    for (i = 0; i < 10; i++) {
      heli_q8_B.Constant_e[i] = 0.0;
    }

    for (i = 0; i < 36; i++) {
      heli_q8_B.Constant6[i] = 0.0;
    }

    for (i = 0; i < 12; i++) {
      heli_q8_B.Constant7[i] = 0.0;
    }

    for (i = 0; i < 30; i++) {
      heli_q8_B.K_k[i] = 0.0;
    }

    for (i = 0; i < 36; i++) {
      heli_q8_B.P_pred_k_plus_1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_B.x_pred_k_plus_1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_B.x_est_k[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_B.P_est_k_diag[i] = 0.0;
    }

    heli_q8_B.Gain1[0] = 0.0;
    heli_q8_B.Gain1[1] = 0.0;
    heli_q8_B.Gain1[2] = 0.0;
    heli_q8_B.Gain2[0] = 0.0;
    heli_q8_B.Gain2[1] = 0.0;
    heli_q8_B.Gain2[2] = 0.0;
    heli_q8_B.Memory2 = 0.0;
    heli_q8_B.Constant = 0.0;
    heli_q8_B.Constant1 = 0.0;
    heli_q8_B.Constant2 = 0.0;
    heli_q8_B.ElevationCounttorad = 0.0;
    heli_q8_B.ManualSwitch = 0.0;
    heli_q8_B.TmpSignalConversionAtToFileInpo[0] = 0.0;
    heli_q8_B.TmpSignalConversionAtToFileInpo[1] = 0.0;
    heli_q8_B.ElevationTransferFcn = 0.0;
    heli_q8_B.RateTransitiony = 0.0;
    heli_q8_B.Joystick_gain_y = 0.0;
    heli_q8_B.PitchCounttorad = 0.0;
    heli_q8_B.PitchTransferFcn = 0.0;
    heli_q8_B.TransferFcn = 0.0;
    heli_q8_B.TravelCounttorad = 0.0;
    heli_q8_B.TravelTransferFcn = 0.0;
    heli_q8_B.Integrator2[0] = 0.0;
    heli_q8_B.Integrator2[1] = 0.0;
    heli_q8_B.TransferFcn_m = 0.0;
    heli_q8_B.Constant1_j[0] = 0.0;
    heli_q8_B.Constant1_j[1] = 0.0;
    heli_q8_B.Constant1_j[2] = 0.0;
    heli_q8_B.Constant1_j[3] = 0.0;
    heli_q8_B.Sum = 0.0;
    heli_q8_B.Sum2 = 0.0;
    heli_q8_B.Vs_offset = 0.0;
    heli_q8_B.FrontmotorSaturation = 0.0;
    heli_q8_B.BackmotorSaturation = 0.0;
    heli_q8_B.RateTransitionx = 0.0;
    heli_q8_B.Joystick_gain_x = 0.0;
    heli_q8_B.GameController_o4 = 0.0;
    heli_q8_B.GameController_o5 = 0.0;
    heli_q8_B.euler_angles[0] = 0.0;
    heli_q8_B.euler_angles[1] = 0.0;
    heli_q8_B.euler_angles[2] = 0.0;
  }

  /* parameters */
  heli_q8_M->ModelData.defaultParam = ((real_T *)&heli_q8_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &heli_q8_X;
    heli_q8_M->ModelData.contStates = (x);
    (void) memset((void *)&heli_q8_X, 0,
                  sizeof(X_heli_q8_T));
  }

  /* states (dwork) */
  heli_q8_M->ModelData.dwork = ((void *) &heli_q8_DW);
  (void) memset((void *)&heli_q8_DW, 0,
                sizeof(DW_heli_q8_T));

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      heli_q8_DW.UnitDelay_DSTATE[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 36; i++) {
      heli_q8_DW.UnitDelay1_DSTATE[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      heli_q8_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  heli_q8_DW.Memory2_PreviousInput = 0.0;
  heli_q8_DW.l_dot = 0.0;
  heli_q8_DW.RateTransitiony_Buffer0 = 0.0;
  heli_q8_DW.HILWriteAnalog_Buffer[0] = 0.0;
  heli_q8_DW.HILWriteAnalog_Buffer[1] = 0.0;
  heli_q8_DW.RateTransitionx_Buffer0 = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    heli_q8_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  heli_q8_M->Sizes.numContStates = (9);/* Number of continuous states */
  heli_q8_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  heli_q8_M->Sizes.numY = (0);         /* Number of model outputs */
  heli_q8_M->Sizes.numU = (0);         /* Number of model inputs */
  heli_q8_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  heli_q8_M->Sizes.numSampTimes = (3); /* Number of sample times */
  heli_q8_M->Sizes.numBlocks = (124);  /* Number of blocks */
  heli_q8_M->Sizes.numBlockIO = (42);  /* Number of block outputs */
  heli_q8_M->Sizes.numBlockPrms = (602);/* Sum of parameter "widths" */
  return heli_q8_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
