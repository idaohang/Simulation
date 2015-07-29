/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ekf_trial_sfun.h"
#include "c4_ekf_trial.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ekf_trial_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c4_debug_family_names[10] = { "nargin", "nargout", "Ad",
  "Bd", "x_hat_kp", "u_kp", "P_hat_kp", "Q", "x_hat_k", "P_hat_k" };

/* Function Declarations */
static void initialize_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance);
static void initialize_params_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance);
static void enable_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance);
static void disable_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance);
static void set_sim_state_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void finalize_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance);
static void sf_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance);
static void c4_chartstep_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance);
static void initSimStructsc4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance);
static void registerMessagesc4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static void c4_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_P_hat_k, const char_T *c4_identifier, real_T c4_y[4]);
static void c4_b_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[4]);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_c_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_x_hat_k, const char_T *c4_identifier, real_T c4_y[2]);
static void c4_d_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2]);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_e_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_eml_scalar_eg(SFc4_ekf_trialInstanceStruct *chartInstance);
static void c4_b_eml_scalar_eg(SFc4_ekf_trialInstanceStruct *chartInstance);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_f_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_g_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_ekf_trial, const char_T *c4_identifier);
static uint8_T c4_h_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_ekf_trialInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_ekf_trial = 0U;
}

static void initialize_params_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance)
{
}

static void enable_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i0;
  real_T c4_u[4];
  const mxArray *c4_b_y = NULL;
  int32_T c4_i1;
  real_T c4_b_u[2];
  const mxArray *c4_c_y = NULL;
  uint8_T c4_hoistedGlobal;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real_T (*c4_x_hat_k)[2];
  real_T (*c4_P_hat_k)[4];
  c4_P_hat_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_x_hat_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(3), FALSE);
  for (c4_i0 = 0; c4_i0 < 4; c4_i0++) {
    c4_u[c4_i0] = (*c4_P_hat_k)[c4_i0];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i1 = 0; c4_i1 < 2; c4_i1++) {
    c4_b_u[c4_i1] = (*c4_x_hat_k)[c4_i1];
  }

  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_hoistedGlobal = chartInstance->c4_is_active_c4_ekf_trial;
  c4_c_u = c4_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y, FALSE);
  return c4_st;
}

static void set_sim_state_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[4];
  int32_T c4_i2;
  real_T c4_dv1[2];
  int32_T c4_i3;
  real_T (*c4_P_hat_k)[4];
  real_T (*c4_x_hat_k)[2];
  c4_P_hat_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_x_hat_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
                      "P_hat_k", c4_dv0);
  for (c4_i2 = 0; c4_i2 < 4; c4_i2++) {
    (*c4_P_hat_k)[c4_i2] = c4_dv0[c4_i2];
  }

  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                        "x_hat_k", c4_dv1);
  for (c4_i3 = 0; c4_i3 < 2; c4_i3++) {
    (*c4_x_hat_k)[c4_i3] = c4_dv1[c4_i3];
  }

  chartInstance->c4_is_active_c4_ekf_trial = c4_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 2)), "is_active_c4_ekf_trial");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_ekf_trial(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance)
{
}

