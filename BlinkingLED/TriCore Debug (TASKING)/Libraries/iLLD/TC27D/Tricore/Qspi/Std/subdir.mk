################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.c" 

COMPILED_SRCS += \
"Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.src" 

C_DEPS += \
"./Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.d" 

OBJS += \
"Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.o" 


# Each subdirectory must supply rules for building sources it contributes
"Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.src":"../Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.c" "Libraries/iLLD/TC27D/Tricore/Qspi/Std/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/AVEES/AURIX-v1.10.6-workspace/BlinkingLED/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.o":"Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.src" "Libraries/iLLD/TC27D/Tricore/Qspi/Std/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Qspi-2f-Std

clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Qspi-2f-Std:
	-$(RM) ./Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.d ./Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.o ./Libraries/iLLD/TC27D/Tricore/Qspi/Std/IfxQspi.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC27D-2f-Tricore-2f-Qspi-2f-Std
