/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ekf_trial_sfun.h"
#include "c3_ekf_trial.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ekf_trial_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[11] = { "C", "K", "nargin", "nargout",
  "x_hat_k", "P_hat_k", "y_hat_k", "y_k", "R", "x_k_k", "P_k_k" };

/* Function Declarations */
static void initialize_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance);
static void initialize_params_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance);
static void enable_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance);
static void disable_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance);
static void set_sim_state_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance);
static void sf_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance);
static void c3_chartstep_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance);
static void initSimStructsc3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance);
static void registerMessagesc3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_P_k_k, const char_T *c3_identifier, real_T c3_y[4]);
static void c3_b_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_x_k_k, const char_T *c3_identifier, real_T c3_y[2]);
static void c3_d_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2]);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_e_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[55]);
static void c3_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance);
static void c3_b_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance);
static void c3_c_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance);
static real_T c3_inv(SFc3_ekf_trialInstanceStruct *chartInstance, real_T c3_x);
static void c3_eml_warning(SFc3_ekf_trialInstanceStruct *chartInstance);
static void c3_b_eml_warning(SFc3_ekf_trialInstanceStruct *chartInstance, char_T
  c3_varargin_2[14]);
static void c3_d_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance);
static void c3_f_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_sprintf, const char_T *c3_identifier, char_T c3_y[14]);
static void c3_g_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, char_T c3_y[14]);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_h_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_i_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_ekf_trial, const char_T *c3_identifier);
static uint8_T c3_j_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_ekf_trialInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_ekf_trial = 0U;
}

static void initialize_params_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance)
{
}

static void enable_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real_T c3_u[4];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i1;
  real_T c3_b_u[2];
  const mxArray *c3_c_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  real_T (*c3_x_k_k)[2];
  real_T (*c3_P_k_k)[4];
  c3_P_k_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_x_k_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(3), FALSE);
  for (c3_i0 = 0; c3_i0 < 4; c3_i0++) {
    c3_u[c3_i0] = (*c3_P_k_k)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i1 = 0; c3_i1 < 2; c3_i1++) {
    c3_b_u[c3_i1] = (*c3_x_k_k)[c3_i1];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_ekf_trial;
  c3_c_u = c3_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  sf_mex_assign(&c3_st, c3_y, FALSE);
  return c3_st;
}

static void set_sim_state_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[4];
  int32_T c3_i2;
  real_T c3_dv1[2];
  int32_T c3_i3;
  real_T (*c3_P_k_k)[4];
  real_T (*c3_x_k_k)[2];
  c3_P_k_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_x_k_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                      "P_k_k", c3_dv0);
  for (c3_i2 = 0; c3_i2 < 4; c3_i2++) {
    (*c3_P_k_k)[c3_i2] = c3_dv0[c3_i2];
  }

  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "x_k_k", c3_dv1);
  for (c3_i3 = 0; c3_i3 < 2; c3_i3++) {
    (*c3_x_k_k)[c3_i3] = c3_dv1[c3_i3];
  }

  chartInstance->c3_is_active_c3_ekf_trial = c3_i_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 2)), "is_active_c3_ekf_trial");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_ekf_trial(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance)
{
}