static void sf_c4_ekf_trial(SFc4_ekf_trialInstanceStruct *chartInstance)
{
  int32_T c4_i4;
  int32_T c4_i5;
  int32_T c4_i6;
  int32_T c4_i7;
  int32_T c4_i8;
  int32_T c4_i9;
  int32_T c4_i10;
  real_T *c4_u_kp;
  real_T (*c4_Q)[4];
  real_T (*c4_P_hat_kp)[4];
  real_T (*c4_x_hat_kp)[2];
  real_T (*c4_Bd)[2];
  real_T (*c4_Ad)[4];
  real_T (*c4_P_hat_k)[4];
  real_T (*c4_x_hat_k)[2];
  c4_Q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 5);
  c4_P_hat_kp = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c4_u_kp = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_x_hat_kp = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c4_Bd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c4_Ad = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  c4_P_hat_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_x_hat_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i4 = 0; c4_i4 < 2; c4_i4++) {
    _SFD_DATA_RANGE_CHECK((*c4_x_hat_k)[c4_i4], 0U);
  }

  for (c4_i5 = 0; c4_i5 < 4; c4_i5++) {
    _SFD_DATA_RANGE_CHECK((*c4_P_hat_k)[c4_i5], 1U);
  }

  for (c4_i6 = 0; c4_i6 < 4; c4_i6++) {
    _SFD_DATA_RANGE_CHECK((*c4_Ad)[c4_i6], 2U);
  }

  for (c4_i7 = 0; c4_i7 < 2; c4_i7++) {
    _SFD_DATA_RANGE_CHECK((*c4_Bd)[c4_i7], 3U);
  }

  for (c4_i8 = 0; c4_i8 < 2; c4_i8++) {
    _SFD_DATA_RANGE_CHECK((*c4_x_hat_kp)[c4_i8], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c4_u_kp, 5U);
  for (c4_i9 = 0; c4_i9 < 4; c4_i9++) {
    _SFD_DATA_RANGE_CHECK((*c4_P_hat_kp)[c4_i9], 6U);
  }

  for (c4_i10 = 0; c4_i10 < 4; c4_i10++) {
    _SFD_DATA_RANGE_CHECK((*c4_Q)[c4_i10], 7U);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_ekf_trial(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ekf_trialMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c4_chartstep_c4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance)
{
  real_T c4_hoistedGlobal;
  int32_T c4_i11;
  real_T c4_Ad[4];
  int32_T c4_i12;
  real_T c4_Bd[2];
  int32_T c4_i13;
  real_T c4_x_hat_kp[2];
  real_T c4_u_kp;
  int32_T c4_i14;
  real_T c4_P_hat_kp[4];
  int32_T c4_i15;
  real_T c4_Q[4];
  uint32_T c4_debug_family_var_map[10];
  real_T c4_nargin = 6.0;
  real_T c4_nargout = 2.0;
  real_T c4_x_hat_k[2];
  real_T c4_P_hat_k[4];
  int32_T c4_i16;
  real_T c4_a[4];
  int32_T c4_i17;
  real_T c4_b[2];
  int32_T c4_i18;
  real_T c4_y[2];
  int32_T c4_i19;
  int32_T c4_i20;
  int32_T c4_i21;
  real_T c4_b_b;
  int32_T c4_i22;
  int32_T c4_i23;
  int32_T c4_i24;
  int32_T c4_i25;
  real_T c4_c_b[4];
  int32_T c4_i26;
  int32_T c4_i27;
  int32_T c4_i28;
  real_T c4_b_y[4];
  int32_T c4_i29;
  int32_T c4_i30;
  int32_T c4_i31;
  int32_T c4_i32;
  int32_T c4_i33;
  int32_T c4_i34;
  int32_T c4_i35;
  int32_T c4_i36;
  int32_T c4_i37;
  int32_T c4_i38;
  int32_T c4_i39;
  int32_T c4_i40;
  int32_T c4_i41;
  int32_T c4_i42;
  real_T *c4_b_u_kp;
  real_T (*c4_b_x_hat_k)[2];
  real_T (*c4_b_P_hat_k)[4];
  real_T (*c4_b_Q)[4];
  real_T (*c4_b_P_hat_kp)[4];
  real_T (*c4_b_x_hat_kp)[2];
  real_T (*c4_b_Bd)[2];
  real_T (*c4_b_Ad)[4];
  c4_b_Q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 5);
  c4_b_P_hat_kp = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
  c4_b_u_kp = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_b_x_hat_kp = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_Bd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_Ad = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  c4_b_P_hat_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c4_b_x_hat_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_u_kp;
  for (c4_i11 = 0; c4_i11 < 4; c4_i11++) {
    c4_Ad[c4_i11] = (*c4_b_Ad)[c4_i11];
  }

  for (c4_i12 = 0; c4_i12 < 2; c4_i12++) {
    c4_Bd[c4_i12] = (*c4_b_Bd)[c4_i12];
  }

  for (c4_i13 = 0; c4_i13 < 2; c4_i13++) {
    c4_x_hat_kp[c4_i13] = (*c4_b_x_hat_kp)[c4_i13];
  }

  c4_u_kp = c4_hoistedGlobal;
  for (c4_i14 = 0; c4_i14 < 4; c4_i14++) {
    c4_P_hat_kp[c4_i14] = (*c4_b_P_hat_kp)[c4_i14];
  }

  for (c4_i15 = 0; c4_i15 < 4; c4_i15++) {
    c4_Q[c4_i15] = (*c4_b_Q)[c4_i15];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_Ad, 2U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_Bd, 3U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_x_hat_kp, 4U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_u_kp, 5U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_P_hat_kp, 6U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_Q, 7U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_x_hat_k, 8U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_P_hat_k, 9U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 4);
  for (c4_i16 = 0; c4_i16 < 4; c4_i16++) {
    c4_a[c4_i16] = c4_Ad[c4_i16];
  }

  for (c4_i17 = 0; c4_i17 < 2; c4_i17++) {
    c4_b[c4_i17] = c4_x_hat_kp[c4_i17];
  }

  c4_eml_scalar_eg(chartInstance);
  c4_eml_scalar_eg(chartInstance);
  for (c4_i18 = 0; c4_i18 < 2; c4_i18++) {
    c4_y[c4_i18] = 0.0;
    c4_i19 = 0;
    for (c4_i20 = 0; c4_i20 < 2; c4_i20++) {
      c4_y[c4_i18] += c4_a[c4_i19 + c4_i18] * c4_b[c4_i20];
      c4_i19 += 2;
    }
  }

  for (c4_i21 = 0; c4_i21 < 2; c4_i21++) {
    c4_b[c4_i21] = c4_Bd[c4_i21];
  }

  c4_b_b = c4_u_kp;
  for (c4_i22 = 0; c4_i22 < 2; c4_i22++) {
    c4_b[c4_i22] *= c4_b_b;
  }

  for (c4_i23 = 0; c4_i23 < 2; c4_i23++) {
    c4_x_hat_k[c4_i23] = c4_y[c4_i23] + c4_b[c4_i23];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 6);
  for (c4_i24 = 0; c4_i24 < 4; c4_i24++) {
    c4_a[c4_i24] = c4_Ad[c4_i24];
  }

  for (c4_i25 = 0; c4_i25 < 4; c4_i25++) {
    c4_c_b[c4_i25] = c4_P_hat_kp[c4_i25];
  }

  c4_b_eml_scalar_eg(chartInstance);
  c4_b_eml_scalar_eg(chartInstance);
  for (c4_i26 = 0; c4_i26 < 2; c4_i26++) {
    c4_i27 = 0;
    for (c4_i28 = 0; c4_i28 < 2; c4_i28++) {
      c4_b_y[c4_i27 + c4_i26] = 0.0;
      c4_i29 = 0;
      for (c4_i30 = 0; c4_i30 < 2; c4_i30++) {
        c4_b_y[c4_i27 + c4_i26] += c4_a[c4_i29 + c4_i26] * c4_c_b[c4_i30 +
          c4_i27];
        c4_i29 += 2;
      }

      c4_i27 += 2;
    }
  }

  c4_i31 = 0;
  for (c4_i32 = 0; c4_i32 < 2; c4_i32++) {
    c4_i33 = 0;
    for (c4_i34 = 0; c4_i34 < 2; c4_i34++) {
      c4_c_b[c4_i34 + c4_i31] = c4_Ad[c4_i33 + c4_i32];
      c4_i33 += 2;
    }

    c4_i31 += 2;
  }

  c4_b_eml_scalar_eg(chartInstance);
  c4_b_eml_scalar_eg(chartInstance);
  for (c4_i35 = 0; c4_i35 < 2; c4_i35++) {
    c4_i36 = 0;
    for (c4_i37 = 0; c4_i37 < 2; c4_i37++) {
      c4_a[c4_i36 + c4_i35] = 0.0;
      c4_i38 = 0;
      for (c4_i39 = 0; c4_i39 < 2; c4_i39++) {
        c4_a[c4_i36 + c4_i35] += c4_b_y[c4_i38 + c4_i35] * c4_c_b[c4_i39 +
          c4_i36];
        c4_i38 += 2;
      }

      c4_i36 += 2;
    }
  }

  for (c4_i40 = 0; c4_i40 < 4; c4_i40++) {
    c4_P_hat_k[c4_i40] = c4_a[c4_i40] + c4_Q[c4_i40];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i41 = 0; c4_i41 < 2; c4_i41++) {
    (*c4_b_x_hat_k)[c4_i41] = c4_x_hat_k[c4_i41];
  }

  for (c4_i42 = 0; c4_i42 < 4; c4_i42++) {
    (*c4_b_P_hat_k)[c4_i42] = c4_P_hat_k[c4_i42];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc4_ekf_trial(SFc4_ekf_trialInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i43;
  int32_T c4_i44;
  int32_T c4_i45;
  real_T c4_b_inData[4];
  int32_T c4_i46;
  int32_T c4_i47;
  int32_T c4_i48;
  real_T c4_u[4];
  const mxArray *c4_y = NULL;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i43 = 0;
  for (c4_i44 = 0; c4_i44 < 2; c4_i44++) {
    for (c4_i45 = 0; c4_i45 < 2; c4_i45++) {
      c4_b_inData[c4_i45 + c4_i43] = (*(real_T (*)[4])c4_inData)[c4_i45 + c4_i43];
    }

    c4_i43 += 2;
  }

  c4_i46 = 0;
  for (c4_i47 = 0; c4_i47 < 2; c4_i47++) {
    for (c4_i48 = 0; c4_i48 < 2; c4_i48++) {
      c4_u[c4_i48 + c4_i46] = c4_b_inData[c4_i48 + c4_i46];
    }

    c4_i46 += 2;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_P_hat_k, const char_T *c4_identifier, real_T c4_y[4])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_P_hat_k), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_P_hat_k);
}

static void c4_b_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[4])
{
  real_T c4_dv2[4];
  int32_T c4_i49;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv2, 1, 0, 0U, 1, 0U, 2, 2, 2);
  for (c4_i49 = 0; c4_i49 < 4; c4_i49++) {
    c4_y[c4_i49] = c4_dv2[c4_i49];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_P_hat_k;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[4];
  int32_T c4_i50;
  int32_T c4_i51;
  int32_T c4_i52;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_P_hat_k = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_P_hat_k), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_P_hat_k);
  c4_i50 = 0;
  for (c4_i51 = 0; c4_i51 < 2; c4_i51++) {
    for (c4_i52 = 0; c4_i52 < 2; c4_i52++) {
      (*(real_T (*)[4])c4_outData)[c4_i52 + c4_i50] = c4_y[c4_i52 + c4_i50];
    }

    c4_i50 += 2;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i53;
  real_T c4_b_inData[2];
  int32_T c4_i54;
  real_T c4_u[2];
  const mxArray *c4_y = NULL;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i53 = 0; c4_i53 < 2; c4_i53++) {
    c4_b_inData[c4_i53] = (*(real_T (*)[2])c4_inData)[c4_i53];
  }

  for (c4_i54 = 0; c4_i54 < 2; c4_i54++) {
    c4_u[c4_i54] = c4_b_inData[c4_i54];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_c_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_x_hat_k, const char_T *c4_identifier, real_T c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_x_hat_k), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_x_hat_k);
}

