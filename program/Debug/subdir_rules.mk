################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
flash.obj: ../flash.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/msp430/include" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/bsp" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/bsp/drivers" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/mrfi" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/mrfi/radios/common" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/mrfi/radios/family1" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="flash.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

simple_receive_app.obj: ../simple_receive_app.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/ti/ccsv6/msp430/include" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/bsp" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/bsp/drivers" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/mrfi" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/mrfi/radios/common" --include_path="C:/Users/Christopher/Documents/CS 3420/drivers/mrfi/radios/family1" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="simple_receive_app.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