static void sf_c3_ekf_trial(SFc3_ekf_trialInstanceStruct *chartInstance)
{
  int32_T c3_i4;
  int32_T c3_i5;
  int32_T c3_i6;
  int32_T c3_i7;
  real_T *c3_y_hat_k;
  real_T *c3_y_k;
  real_T *c3_R;
  real_T (*c3_P_k_k)[4];
  real_T (*c3_x_k_k)[2];
  real_T (*c3_P_hat_k)[4];
  real_T (*c3_x_hat_k)[2];
  c3_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c3_P_k_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_x_k_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_y_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_y_hat_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_P_hat_k = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c3_x_hat_k = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i4 = 0; c3_i4 < 2; c3_i4++) {
    _SFD_DATA_RANGE_CHECK((*c3_x_hat_k)[c3_i4], 0U);
  }

  for (c3_i5 = 0; c3_i5 < 4; c3_i5++) {
    _SFD_DATA_RANGE_CHECK((*c3_P_hat_k)[c3_i5], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_y_hat_k, 2U);
  _SFD_DATA_RANGE_CHECK(*c3_y_k, 3U);
  for (c3_i6 = 0; c3_i6 < 2; c3_i6++) {
    _SFD_DATA_RANGE_CHECK((*c3_x_k_k)[c3_i6], 4U);
  }

  for (c3_i7 = 0; c3_i7 < 4; c3_i7++) {
    _SFD_DATA_RANGE_CHECK((*c3_P_k_k)[c3_i7], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_R, 6U);
  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_ekf_trial(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ekf_trialMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance)
{
  real_T c3_hoistedGlobal;
  real_T c3_b_hoistedGlobal;
  real_T c3_c_hoistedGlobal;
  int32_T c3_i8;
  real_T c3_x_hat_k[2];
  int32_T c3_i9;
  real_T c3_P_hat_k[4];
  real_T c3_y_hat_k;
  real_T c3_y_k;
  real_T c3_R;
  uint32_T c3_debug_family_var_map[11];
  real_T c3_C[2];
  real_T c3_K[2];
  real_T c3_nargin = 5.0;
  real_T c3_nargout = 2.0;
  real_T c3_x_k_k[2];
  real_T c3_P_k_k[4];
  int32_T c3_i10;
  int32_T c3_i11;
  real_T c3_a[4];
  int32_T c3_i12;
  real_T c3_y[2];
  int32_T c3_i13;
  int32_T c3_i14;
  int32_T c3_i15;
  int32_T c3_i16;
  int32_T c3_i17;
  real_T c3_b_y[2];
  int32_T c3_i18;
  real_T c3_c_y;
  int32_T c3_k;
  int32_T c3_b_k;
  real_T c3_b;
  int32_T c3_i19;
  int32_T c3_i20;
  real_T c3_b_b;
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  real_T c3_I[4];
  int32_T c3_i;
  int32_T c3_b_i;
  int32_T c3_i24;
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  int32_T c3_i31;
  int32_T c3_i32;
  real_T c3_b_C[4];
  int32_T c3_i33;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  int32_T c3_i40;
  int32_T c3_i41;
  int32_T c3_i42;
  real_T *c3_b_y_hat_k;
  real_T *c3_b_y_k;
  real_T *c3_b_R;
  real_T (*c3_b_x_k_k)[2];
  real_T (*c3_b_P_k_k)[4];
  real_T (*c3_b_P_hat_k)[4];
  real_T (*c3_b_x_hat_k)[2];
  c3_b_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c3_b_P_k_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_x_k_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_y_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_b_y_hat_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_P_hat_k = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_x_hat_k = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  c3_hoistedGlobal = *c3_b_y_hat_k;
  c3_b_hoistedGlobal = *c3_b_y_k;
  c3_c_hoistedGlobal = *c3_b_R;
  for (c3_i8 = 0; c3_i8 < 2; c3_i8++) {
    c3_x_hat_k[c3_i8] = (*c3_b_x_hat_k)[c3_i8];
  }

  for (c3_i9 = 0; c3_i9 < 4; c3_i9++) {
    c3_P_hat_k[c3_i9] = (*c3_b_P_hat_k)[c3_i9];
  }

  c3_y_hat_k = c3_hoistedGlobal;
  c3_y_k = c3_b_hoistedGlobal;
  c3_R = c3_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 11U, 11U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_C, 0U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_K, 1U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 2U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 3U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_x_hat_k, 4U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_P_hat_k, 5U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_y_hat_k, 6U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_y_k, 7U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_R, 8U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_x_k_k, 9U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_P_k_k, 10U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 3);
  for (c3_i10 = 0; c3_i10 < 2; c3_i10++) {
    c3_C[c3_i10] = 1.0 - (real_T)c3_i10;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 5);
  for (c3_i11 = 0; c3_i11 < 4; c3_i11++) {
    c3_a[c3_i11] = c3_P_hat_k[c3_i11];
  }

  c3_eml_scalar_eg(chartInstance);
  c3_eml_scalar_eg(chartInstance);
  for (c3_i12 = 0; c3_i12 < 2; c3_i12++) {
    c3_y[c3_i12] = 0.0;
    c3_i13 = 0;
    for (c3_i14 = 0; c3_i14 < 2; c3_i14++) {
      c3_y[c3_i12] += c3_a[c3_i13 + c3_i12] * (1.0 - (real_T)c3_i14);
      c3_i13 += 2;
    }
  }

  for (c3_i15 = 0; c3_i15 < 4; c3_i15++) {
    c3_a[c3_i15] = c3_P_hat_k[c3_i15];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_i16 = 0;
  for (c3_i17 = 0; c3_i17 < 2; c3_i17++) {
    c3_b_y[c3_i17] = 0.0;
    for (c3_i18 = 0; c3_i18 < 2; c3_i18++) {
      c3_b_y[c3_i17] += (1.0 - (real_T)c3_i18) * c3_a[c3_i18 + c3_i16];
    }

    c3_i16 += 2;
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  c3_c_y = 0.0;
  for (c3_k = 1; c3_k < 3; c3_k++) {
    c3_b_k = c3_k;
    c3_c_y += c3_b_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c3_b_k), 1, 2, 1, 0) - 1] * (1.0 + -(real_T)
      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c3_b_k), 1, 2, 1, 0) - 1));
  }

  c3_b = c3_inv(chartInstance, c3_c_y + c3_R);
  for (c3_i19 = 0; c3_i19 < 2; c3_i19++) {
    c3_K[c3_i19] = c3_y[c3_i19] * c3_b;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 7);
  for (c3_i20 = 0; c3_i20 < 2; c3_i20++) {
    c3_y[c3_i20] = c3_K[c3_i20];
  }

  c3_b_b = c3_y_k - c3_y_hat_k;
  for (c3_i21 = 0; c3_i21 < 2; c3_i21++) {
    c3_y[c3_i21] *= c3_b_b;
  }

  for (c3_i22 = 0; c3_i22 < 2; c3_i22++) {
    c3_x_k_k[c3_i22] = c3_x_hat_k[c3_i22] + c3_y[c3_i22];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 9);
  for (c3_i23 = 0; c3_i23 < 4; c3_i23++) {
    c3_I[c3_i23] = 0.0;
  }

  for (c3_i = 1; c3_i < 3; c3_i++) {
    c3_b_i = c3_i;
    c3_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_b_i), 1, 2, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c3_b_i), 1, 2, 2, 0) - 1) <<
           1)) - 1] = 1.0;
  }

  for (c3_i24 = 0; c3_i24 < 2; c3_i24++) {
    c3_y[c3_i24] = c3_K[c3_i24];
  }

  for (c3_i25 = 0; c3_i25 < 2; c3_i25++) {
    c3_i26 = 0;
    for (c3_i27 = 0; c3_i27 < 2; c3_i27++) {
      c3_a[c3_i26 + c3_i25] = c3_y[c3_i25] * (1.0 - (real_T)c3_i27);
      c3_i26 += 2;
    }
  }

  for (c3_i28 = 0; c3_i28 < 4; c3_i28++) {
    c3_I[c3_i28] -= c3_a[c3_i28];
  }

  for (c3_i29 = 0; c3_i29 < 4; c3_i29++) {
    c3_a[c3_i29] = c3_P_hat_k[c3_i29];
  }

  c3_d_eml_scalar_eg(chartInstance);
  c3_d_eml_scalar_eg(chartInstance);
  for (c3_i30 = 0; c3_i30 < 4; c3_i30++) {
    c3_P_k_k[c3_i30] = 0.0;
  }

  for (c3_i31 = 0; c3_i31 < 4; c3_i31++) {
    c3_P_k_k[c3_i31] = 0.0;
  }

  for (c3_i32 = 0; c3_i32 < 4; c3_i32++) {
    c3_b_C[c3_i32] = c3_P_k_k[c3_i32];
  }

  for (c3_i33 = 0; c3_i33 < 4; c3_i33++) {
    c3_P_k_k[c3_i33] = c3_b_C[c3_i33];
  }

  for (c3_i34 = 0; c3_i34 < 4; c3_i34++) {
    c3_b_C[c3_i34] = c3_P_k_k[c3_i34];
  }

  for (c3_i35 = 0; c3_i35 < 4; c3_i35++) {
    c3_P_k_k[c3_i35] = c3_b_C[c3_i35];
  }

  for (c3_i36 = 0; c3_i36 < 2; c3_i36++) {
    c3_i37 = 0;
    for (c3_i38 = 0; c3_i38 < 2; c3_i38++) {
      c3_P_k_k[c3_i37 + c3_i36] = 0.0;
      c3_i39 = 0;
      for (c3_i40 = 0; c3_i40 < 2; c3_i40++) {
        c3_P_k_k[c3_i37 + c3_i36] += c3_I[c3_i39 + c3_i36] * c3_a[c3_i40 +
          c3_i37];
        c3_i39 += 2;
      }

      c3_i37 += 2;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i41 = 0; c3_i41 < 2; c3_i41++) {
    (*c3_b_x_k_k)[c3_i41] = c3_x_k_k[c3_i41];
  }

  for (c3_i42 = 0; c3_i42 < 4; c3_i42++) {
    (*c3_b_P_k_k)[c3_i42] = c3_P_k_k[c3_i42];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc3_ekf_trial(SFc3_ekf_trialInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i43;
  int32_T c3_i44;
  int32_T c3_i45;
  real_T c3_b_inData[4];
  int32_T c3_i46;
  int32_T c3_i47;
  int32_T c3_i48;
  real_T c3_u[4];
  const mxArray *c3_y = NULL;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i43 = 0;
  for (c3_i44 = 0; c3_i44 < 2; c3_i44++) {
    for (c3_i45 = 0; c3_i45 < 2; c3_i45++) {
      c3_b_inData[c3_i45 + c3_i43] = (*(real_T (*)[4])c3_inData)[c3_i45 + c3_i43];
    }

    c3_i43 += 2;
  }

  c3_i46 = 0;
  for (c3_i47 = 0; c3_i47 < 2; c3_i47++) {
    for (c3_i48 = 0; c3_i48 < 2; c3_i48++) {
      c3_u[c3_i48 + c3_i46] = c3_b_inData[c3_i48 + c3_i46];
    }

    c3_i46 += 2;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 2, 2), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_P_k_k, const char_T *c3_identifier, real_T c3_y[4])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_P_k_k), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_P_k_k);
}

