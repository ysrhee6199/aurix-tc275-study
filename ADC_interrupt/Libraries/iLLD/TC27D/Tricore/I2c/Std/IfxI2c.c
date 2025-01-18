/**
 * \file IfxI2c.c
 * \brief I2C  basic functionality
 *
 * \version iLLD_1_0_1_17_0
 * \copyright Copyright (c) 2023 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxI2c.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxI2c_configureAsMaster(Ifx_I2C *i2c)
{
    // enter config Mode
    IfxI2c_stop(i2c);

    i2c->ADDRCFG.U      = 0;
    i2c->ADDRCFG.B.MnS  = 1; // master mode
    i2c->ADDRCFG.B.SONA = 0; // don't release the bus on NACK
    i2c->ADDRCFG.B.SOPE = 0; // after transfer go into master restart state
    i2c->ADDRCFG.B.TBAM = 0; // 7 bit address mode
    i2c->FIFOCFG.U      = 0;
    i2c->FIFOCFG.B.TXFC = 1; // FIFO as flow controller
    i2c->FIFOCFG.B.RXFC = 1; // FIFO as flow controller
    i2c->FIFOCFG.B.TXBS = 0; // Burst size 1 word
    i2c->FIFOCFG.B.RXBS = 0; // Burst size 1 word
    i2c->FIFOCFG.B.TXFA = 0; // fifo is byte aligned
    i2c->FIFOCFG.B.RXFA = 0; // fifo is byte aligned
}


void IfxI2c_disableModule(Ifx_I2C *i2c)
{
    uint16 pwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(pwd);

    i2c->CLC.B.DISR = 1;

    while (i2c->CLC.B.DISS == 0)
    {}

    IfxScuWdt_setCpuEndinit(pwd);
}


void IfxI2c_enableBurstDataTransferInterrupt(Ifx_I2C *i2c, IfxSrc_Tos typeOfService, uint16 priority)
{
    volatile Ifx_SRC_SRCR *src;
    src = IfxI2c_getBurstDataTransferSrcPointer(i2c);
    IfxSrc_init(src, typeOfService, priority);
    IfxSrc_enable(src);
}


void IfxI2c_enableErrorInterrupt(Ifx_I2C *i2c, IfxSrc_Tos typeOfService, uint16 priority)
{
    volatile Ifx_SRC_SRCR *src;
    src = IfxI2c_getErrorSrcPointer(i2c);
    IfxSrc_init(src, typeOfService, priority);
    IfxSrc_enable(src);
}


void IfxI2c_enableLastBurstDataTransferInterrupt(Ifx_I2C *i2c, IfxSrc_Tos typeOfService, uint16 priority)
{
    volatile Ifx_SRC_SRCR *src;
    src = IfxI2c_getLastBurstDataTransferSrcPointer(i2c);
    IfxSrc_init(src, typeOfService, priority);
    IfxSrc_enable(src);
}


void IfxI2c_enableLastSingleDataTransferInterrupt(Ifx_I2C *i2c, IfxSrc_Tos typeOfService, uint16 priority)
{
    volatile Ifx_SRC_SRCR *src;
    src = IfxI2c_getLastSingleDataTransferSrcPointer(i2c);
    IfxSrc_init(src, typeOfService, priority);
    IfxSrc_enable(src);
}


void IfxI2c_enableModule(Ifx_I2C *i2c)
{
    uint16 pwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(pwd);
    i2c->CLC.B.DISR = 0U;

    while (i2c->CLC.B.DISS == 1U)
    {}

    i2c->CLC1.B.RMC = 1U;

    while (i2c->CLC1.B.RMC != 1U)
    {}

    i2c->CLC1.B.DISR = 0U;

    while (i2c->CLC1.B.DISS == 1U)
    {}

    // disable all interrupts
    i2c->ERRIRQSM.U = 0x00;
    i2c->PIRQSM.U   = 0x00;
    i2c->IMSC.U     = 0x00;

    IfxScuWdt_setCpuEndinit(pwd);
}


void IfxI2c_enableProtocolInterrupt(void *i2c, IfxSrc_Tos typeOfService, uint16 priority)
{
    volatile Ifx_SRC_SRCR *src;
    src = IfxI2c_getProtocolSrcPointer(i2c);
    IfxSrc_init(src, typeOfService, priority);
    IfxSrc_enable(src);
}


void IfxI2c_enableSingleDataTransferInterrupt(Ifx_I2C *i2c, IfxSrc_Tos typeOfService, uint16 priority)
{
    volatile Ifx_SRC_SRCR *src;
    src = IfxI2c_getSingleDataTransferSrcPointer(i2c);
    IfxSrc_init(src, typeOfService, priority);
    IfxSrc_enable(src);
}


Ifx_I2C *IfxI2c_getAddress(IfxI2c_Index i2c)
{
    Ifx_I2C *module;

    if (i2c < IFXI2C_NUM_MODULES)
    {
        module = (Ifx_I2C *)IfxI2c_cfg_indexMap[i2c].module;
    }
    else
    {
        module = NULL_PTR;
    }

    return module;
}


float32 IfxI2c_getBaudrate(Ifx_I2C *i2c)
{
    uint8   inc     = i2c->FDIVCFG.B.INC;
    uint16  dec     = i2c->FDIVCFG.B.DEC;
    uint8   rmc     = i2c->CLC1.B.RMC;
    float32 fKernel = IfxScuCcu_getBaud1Frequency();

    return (fKernel / rmc) / ((2 * dec / inc) + 3);
}


IfxI2c_Index IfxI2c_getIndex(Ifx_I2C *i2c)
{
    uint32       index;
    IfxI2c_Index result;

    result = IfxI2c_Index_none;

    for (index = 0; index < IFXI2C_NUM_MODULES; index++)
    {
        if (IfxI2c_cfg_indexMap[index].module == i2c)
        {
            result = (IfxI2c_Index)IfxI2c_cfg_indexMap[index].index;
            break;
        }
    }

    return result;
}


void IfxI2c_initSclSdaPin(const IfxI2c_Scl_InOut *scl, const IfxI2c_Sda_InOut *sda, IfxPort_PadDriver padDriver)
{
    IfxPort_OutputMode mode = (IfxPort_OutputMode)IfxPort_Mode_outputOpenDrainGeneral;
    IfxPort_setPinModeOutput(scl->pin.port, scl->pin.pinIndex, mode, scl->outSelect);
    IfxPort_setPinModeOutput(sda->pin.port, sda->pin.pinIndex, mode, sda->outSelect);
    IfxPort_setPinPadDriver(scl->pin.port, scl->pin.pinIndex, padDriver);
    IfxPort_setPinPadDriver(sda->pin.port, sda->pin.pinIndex, padDriver);
    IfxI2c_setPinSelection(scl->module, (IfxI2c_PinSelect)scl->inSelect); // note: uses the same PISEL register like SDA
}


void IfxI2c_releaseBus(Ifx_I2C *i2c)
{
    // only set the set end of transmisson bit if bus is not free
    if (i2c->BUSSTAT.B.BS != IfxI2c_BusStatus_idle)
    {
        i2c->ENDDCTRL.B.SETEND = 1;

        // wait until bus is free
        while (IfxI2c_getProtocolInterruptSourceStatus(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd) == FALSE)
        {}

        IfxI2c_clearProtocolInterruptSource(i2c, IfxI2c_ProtocolInterruptSource_transmissionEnd);
    }
}


void IfxI2c_resetFifo(Ifx_I2C *i2c)
{
    /* reset FIFO */
    i2c->FIFOCFG.U = 0x0;
}