static void c4_d_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2])
{
  real_T c4_dv3[2];
  int32_T c4_i55;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv3, 1, 0, 0U, 1, 0U, 1, 2);
  for (c4_i55 = 0; c4_i55 < 2; c4_i55++) {
    c4_y[c4_i55] = c4_dv3[c4_i55];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_x_hat_k;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[2];
  int32_T c4_i56;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_x_hat_k = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_x_hat_k), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_x_hat_k);
  for (c4_i56 = 0; c4_i56 < 2; c4_i56++) {
    (*(real_T (*)[2])c4_outData)[c4_i56] = c4_y[c4_i56];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_e_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_ekf_trial_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[9];
  c4_ResolvedFunctionInfo (*c4_b_info)[9];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i57;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_b_info = (c4_ResolvedFunctionInfo (*)[9])c4_info;
  (*c4_b_info)[0].context = "";
  (*c4_b_info)[0].name = "mtimes";
  (*c4_b_info)[0].dominantType = "double";
  (*c4_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c4_b_info)[0].fileTimeLo = 1289552092U;
  (*c4_b_info)[0].fileTimeHi = 0U;
  (*c4_b_info)[0].mFileTimeLo = 0U;
  (*c4_b_info)[0].mFileTimeHi = 0U;
  (*c4_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c4_b_info)[1].name = "eml_index_class";
  (*c4_b_info)[1].dominantType = "";
  (*c4_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c4_b_info)[1].fileTimeLo = 1323202978U;
  (*c4_b_info)[1].fileTimeHi = 0U;
  (*c4_b_info)[1].mFileTimeLo = 0U;
  (*c4_b_info)[1].mFileTimeHi = 0U;
  (*c4_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c4_b_info)[2].name = "eml_scalar_eg";
  (*c4_b_info)[2].dominantType = "double";
  (*c4_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c4_b_info)[2].fileTimeLo = 1286851196U;
  (*c4_b_info)[2].fileTimeHi = 0U;
  (*c4_b_info)[2].mFileTimeLo = 0U;
  (*c4_b_info)[2].mFileTimeHi = 0U;
  (*c4_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c4_b_info)[3].name = "eml_xgemm";
  (*c4_b_info)[3].dominantType = "char";
  (*c4_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  (*c4_b_info)[3].fileTimeLo = 1299109172U;
  (*c4_b_info)[3].fileTimeHi = 0U;
  (*c4_b_info)[3].mFileTimeLo = 0U;
  (*c4_b_info)[3].mFileTimeHi = 0U;
  (*c4_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  (*c4_b_info)[4].name = "eml_blas_inline";
  (*c4_b_info)[4].dominantType = "";
  (*c4_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  (*c4_b_info)[4].fileTimeLo = 1299109168U;
  (*c4_b_info)[4].fileTimeHi = 0U;
  (*c4_b_info)[4].mFileTimeLo = 0U;
  (*c4_b_info)[4].mFileTimeHi = 0U;
  (*c4_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  (*c4_b_info)[5].name = "mtimes";
  (*c4_b_info)[5].dominantType = "double";
  (*c4_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c4_b_info)[5].fileTimeLo = 1289552092U;
  (*c4_b_info)[5].fileTimeHi = 0U;
  (*c4_b_info)[5].mFileTimeLo = 0U;
  (*c4_b_info)[5].mFileTimeHi = 0U;
  (*c4_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  (*c4_b_info)[6].name = "eml_index_class";
  (*c4_b_info)[6].dominantType = "";
  (*c4_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*c4_b_info)[6].fileTimeLo = 1323202978U;
  (*c4_b_info)[6].fileTimeHi = 0U;
  (*c4_b_info)[6].mFileTimeLo = 0U;
  (*c4_b_info)[6].mFileTimeHi = 0U;
  (*c4_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  (*c4_b_info)[7].name = "eml_scalar_eg";
  (*c4_b_info)[7].dominantType = "double";
  (*c4_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c4_b_info)[7].fileTimeLo = 1286851196U;
  (*c4_b_info)[7].fileTimeHi = 0U;
  (*c4_b_info)[7].mFileTimeLo = 0U;
  (*c4_b_info)[7].mFileTimeHi = 0U;
  (*c4_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  (*c4_b_info)[8].name = "eml_refblas_xgemm";
  (*c4_b_info)[8].dominantType = "char";
  (*c4_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  (*c4_b_info)[8].fileTimeLo = 1299109174U;
  (*c4_b_info)[8].fileTimeHi = 0U;
  (*c4_b_info)[8].mFileTimeLo = 0U;
  (*c4_b_info)[8].mFileTimeHi = 0U;
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 9), FALSE);
  for (c4_i57 = 0; c4_i57 < 9; c4_i57++) {
    c4_r0 = &c4_info[c4_i57];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i57);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i57);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_eml_scalar_eg(SFc4_ekf_trialInstanceStruct *chartInstance)
{
}

static void c4_b_eml_scalar_eg(SFc4_ekf_trialInstanceStruct *chartInstance)
{
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static int32_T c4_f_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i58;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i58, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i58;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_g_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_ekf_trial, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_ekf_trial), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_ekf_trial);
  return c4_y;
}

static uint8_T c4_h_emlrt_marshallIn(SFc4_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_ekf_trialInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c4_ekf_trial_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(428611666U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2205529384U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2777450578U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1745757326U);
}

mxArray *sf_c4_ekf_trial_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("yWaw9gOL9g475vGApRHyVE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(2);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_ekf_trial_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c4_ekf_trial(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[7],T\"P_hat_k\",},{M[1],M[4],T\"x_hat_k\",},{M[8],M[0],T\"is_active_c4_ekf_trial\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_ekf_trial_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_ekf_trialInstanceStruct *chartInstance;
    chartInstance = (SFc4_ekf_trialInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ekf_trialMachineNumber_,
           4,
           1,
           1,
           8,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_ekf_trialMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ekf_trialMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ekf_trialMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"x_hat_k");
          _SFD_SET_DATA_PROPS(1,2,0,1,"P_hat_k");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Ad");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Bd");
          _SFD_SET_DATA_PROPS(4,1,1,0,"x_hat_kp");
          _SFD_SET_DATA_PROPS(5,1,1,0,"u_kp");
          _SFD_SET_DATA_PROPS(6,1,1,0,"P_hat_kp");
          _SFD_SET_DATA_PROPS(7,1,1,0,"Q");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,140);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)
            c4_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c4_u_kp;
          real_T (*c4_x_hat_k)[2];
          real_T (*c4_P_hat_k)[4];
          real_T (*c4_Ad)[4];
          real_T (*c4_Bd)[2];
          real_T (*c4_x_hat_kp)[2];
          real_T (*c4_P_hat_kp)[4];
          real_T (*c4_Q)[4];
          c4_Q = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 5);
          c4_P_hat_kp = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 4);
          c4_u_kp = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c4_x_hat_kp = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 2);
          c4_Bd = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
          c4_Ad = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          c4_P_hat_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
          c4_x_hat_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, *c4_x_hat_k);
          _SFD_SET_DATA_VALUE_PTR(1U, *c4_P_hat_k);
          _SFD_SET_DATA_VALUE_PTR(2U, *c4_Ad);
          _SFD_SET_DATA_VALUE_PTR(3U, *c4_Bd);
          _SFD_SET_DATA_VALUE_PTR(4U, *c4_x_hat_kp);
          _SFD_SET_DATA_VALUE_PTR(5U, c4_u_kp);
          _SFD_SET_DATA_VALUE_PTR(6U, *c4_P_hat_kp);
          _SFD_SET_DATA_VALUE_PTR(7U, *c4_Q);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ekf_trialMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "cuygSHqpBB4NUdsR3ria4C";
}