static void c3_b_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4])
{
  real_T c3_dv2[4];
  int32_T c3_i49;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv2, 1, 0, 0U, 1, 0U, 2, 2, 2);
  for (c3_i49 = 0; c3_i49 < 4; c3_i49++) {
    c3_y[c3_i49] = c3_dv2[c3_i49];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_P_k_k;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[4];
  int32_T c3_i50;
  int32_T c3_i51;
  int32_T c3_i52;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_P_k_k = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_P_k_k), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_P_k_k);
  c3_i50 = 0;
  for (c3_i51 = 0; c3_i51 < 2; c3_i51++) {
    for (c3_i52 = 0; c3_i52 < 2; c3_i52++) {
      (*(real_T (*)[4])c3_outData)[c3_i52 + c3_i50] = c3_y[c3_i52 + c3_i50];
    }

    c3_i50 += 2;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i53;
  real_T c3_b_inData[2];
  int32_T c3_i54;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i53 = 0; c3_i53 < 2; c3_i53++) {
    c3_b_inData[c3_i53] = (*(real_T (*)[2])c3_inData)[c3_i53];
  }

  for (c3_i54 = 0; c3_i54 < 2; c3_i54++) {
    c3_u[c3_i54] = c3_b_inData[c3_i54];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_c_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_x_k_k, const char_T *c3_identifier, real_T c3_y[2])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_x_k_k), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_x_k_k);
}