void IfxI2c_resetModule(Ifx_I2C *i2c)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(passwd);
    i2c->KRST0.B.RST = 1;           /* Only if both Kernel reset bits are set a reset is executed */
    i2c->KRST1.B.RST = 1;
    IfxScuWdt_setCpuEndinit(passwd);

    while (0 == i2c->KRST0.B.RSTSTAT)   /* Wait until reset is executed */

    {}

    IfxScuWdt_clearCpuEndinit(passwd);
    i2c->KRSTCLR.B.CLR = 1;         /* Clear Kernel reset status bit */
    IfxScuWdt_setCpuEndinit(passwd);
}


void IfxI2c_setBaudrate(Ifx_I2C *i2c, float32 baudrate)
{
    float32 fKernel = IfxScuCcu_getBaud1Frequency();
    uint8   rmc     = i2c->CLC1.B.RMC;
    float32 dec;
    dec = (((fKernel / rmc) / baudrate) - 3) / 2;     // always: Inc = 1

    // dec:inc must be at least 6
    if (dec < 6)
    {
        dec = 6;
    }
    else if (dec > (1 << IFX_I2C_FDIVCFG_DEC_LEN) - 1)
    {
        dec = (1 << IFX_I2C_FDIVCFG_DEC_LEN) - 1;
    }

    uint16 pwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(pwd);
    /* Baudrate configuration */
    i2c->FDIVCFG.B.INC           = 1;
    i2c->FDIVCFG.B.DEC           = (uint16)(dec + 0.5f);
    i2c->TIMCFG.B.SDA_DEL_HD_DAT = 0x3F;
    i2c->TIMCFG.B.FS_SCL_LOW     = 1;
    i2c->TIMCFG.B.EN_SCL_LOW_LEN = 1;
    i2c->TIMCFG.B.SCL_LOW_LEN    = 0x20;

    IfxScuWdt_setCpuEndinit(pwd);
}


void IfxI2c_configureAsSlave(Ifx_I2C *i2c)
{
    i2c->ADDRCFG.B.MnS = 1; // master mode
}


void IfxI2c_configureAddrFifo(Ifx_I2C *i2c, const IfxI2c_Config *config)
{
    // Note: I2C should not be running. Use IfxI2c_stop() before calling this api.

    i2c->ADDRCFG.B.ADR  = config->addressConfig.slaveAddress;
    i2c->ADDRCFG.B.GCE  = config->addressConfig.generalCallEnable;
    i2c->ADDRCFG.B.MCE  = config->addressConfig.masterCodeEnable;
    i2c->ADDRCFG.B.SONA = config->addressConfig.stopOnNotAcknowledge;
    i2c->ADDRCFG.B.SOPE = config->addressConfig.stopOnPacketEnd;
    i2c->ADDRCFG.B.TBAM = config->addressConfig.addressMode;

    i2c->FIFOCFG.B.TXFC = config->fifoConfig.txFifoFlowControl;
    i2c->FIFOCFG.B.RXFC = config->fifoConfig.rxFifoFlowControl;
    i2c->FIFOCFG.B.TXBS = config->fifoConfig.txBurstSize;
    i2c->FIFOCFG.B.RXBS = config->fifoConfig.rxBurstSize;
    i2c->FIFOCFG.B.TXFA = config->fifoConfig.txFifoAlignment;
    i2c->FIFOCFG.B.RXFA = config->fifoConfig.rxFifoAlignment;
}