static void sf_opaque_initialize_c4_ekf_trial(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_ekf_trialInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*)
    chartInstanceVar);
  initialize_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_ekf_trial(void *chartInstanceVar)
{
  enable_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_ekf_trial(void *chartInstanceVar)
{
  disable_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_ekf_trial(void *chartInstanceVar)
{
  sf_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_ekf_trial(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_ekf_trial();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c4_ekf_trial(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_ekf_trial();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_ekf_trial(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_ekf_trial(S);
}

static void sf_opaque_set_sim_state_c4_ekf_trial(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c4_ekf_trial(S, st);
}

static void sf_opaque_terminate_c4_ekf_trial(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_ekf_trialInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ekf_trial_optimization_info();
    }

    finalize_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_ekf_trial((SFc4_ekf_trialInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_ekf_trial(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_ekf_trial((SFc4_ekf_trialInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_ekf_trial(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ekf_trial_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,4,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1111579383U));
  ssSetChecksum1(S,(3245055154U));
  ssSetChecksum2(S,(4282962771U));
  ssSetChecksum3(S,(109114196U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_ekf_trial(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_ekf_trial(SimStruct *S)
{
  SFc4_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc4_ekf_trialInstanceStruct *)utMalloc(sizeof
    (SFc4_ekf_trialInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_ekf_trialInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_ekf_trial;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_ekf_trial;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_ekf_trial;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_ekf_trial;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_ekf_trial;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_ekf_trial;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_ekf_trial;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_ekf_trial;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_ekf_trial;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_ekf_trial;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_ekf_trial;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c4_ekf_trial_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_ekf_trial(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_ekf_trial(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_ekf_trial(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_ekf_trial_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