static void c3_d_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2])
{
  real_T c3_dv3[2];
  int32_T c3_i55;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv3, 1, 0, 0U, 1, 0U, 1, 2);
  for (c3_i55 = 0; c3_i55 < 2; c3_i55++) {
    c3_y[c3_i55] = c3_dv3[c3_i55];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_x_k_k;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2];
  int32_T c3_i56;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_x_k_k = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_x_k_k), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_x_k_k);
  for (c3_i56 = 0; c3_i56 < 2; c3_i56++) {
    (*(real_T (*)[2])c3_outData)[c3_i56] = c3_y[c3_i56];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_e_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i57;
  real_T c3_b_inData[2];
  int32_T c3_i58;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i57 = 0; c3_i57 < 2; c3_i57++) {
    c3_b_inData[c3_i57] = (*(real_T (*)[2])c3_inData)[c3_i57];
  }

  for (c3_i58 = 0; c3_i58 < 2; c3_i58++) {
    c3_u[c3_i58] = c3_b_inData[c3_i58];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 2), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

const mxArray *sf_c3_ekf_trial_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[55];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i59;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 55), FALSE);
  for (c3_i59 = 0; c3_i59 < 55; c3_i59++) {
    c3_r0 = &c3_info[c3_i59];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context", "nameCaptureInfo",
                    c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name", "nameCaptureInfo", c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved", "nameCaptureInfo",
                    c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c3_i59);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c3_i59);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[55])
{
  c3_info[0].context = "";
  c3_info[0].name = "mtimes";
  c3_info[0].dominantType = "double";
  c3_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[0].fileTimeLo = 1289552092U;
  c3_info[0].fileTimeHi = 0U;
  c3_info[0].mFileTimeLo = 0U;
  c3_info[0].mFileTimeHi = 0U;
  c3_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[1].name = "eml_index_class";
  c3_info[1].dominantType = "";
  c3_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[1].fileTimeLo = 1323202978U;
  c3_info[1].fileTimeHi = 0U;
  c3_info[1].mFileTimeLo = 0U;
  c3_info[1].mFileTimeHi = 0U;
  c3_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[2].name = "eml_scalar_eg";
  c3_info[2].dominantType = "double";
  c3_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[2].fileTimeLo = 1286851196U;
  c3_info[2].fileTimeHi = 0U;
  c3_info[2].mFileTimeLo = 0U;
  c3_info[2].mFileTimeHi = 0U;
  c3_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[3].name = "eml_xgemm";
  c3_info[3].dominantType = "char";
  c3_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c3_info[3].fileTimeLo = 1299109172U;
  c3_info[3].fileTimeHi = 0U;
  c3_info[3].mFileTimeLo = 0U;
  c3_info[3].mFileTimeHi = 0U;
  c3_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c3_info[4].name = "eml_blas_inline";
  c3_info[4].dominantType = "";
  c3_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[4].fileTimeLo = 1299109168U;
  c3_info[4].fileTimeHi = 0U;
  c3_info[4].mFileTimeLo = 0U;
  c3_info[4].mFileTimeHi = 0U;
  c3_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c3_info[5].name = "mtimes";
  c3_info[5].dominantType = "double";
  c3_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[5].fileTimeLo = 1289552092U;
  c3_info[5].fileTimeHi = 0U;
  c3_info[5].mFileTimeLo = 0U;
  c3_info[5].mFileTimeHi = 0U;
  c3_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c3_info[6].name = "eml_index_class";
  c3_info[6].dominantType = "";
  c3_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[6].fileTimeLo = 1323202978U;
  c3_info[6].fileTimeHi = 0U;
  c3_info[6].mFileTimeLo = 0U;
  c3_info[6].mFileTimeHi = 0U;
  c3_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c3_info[7].name = "eml_scalar_eg";
  c3_info[7].dominantType = "double";
  c3_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[7].fileTimeLo = 1286851196U;
  c3_info[7].fileTimeHi = 0U;
  c3_info[7].mFileTimeLo = 0U;
  c3_info[7].mFileTimeHi = 0U;
  c3_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c3_info[8].name = "eml_refblas_xgemm";
  c3_info[8].dominantType = "char";
  c3_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c3_info[8].fileTimeLo = 1299109174U;
  c3_info[8].fileTimeHi = 0U;
  c3_info[8].mFileTimeLo = 0U;
  c3_info[8].mFileTimeHi = 0U;
  c3_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[9].name = "eml_xdotu";
  c3_info[9].dominantType = "double";
  c3_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[9].fileTimeLo = 1299109172U;
  c3_info[9].fileTimeHi = 0U;
  c3_info[9].mFileTimeLo = 0U;
  c3_info[9].mFileTimeHi = 0U;
  c3_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[10].name = "eml_blas_inline";
  c3_info[10].dominantType = "";
  c3_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[10].fileTimeLo = 1299109168U;
  c3_info[10].fileTimeHi = 0U;
  c3_info[10].mFileTimeLo = 0U;
  c3_info[10].mFileTimeHi = 0U;
  c3_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c3_info[11].name = "eml_xdot";
  c3_info[11].dominantType = "double";
  c3_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c3_info[11].fileTimeLo = 1299109172U;
  c3_info[11].fileTimeHi = 0U;
  c3_info[11].mFileTimeLo = 0U;
  c3_info[11].mFileTimeHi = 0U;
  c3_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c3_info[12].name = "eml_blas_inline";
  c3_info[12].dominantType = "";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[12].fileTimeLo = 1299109168U;
  c3_info[12].fileTimeHi = 0U;
  c3_info[12].mFileTimeLo = 0U;
  c3_info[12].mFileTimeHi = 0U;
  c3_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c3_info[13].name = "eml_index_class";
  c3_info[13].dominantType = "";
  c3_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[13].fileTimeLo = 1323202978U;
  c3_info[13].fileTimeHi = 0U;
  c3_info[13].mFileTimeLo = 0U;
  c3_info[13].mFileTimeHi = 0U;
  c3_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c3_info[14].name = "eml_refblas_xdot";
  c3_info[14].dominantType = "double";
  c3_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c3_info[14].fileTimeLo = 1299109172U;
  c3_info[14].fileTimeHi = 0U;
  c3_info[14].mFileTimeLo = 0U;
  c3_info[14].mFileTimeHi = 0U;
  c3_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c3_info[15].name = "eml_refblas_xdotx";
  c3_info[15].dominantType = "char";
  c3_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[15].fileTimeLo = 1299109174U;
  c3_info[15].fileTimeHi = 0U;
  c3_info[15].mFileTimeLo = 0U;
  c3_info[15].mFileTimeHi = 0U;
  c3_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[16].name = "eml_scalar_eg";
  c3_info[16].dominantType = "double";
  c3_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[16].fileTimeLo = 1286851196U;
  c3_info[16].fileTimeHi = 0U;
  c3_info[16].mFileTimeLo = 0U;
  c3_info[16].mFileTimeHi = 0U;
  c3_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[17].name = "eml_index_class";
  c3_info[17].dominantType = "";
  c3_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[17].fileTimeLo = 1323202978U;
  c3_info[17].fileTimeHi = 0U;
  c3_info[17].mFileTimeLo = 0U;
  c3_info[17].mFileTimeHi = 0U;
  c3_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[18].name = "eml_index_minus";
  c3_info[18].dominantType = "double";
  c3_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[18].fileTimeLo = 1286851178U;
  c3_info[18].fileTimeHi = 0U;
  c3_info[18].mFileTimeLo = 0U;
  c3_info[18].mFileTimeHi = 0U;
  c3_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[19].name = "eml_index_class";
  c3_info[19].dominantType = "";
  c3_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[19].fileTimeLo = 1323202978U;
  c3_info[19].fileTimeHi = 0U;
  c3_info[19].mFileTimeLo = 0U;
  c3_info[19].mFileTimeHi = 0U;
  c3_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[20].name = "eml_index_times";
  c3_info[20].dominantType = "coder.internal.indexInt";
  c3_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c3_info[20].fileTimeLo = 1286851180U;
  c3_info[20].fileTimeHi = 0U;
  c3_info[20].mFileTimeLo = 0U;
  c3_info[20].mFileTimeHi = 0U;
  c3_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c3_info[21].name = "eml_index_class";
  c3_info[21].dominantType = "";
  c3_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[21].fileTimeLo = 1323202978U;
  c3_info[21].fileTimeHi = 0U;
  c3_info[21].mFileTimeLo = 0U;
  c3_info[21].mFileTimeHi = 0U;
  c3_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[22].name = "eml_index_plus";
  c3_info[22].dominantType = "coder.internal.indexInt";
  c3_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[22].fileTimeLo = 1286851178U;
  c3_info[22].fileTimeHi = 0U;
  c3_info[22].mFileTimeLo = 0U;
  c3_info[22].mFileTimeHi = 0U;
  c3_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[23].name = "eml_index_class";
  c3_info[23].dominantType = "";
  c3_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[23].fileTimeLo = 1323202978U;
  c3_info[23].fileTimeHi = 0U;
  c3_info[23].mFileTimeLo = 0U;
  c3_info[23].mFileTimeHi = 0U;
  c3_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c3_info[24].name = "eml_int_forloop_overflow_check";
  c3_info[24].dominantType = "";
  c3_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[24].fileTimeLo = 1346542740U;
  c3_info[24].fileTimeHi = 0U;
  c3_info[24].mFileTimeLo = 0U;
  c3_info[24].mFileTimeHi = 0U;
  c3_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c3_info[25].name = "intmax";
  c3_info[25].dominantType = "char";
  c3_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[25].fileTimeLo = 1311287716U;
  c3_info[25].fileTimeHi = 0U;
  c3_info[25].mFileTimeLo = 0U;
  c3_info[25].mFileTimeHi = 0U;
  c3_info[26].context = "";
  c3_info[26].name = "inv";
  c3_info[26].dominantType = "double";
  c3_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c3_info[26].fileTimeLo = 1305350400U;
  c3_info[26].fileTimeHi = 0U;
  c3_info[26].mFileTimeLo = 0U;
  c3_info[26].mFileTimeHi = 0U;
  c3_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c3_info[27].name = "eml_div";
  c3_info[27].dominantType = "double";
  c3_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c3_info[27].fileTimeLo = 1313380210U;
  c3_info[27].fileTimeHi = 0U;
  c3_info[27].mFileTimeLo = 0U;
  c3_info[27].mFileTimeHi = 0U;
  c3_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[28].name = "norm";
  c3_info[28].dominantType = "double";
  c3_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[28].fileTimeLo = 1336554494U;
  c3_info[28].fileTimeHi = 0U;
  c3_info[28].mFileTimeLo = 0U;
  c3_info[28].mFileTimeHi = 0U;
  c3_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c3_info[29].name = "abs";
  c3_info[29].dominantType = "double";
  c3_info[29].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[29].fileTimeLo = 1343862766U;
  c3_info[29].fileTimeHi = 0U;
  c3_info[29].mFileTimeLo = 0U;
  c3_info[29].mFileTimeHi = 0U;
  c3_info[30].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[30].name = "eml_scalar_abs";
  c3_info[30].dominantType = "double";
  c3_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[30].fileTimeLo = 1286851112U;
  c3_info[30].fileTimeHi = 0U;
  c3_info[30].mFileTimeLo = 0U;
  c3_info[30].mFileTimeHi = 0U;
  c3_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[31].name = "mtimes";
  c3_info[31].dominantType = "double";
  c3_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[31].fileTimeLo = 1289552092U;
  c3_info[31].fileTimeHi = 0U;
  c3_info[31].mFileTimeLo = 0U;
  c3_info[31].mFileTimeHi = 0U;
  c3_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[32].name = "eml_warning";
  c3_info[32].dominantType = "char";
  c3_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c3_info[32].fileTimeLo = 1286851202U;
  c3_info[32].fileTimeHi = 0U;
  c3_info[32].mFileTimeLo = 0U;
  c3_info[32].mFileTimeHi = 0U;
  c3_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[33].name = "isnan";
  c3_info[33].dominantType = "double";
  c3_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c3_info[33].fileTimeLo = 1286851160U;
  c3_info[33].fileTimeHi = 0U;
  c3_info[33].mFileTimeLo = 0U;
  c3_info[33].mFileTimeHi = 0U;
  c3_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[34].name = "eps";
  c3_info[34].dominantType = "char";
  c3_info[34].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[34].fileTimeLo = 1326760396U;
  c3_info[34].fileTimeHi = 0U;
  c3_info[34].mFileTimeLo = 0U;
  c3_info[34].mFileTimeHi = 0U;
  c3_info[35].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[35].name = "eml_is_float_class";
  c3_info[35].dominantType = "char";
  c3_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c3_info[35].fileTimeLo = 1286851182U;
  c3_info[35].fileTimeHi = 0U;
  c3_info[35].mFileTimeLo = 0U;
  c3_info[35].mFileTimeHi = 0U;
  c3_info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[36].name = "eml_eps";
  c3_info[36].dominantType = "char";
  c3_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c3_info[36].fileTimeLo = 1326760396U;
  c3_info[36].fileTimeHi = 0U;
  c3_info[36].mFileTimeLo = 0U;
  c3_info[36].mFileTimeHi = 0U;
  c3_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c3_info[37].name = "eml_float_model";
  c3_info[37].dominantType = "char";
  c3_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c3_info[37].fileTimeLo = 1326760396U;
  c3_info[37].fileTimeHi = 0U;
  c3_info[37].mFileTimeLo = 0U;
  c3_info[37].mFileTimeHi = 0U;
  c3_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c3_info[38].name = "eml_flt2str";
  c3_info[38].dominantType = "double";
  c3_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c3_info[38].fileTimeLo = 1309483596U;
  c3_info[38].fileTimeHi = 0U;
  c3_info[38].mFileTimeLo = 0U;
  c3_info[38].mFileTimeHi = 0U;
  c3_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c3_info[39].name = "char";
  c3_info[39].dominantType = "double";
  c3_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c3_info[39].fileTimeLo = 1319762368U;
  c3_info[39].fileTimeHi = 0U;
  c3_info[39].mFileTimeLo = 0U;
  c3_info[39].mFileTimeHi = 0U;
  c3_info[40].context = "";
  c3_info[40].name = "eye";
  c3_info[40].dominantType = "double";
  c3_info[40].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c3_info[40].fileTimeLo = 1286851088U;
  c3_info[40].fileTimeHi = 0U;
  c3_info[40].mFileTimeLo = 0U;
  c3_info[40].mFileTimeHi = 0U;
  c3_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[41].name = "eml_assert_valid_size_arg";
  c3_info[41].dominantType = "double";
  c3_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[41].fileTimeLo = 1286851094U;
  c3_info[41].fileTimeHi = 0U;
  c3_info[41].mFileTimeLo = 0U;
  c3_info[41].mFileTimeHi = 0U;
  c3_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c3_info[42].name = "isinf";
  c3_info[42].dominantType = "double";
  c3_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c3_info[42].fileTimeLo = 1286851160U;
  c3_info[42].fileTimeHi = 0U;
  c3_info[42].mFileTimeLo = 0U;
  c3_info[42].mFileTimeHi = 0U;
  c3_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c3_info[43].name = "mtimes";
  c3_info[43].dominantType = "double";
  c3_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[43].fileTimeLo = 1289552092U;
  c3_info[43].fileTimeHi = 0U;
  c3_info[43].mFileTimeLo = 0U;
  c3_info[43].mFileTimeHi = 0U;
  c3_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[44].name = "eml_index_class";
  c3_info[44].dominantType = "";
  c3_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[44].fileTimeLo = 1323202978U;
  c3_info[44].fileTimeHi = 0U;
  c3_info[44].mFileTimeLo = 0U;
  c3_info[44].mFileTimeHi = 0U;
  c3_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[45].name = "intmax";
  c3_info[45].dominantType = "char";
  c3_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[45].fileTimeLo = 1311287716U;
  c3_info[45].fileTimeHi = 0U;
  c3_info[45].mFileTimeLo = 0U;
  c3_info[45].mFileTimeHi = 0U;
  c3_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[46].name = "eml_is_float_class";
  c3_info[46].dominantType = "char";
  c3_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c3_info[46].fileTimeLo = 1286851182U;
  c3_info[46].fileTimeHi = 0U;
  c3_info[46].mFileTimeLo = 0U;
  c3_info[46].mFileTimeHi = 0U;
  c3_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[47].name = "min";
  c3_info[47].dominantType = "double";
  c3_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[47].fileTimeLo = 1311287718U;
  c3_info[47].fileTimeHi = 0U;
  c3_info[47].mFileTimeLo = 0U;
  c3_info[47].mFileTimeHi = 0U;
  c3_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[48].name = "eml_min_or_max";
  c3_info[48].dominantType = "char";
  c3_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c3_info[48].fileTimeLo = 1334103890U;
  c3_info[48].fileTimeHi = 0U;
  c3_info[48].mFileTimeLo = 0U;
  c3_info[48].mFileTimeHi = 0U;
  c3_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[49].name = "eml_scalar_eg";
  c3_info[49].dominantType = "double";
  c3_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[49].fileTimeLo = 1286851196U;
  c3_info[49].fileTimeHi = 0U;
  c3_info[49].mFileTimeLo = 0U;
  c3_info[49].mFileTimeHi = 0U;
  c3_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[50].name = "eml_scalexp_alloc";
  c3_info[50].dominantType = "double";
  c3_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[50].fileTimeLo = 1352457260U;
  c3_info[50].fileTimeHi = 0U;
  c3_info[50].mFileTimeLo = 0U;
  c3_info[50].mFileTimeHi = 0U;
  c3_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[51].name = "eml_index_class";
  c3_info[51].dominantType = "";
  c3_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[51].fileTimeLo = 1323202978U;
  c3_info[51].fileTimeHi = 0U;
  c3_info[51].mFileTimeLo = 0U;
  c3_info[51].mFileTimeHi = 0U;
  c3_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c3_info[52].name = "eml_scalar_eg";
  c3_info[52].dominantType = "double";
  c3_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[52].fileTimeLo = 1286851196U;
  c3_info[52].fileTimeHi = 0U;
  c3_info[52].mFileTimeLo = 0U;
  c3_info[52].mFileTimeHi = 0U;
  c3_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[53].name = "eml_index_class";
  c3_info[53].dominantType = "";
  c3_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[53].fileTimeLo = 1323202978U;
  c3_info[53].fileTimeHi = 0U;
  c3_info[53].mFileTimeLo = 0U;
  c3_info[53].mFileTimeHi = 0U;
  c3_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c3_info[54].name = "eml_int_forloop_overflow_check";
  c3_info[54].dominantType = "";
  c3_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[54].fileTimeLo = 1346542740U;
  c3_info[54].fileTimeHi = 0U;
  c3_info[54].mFileTimeLo = 0U;
  c3_info[54].mFileTimeHi = 0U;
}

