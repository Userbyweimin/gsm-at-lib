/**
 * \file            gsm_device.c
 * \brief           Device driver internal functions
 */

/*
 * Copyright (c) 2018 Tilen Majerle
 *  
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of GSM-AT.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 */
#include "gsm/gsm_private.h"
#include "gsm/gsm_device.h"

/**
 * \brief           Set physical driver for GSM device
 * \param[in]       driver: Pointer to device driver
 * \return          \ref gsmOK on success, member of \ref gsmr_t otherwise
 */
gsmr_t
gsm_device_set_driver(gsm_device_driver_t* driver) {
    //GSM_CORE_PROTECT();                         /* Protect core */
    gsm.driver = driver;                        /* Set device driver */
    //GSM_CORE_UNPROTECT();                       /* Unprotect core */
    return gsmOK;
}

gsm_device_driver_t *
gsm_device_get_driver(void) {
    return gsm.driver;
}

#if GSM_CFG_SMS || __DOXYGEN__

/**
 * \brief           Set SMS ready (or not) from device driver
 * \note            This function may be called from device driver only
 * \param[in]       ready: Ready flag. Set to `1` if SMS ready, `0` otherwise
 * \return          `1` on success, `0` otherwise
 */
uint8_t
gsm_device_set_sms_ready(uint8_t ready) {
    gsm.sms.ready = !!ready;                    /* SMS ready flag */
    gsmi_send_cb(GSM_CB_SMS_READY);             /* Send SMS ready event */
    return 1;
}

#endif /* GSM_CFG_SMS || __DOXYGEN__ */

#if GSM_CFG_CALL || __DOXYGEN__

/**
 * \brief           Set call ready (or not) from device driver
 * \note            This function may be called from device driver only
 * \param[in]       ready: Ready flag. Set to `1` if call ready, `0` otherwise
 * \return          `1` on success, `0` otherwise
 */
uint8_t
gsm_device_set_call_ready(uint8_t ready) {
    gsm.call.ready = !!ready;                   /* Call ready flag */
    gsmi_send_cb(GSM_CB_CALL_READY);            /* Send call ready event */
    return 1;
}

#endif /* GSM_CFG_CALL || __DOXYGEN__ */

#if GSM_CFG_NETWORK || __DOXYGEN__

/**
 * \brief           Set IP address to stack received by GSM device
 * \note            This function may be called from device driver only
 * \param[in]       ip: IP address. Set to `NULL` to clear address
 * \return          `1` on success, `0` otherwise
 */
uint8_t
gsm_device_set_ip(gsm_ip_t* ip) {
    if (ip != NULL) {
        //memcpy(&gsm.ip, ip, sizeof(*ip));
    } else {
        //memset(&gsm.ip, 0x00, sizeof(*ip));
    }
    return 1;
}

/**
 * \brief           Set network is ready to use flag
 * \note            This function may be called from device driver only
 * \param[in]       ready: Flag indicates if network is ready and connection(s) can be established
 * \return          `1` on success, `0` otherwise
 */
uint8_t
gsm_device_set_network_ready(uint8_t ready) {
    return 1;
}

#endif /* GSM_CFG_NETWORK || __DOXYGEN__ */
