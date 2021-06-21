/*******************************************************************************
*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
*
****************************************************************************//*!
*
* @brief  Subtraction
* 
*******************************************************************************/
#ifndef _MLIB_SUB_F64_H_
#define _MLIB_SUB_F64_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Includes
*******************************************************************************/
#include "mlib_types.h"

/*******************************************************************************
* Macros
*******************************************************************************/  
#define MLIB_Sub_F64_Ci(f64Min, f64Sub)    MLIB_Sub_F64_FCi(f64Min, f64Sub) 
#define MLIB_SubSat_F64_Ci(f64Min, f64Sub) MLIB_SubSat_F64_FCi(f64Min, f64Sub)  
  
/***************************************************************************//*!
*
* f64Out = f64Min - f64Sub
* Without saturation
*******************************************************************************/ 
RAM_FUNC_LIB 
static inline frac64_t MLIB_Sub_F64_FCi(register frac64_t f64Min, register frac64_t f64Sub)
{
    return(f64Min - f64Sub);
}
 
/***************************************************************************//*!
*
* f64Out = f64Min - f64Sub
* With saturation
*******************************************************************************/
RAM_FUNC_LIB 
static inline frac64_t MLIB_SubSat_F64_FCi(register frac64_t f64Min, register frac64_t f64Sub)
{
    register int64_t i64Temp;
    register int64_t i64satmin, i64satmax;

    i64Temp = MLIB_Sub_F64_FCi(f64Min, f64Sub);
    i64satmax = (~f64Min & f64Sub) & i64Temp;
    i64satmin = f64Min & (~f64Sub) & (~i64Temp);

    i64Temp = (i64satmin < 0) ? INT64_MIN : i64Temp;
    i64Temp = (i64satmax < 0) ? INT64_MAX : i64Temp;
    return(i64Temp);
}
 
#if defined(__cplusplus)
}
#endif

#endif /* _MLIB_SUB_F64_H_ */ 