static void c3_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance)
{
}

static void c3_b_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance)
{
}

static void c3_c_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance)
{
}

static real_T c3_inv(SFc3_ekf_trialInstanceStruct *chartInstance, real_T c3_x)
{
  real_T c3_y;
  real_T c3_b_y;
  real_T c3_b_x;
  real_T c3_xinv;
  real_T c3_c_x;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_n1x;
  real_T c3_f_x;
  real_T c3_g_x;
  real_T c3_h_x;
  real_T c3_n1xinv;
  real_T c3_a;
  real_T c3_b;
  real_T c3_c_y;
  real_T c3_rc;
  real_T c3_i_x;
  boolean_T c3_b_b;
  real_T c3_j_x;
  int32_T c3_i60;
  static char_T c3_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c3_u[8];
  const mxArray *c3_d_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_e_y = NULL;
  real_T c3_c_u;
  const mxArray *c3_f_y = NULL;
  real_T c3_d_u;
  const mxArray *c3_g_y = NULL;
  char_T c3_str[14];
  int32_T c3_i61;
  char_T c3_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  c3_b_y = c3_x;
  c3_y = 1.0 / c3_b_y;
  c3_b_x = c3_x;
  c3_xinv = c3_y;
  c3_c_x = c3_b_x;
  c3_d_x = c3_c_x;
  c3_e_x = c3_d_x;
  c3_n1x = muDoubleScalarAbs(c3_e_x);
  c3_f_x = c3_xinv;
  c3_g_x = c3_f_x;
  c3_h_x = c3_g_x;
  c3_n1xinv = muDoubleScalarAbs(c3_h_x);
  c3_a = c3_n1x;
  c3_b = c3_n1xinv;
  c3_c_y = c3_a * c3_b;
  c3_rc = 1.0 / c3_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c3_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c3_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c3_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c3_i_x = c3_rc;
    c3_b_b = muDoubleScalarIsNaN(c3_i_x);
    guard3 = FALSE;
    if (c3_b_b) {
      guard3 = TRUE;
    } else {
      if (c3_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c3_j_x = c3_rc;
      for (c3_i60 = 0; c3_i60 < 8; c3_i60++) {
        c3_u[c3_i60] = c3_cv0[c3_i60];
      }

      c3_d_y = NULL;
      sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c3_b_u = 14.0;
      c3_e_y = NULL;
      sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c3_c_u = 6.0;
      c3_f_y = NULL;
      sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c3_d_u = c3_j_x;
      c3_g_y = NULL;
      sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c3_f_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c3_d_y, 14, c3_e_y, 14,
        c3_f_y), 14, c3_g_y), "sprintf", c3_str);
      for (c3_i61 = 0; c3_i61 < 14; c3_i61++) {
        c3_b_str[c3_i61] = c3_str[c3_i61];
      }

      c3_b_eml_warning(chartInstance, c3_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c3_eml_warning(chartInstance);
  }

  return c3_y;
}

