/* Copyright 2019,2020 NXP
 * 
 * This software is owned or controlled by NXP and may only be used
 * strictly in accordance with the applicable license terms.  By expressly
 * accepting such terms or by downloading, installing, activating and/or
 * otherwise using the software, you are agreeing that you have read, and
 * that you agree to comply with and are bound by, such license terms.  If
 * you do not agree to be bound by the applicable license terms, then you
 * may not retain, install, activate or otherwise use the software.
 * 
 */

#ifndef SSS_APIS_VERSION_INFO_H_INCLUDED
#define SSS_APIS_VERSION_INFO_H_INCLUDED


/* clang-format off */
#define SSS_APIS_PROD_NAME          "SSS_APIs"
#define SSS_APIS_VER_STRING_NUM     "v03.02.00_20200522"
#define SSS_APIS_PROD_NAME_VER_FULL "SSS_APIs_v03.02.00_20200522"
#define SSS_APIS_VER_MAJOR          (3u)
#define SSS_APIS_VER_MINOR          (2u)
#define SSS_APIS_VER_DEV            (0u)

/* v03.02 = 30002u */
#define SSS_APIS_VER_MAJOR_MINOR ( 0 \
    | (SSS_APIS_VER_MAJOR * 10000u)    \
    | (SSS_APIS_VER_MINOR))

/* v03.02.00 = 300020000ULL */
#define SSS_APIS_VER_MAJOR_MINOR_DEV ( 0 \
    | (SSS_APIS_VER_MAJOR * 10000*10000u)    \
    | (SSS_APIS_VER_MINOR * 10000u)    \
    | (SSS_APIS_VER_DEV))

/* clang-format on */


/* Version Information:
 * Generated by:
 *     scripts\version_info.py (v2019.01.17_00)
 * 
 * Do not edit this file. Update:
 *     sss/version_info.txt instead.
 * 
 * prod_name = "SSS_APIs"
 * 
 * prod_desc = "SSS APIs"
 * 
 * lang_c_prefix = prod_name.upper()
 * 
 * lang_namespace = ""
 * 
 * v_major  = "03"
 * 
 * v_minor  = "02"
 * 
 * v_dev    = "00"
 * 
 * v_meta   = ""
 * 
 * maturity = "B"
 * 
 * #
 * # 03.00.00 : Changed Enums
 * #
 */

#endif /* SSS_APIS_VERSION_INFO_H_INCLUDED */
