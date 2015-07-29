/* Include files */

#include "ekf_trial_sfun.h"
#include "ekf_trial_sfun_debug_macros.h"
#include "c1_ekf_trial.h"
#include "c2_ekf_trial.h"
#include "c3_ekf_trial.h"
#include "c4_ekf_trial.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _ekf_trialMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void ekf_trial_initializer(void)
{
}

void ekf_trial_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_ekf_trial_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_ekf_trial_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_ekf_trial_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_ekf_trial_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_ekf_trial_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_ekf_trial_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2736909966U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1585269059U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3085367242U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1893596330U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3527757249U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1817934660U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2541461284U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3201172475U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_ekf_trial_get_check_sum(mxArray *plhs[]);
          sf_c1_ekf_trial_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_ekf_trial_get_check_sum(mxArray *plhs[]);
          sf_c2_ekf_trial_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_ekf_trial_get_check_sum(mxArray *plhs[]);
          sf_c3_ekf_trial_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_ekf_trial_get_check_sum(mxArray *plhs[]);
          sf_c4_ekf_trial_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1764838350U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3410240878U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(118138738U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(243351119U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(111151533U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(348867239U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1109008676U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2239795005U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ekf_trial_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "33zv9kxwXnuaUBXRXTWm8E") == 0) {
          extern mxArray *sf_c1_ekf_trial_get_autoinheritance_info(void);
          plhs[0] = sf_c1_ekf_trial_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "eA3wrUA1W8m5XcHRHzRBTF") == 0) {
          extern mxArray *sf_c2_ekf_trial_get_autoinheritance_info(void);
          plhs[0] = sf_c2_ekf_trial_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "VlZmwEUbpGTiUudw8Q6EQD") == 0) {
          extern mxArray *sf_c3_ekf_trial_get_autoinheritance_info(void);
          plhs[0] = sf_c3_ekf_trial_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "yWaw9gOL9g475vGApRHyVE") == 0) {
          extern mxArray *sf_c4_ekf_trial_get_autoinheritance_info(void);
          plhs[0] = sf_c4_ekf_trial_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ekf_trial_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_ekf_trial_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_ekf_trial_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_ekf_trial_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_ekf_trial_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_ekf_trial_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_ekf_trial_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_ekf_trial_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_ekf_trial_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_ekf_trial_third_party_uses_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "Ru6nVlFG8LETtbll896weE") == 0) {
          extern mxArray *sf_c1_ekf_trial_third_party_uses_info(void);
          plhs[0] = sf_c1_ekf_trial_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "hDFJ0GP3LdnmbIoS52ceBD") == 0) {
          extern mxArray *sf_c2_ekf_trial_third_party_uses_info(void);
          plhs[0] = sf_c2_ekf_trial_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "bVlc08pa7bSVekJ3CcqQxB") == 0) {
          extern mxArray *sf_c3_ekf_trial_third_party_uses_info(void);
          plhs[0] = sf_c3_ekf_trial_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "cuygSHqpBB4NUdsR3ria4C") == 0) {
          extern mxArray *sf_c4_ekf_trial_third_party_uses_info(void);
          plhs[0] = sf_c4_ekf_trial_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void ekf_trial_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _ekf_trialMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "ekf_trial","sfun",0,4,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_ekf_trialMachineNumber_,0,
    0);
  sf_debug_set_machine_data_thresholds(debugInstance,_ekf_trialMachineNumber_,0);
}

void ekf_trial_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_ekf_trial_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("ekf_trial",
      "ekf_trial");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_ekf_trial_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