static void c3_eml_warning(SFc3_ekf_trialInstanceStruct *chartInstance)
{
  int32_T c3_i62;
  static char_T c3_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c3_u[27];
  const mxArray *c3_y = NULL;
  for (c3_i62 = 0; c3_i62 < 27; c3_i62++) {
    c3_u[c3_i62] = c3_varargin_1[c3_i62];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c3_y));
}

static void c3_b_eml_warning(SFc3_ekf_trialInstanceStruct *chartInstance, char_T
  c3_varargin_2[14])
{
  int32_T c3_i63;
  static char_T c3_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c3_u[33];
  const mxArray *c3_y = NULL;
  int32_T c3_i64;
  char_T c3_b_u[14];
  const mxArray *c3_b_y = NULL;
  for (c3_i63 = 0; c3_i63 < 33; c3_i63++) {
    c3_u[c3_i63] = c3_varargin_1[c3_i63];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 33), FALSE);
  for (c3_i64 = 0; c3_i64 < 14; c3_i64++) {
    c3_b_u[c3_i64] = c3_varargin_2[c3_i64];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c3_y, 14, c3_b_y));
}

static void c3_d_eml_scalar_eg(SFc3_ekf_trialInstanceStruct *chartInstance)
{
}

static void c3_f_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_sprintf, const char_T *c3_identifier, char_T c3_y[14])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_sprintf), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_sprintf);
}

static void c3_g_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, char_T c3_y[14])
{
  char_T c3_cv1[14];
  int32_T c3_i65;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c3_i65 = 0; c3_i65 < 14; c3_i65++) {
    c3_y[c3_i65] = c3_cv1[c3_i65];
  }

  sf_mex_destroy(&c3_u);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static int32_T c3_h_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i66;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i66, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i66;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_i_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_ekf_trial, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_ekf_trial), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_ekf_trial);
  return c3_y;
}

static uint8_T c3_j_emlrt_marshallIn(SFc3_ekf_trialInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_ekf_trialInstanceStruct *chartInstance)
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

void sf_c3_ekf_trial_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3117134100U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(660718224U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(187827177U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1181538760U);
}

mxArray *sf_c3_ekf_trial_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("VlZmwEUbpGTiUudw8Q6EQD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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

mxArray *sf_c3_ekf_trial_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c3_ekf_trial(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[10],T\"P_k_k\",},{M[1],M[5],T\"x_k_k\",},{M[8],M[0],T\"is_active_c3_ekf_trial\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_ekf_trial_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_ekf_trialInstanceStruct *chartInstance;
    chartInstance = (SFc3_ekf_trialInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ekf_trialMachineNumber_,
           3,
           1,
           1,
           7,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"x_hat_k");
          _SFD_SET_DATA_PROPS(1,1,1,0,"P_hat_k");
          _SFD_SET_DATA_PROPS(2,1,1,0,"y_hat_k");
          _SFD_SET_DATA_PROPS(3,1,1,0,"y_k");
          _SFD_SET_DATA_PROPS(4,2,0,1,"x_k_k");
          _SFD_SET_DATA_PROPS(5,2,0,1,"P_k_k");
          _SFD_SET_DATA_PROPS(6,1,1,0,"R");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,319);
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
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c3_y_hat_k;
          real_T *c3_y_k;
          real_T *c3_R;
          real_T (*c3_x_hat_k)[2];
          real_T (*c3_P_hat_k)[4];
          real_T (*c3_x_k_k)[2];
          real_T (*c3_P_k_k)[4];
          c3_R = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c3_P_k_k = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 2);
          c3_x_k_k = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_y_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c3_y_hat_k = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c3_P_hat_k = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
          c3_x_hat_k = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_x_hat_k);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_P_hat_k);
          _SFD_SET_DATA_VALUE_PTR(2U, c3_y_hat_k);
          _SFD_SET_DATA_VALUE_PTR(3U, c3_y_k);
          _SFD_SET_DATA_VALUE_PTR(4U, *c3_x_k_k);
          _SFD_SET_DATA_VALUE_PTR(5U, *c3_P_k_k);
          _SFD_SET_DATA_VALUE_PTR(6U, c3_R);
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
  return "bVlc08pa7bSVekJ3CcqQxB";
}

static void sf_opaque_initialize_c3_ekf_trial(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_ekf_trialInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*)
    chartInstanceVar);
  initialize_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_ekf_trial(void *chartInstanceVar)
{
  enable_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_ekf_trial(void *chartInstanceVar)
{
  disable_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_ekf_trial(void *chartInstanceVar)
{
  sf_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_ekf_trial(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_ekf_trial();/* state var info */
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

extern void sf_internal_set_sim_state_c3_ekf_trial(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_ekf_trial();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_ekf_trial(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_ekf_trial(S);
}

static void sf_opaque_set_sim_state_c3_ekf_trial(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_ekf_trial(S, st);
}

static void sf_opaque_terminate_c3_ekf_trial(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_ekf_trialInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ekf_trial_optimization_info();
    }

    finalize_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_ekf_trial((SFc3_ekf_trialInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_ekf_trial(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_ekf_trial((SFc3_ekf_trialInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_ekf_trial(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ekf_trial_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,3,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(817805501U));
  ssSetChecksum1(S,(3298142942U));
  ssSetChecksum2(S,(1615334143U));
  ssSetChecksum3(S,(2203755025U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_ekf_trial(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_ekf_trial(SimStruct *S)
{
  SFc3_ekf_trialInstanceStruct *chartInstance;
  chartInstance = (SFc3_ekf_trialInstanceStruct *)utMalloc(sizeof
    (SFc3_ekf_trialInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_ekf_trialInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_ekf_trial;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_ekf_trial;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_ekf_trial;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_ekf_trial;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_ekf_trial;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_ekf_trial;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_ekf_trial;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_ekf_trial;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_ekf_trial;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_ekf_trial;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_ekf_trial;
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

void c3_ekf_trial_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_ekf_trial(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_ekf_trial(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_ekf_trial(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_ekf_trial_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
