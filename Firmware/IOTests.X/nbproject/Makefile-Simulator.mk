#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Simulator.mk)" "nbproject/Makefile-local-Simulator.mk"
include nbproject/Makefile-local-Simulator.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Simulator
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Common/MessageFIFOBuffer.c ../Common/Counters.c ../Common/BuggyMessage.c ../Driver/LEDs.c ../Driver/Speaker.c ../Driver/Uart.c ../Driver/Timer.c ../Driver/ESP8266.c ../Driver/AnalogSensors.c ../Driver/DigitalSensors.c main.c Stm.Initialize.c Stm.Operational.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1 ${OBJECTDIR}/_ext/2108356922/Counters.p1 ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1 ${OBJECTDIR}/_ext/2139645815/LEDs.p1 ${OBJECTDIR}/_ext/2139645815/Speaker.p1 ${OBJECTDIR}/_ext/2139645815/Uart.p1 ${OBJECTDIR}/_ext/2139645815/Timer.p1 ${OBJECTDIR}/_ext/2139645815/ESP8266.p1 ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1 ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/Stm.Initialize.p1 ${OBJECTDIR}/Stm.Operational.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d ${OBJECTDIR}/_ext/2108356922/Counters.p1.d ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d ${OBJECTDIR}/_ext/2139645815/Uart.p1.d ${OBJECTDIR}/_ext/2139645815/Timer.p1.d ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/Stm.Initialize.p1.d ${OBJECTDIR}/Stm.Operational.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1 ${OBJECTDIR}/_ext/2108356922/Counters.p1 ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1 ${OBJECTDIR}/_ext/2139645815/LEDs.p1 ${OBJECTDIR}/_ext/2139645815/Speaker.p1 ${OBJECTDIR}/_ext/2139645815/Uart.p1 ${OBJECTDIR}/_ext/2139645815/Timer.p1 ${OBJECTDIR}/_ext/2139645815/ESP8266.p1 ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1 ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/Stm.Initialize.p1 ${OBJECTDIR}/Stm.Operational.p1

# Source Files
SOURCEFILES=../Common/MessageFIFOBuffer.c ../Common/Counters.c ../Common/BuggyMessage.c ../Driver/LEDs.c ../Driver/Speaker.c ../Driver/Uart.c ../Driver/Timer.c ../Driver/ESP8266.c ../Driver/AnalogSensors.c ../Driver/DigitalSensors.c main.c Stm.Initialize.c Stm.Operational.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Simulator.mk dist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4455
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1: ../Common/MessageFIFOBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2108356922" 
	@${RM} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1  ../Common/MessageFIFOBuffer.c 
	@-${MV} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.d ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2108356922/Counters.p1: ../Common/Counters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2108356922" 
	@${RM} ${OBJECTDIR}/_ext/2108356922/Counters.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2108356922/Counters.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2108356922/Counters.p1  ../Common/Counters.c 
	@-${MV} ${OBJECTDIR}/_ext/2108356922/Counters.d ${OBJECTDIR}/_ext/2108356922/Counters.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2108356922/Counters.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1: ../Common/BuggyMessage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2108356922" 
	@${RM} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1  ../Common/BuggyMessage.c 
	@-${MV} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.d ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/LEDs.p1: ../Driver/LEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/LEDs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/LEDs.p1  ../Driver/LEDs.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/LEDs.d ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/Speaker.p1: ../Driver/Speaker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Speaker.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/Speaker.p1  ../Driver/Speaker.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/Speaker.d ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/Uart.p1: ../Driver/Uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Uart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Uart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/Uart.p1  ../Driver/Uart.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/Uart.d ${OBJECTDIR}/_ext/2139645815/Uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/Uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/Timer.p1: ../Driver/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/Timer.p1  ../Driver/Timer.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/Timer.d ${OBJECTDIR}/_ext/2139645815/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/ESP8266.p1: ../Driver/ESP8266.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/ESP8266.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/ESP8266.p1  ../Driver/ESP8266.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/ESP8266.d ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1: ../Driver/AnalogSensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1  ../Driver/AnalogSensors.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.d ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1: ../Driver/DigitalSensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1  ../Driver/DigitalSensors.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.d ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Stm.Initialize.p1: Stm.Initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stm.Initialize.p1.d 
	@${RM} ${OBJECTDIR}/Stm.Initialize.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Stm.Initialize.p1  Stm.Initialize.c 
	@-${MV} ${OBJECTDIR}/Stm.Initialize.d ${OBJECTDIR}/Stm.Initialize.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Stm.Initialize.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Stm.Operational.p1: Stm.Operational.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stm.Operational.p1.d 
	@${RM} ${OBJECTDIR}/Stm.Operational.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Stm.Operational.p1  Stm.Operational.c 
	@-${MV} ${OBJECTDIR}/Stm.Operational.d ${OBJECTDIR}/Stm.Operational.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Stm.Operational.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1: ../Common/MessageFIFOBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2108356922" 
	@${RM} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1  ../Common/MessageFIFOBuffer.c 
	@-${MV} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.d ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2108356922/MessageFIFOBuffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2108356922/Counters.p1: ../Common/Counters.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2108356922" 
	@${RM} ${OBJECTDIR}/_ext/2108356922/Counters.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2108356922/Counters.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2108356922/Counters.p1  ../Common/Counters.c 
	@-${MV} ${OBJECTDIR}/_ext/2108356922/Counters.d ${OBJECTDIR}/_ext/2108356922/Counters.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2108356922/Counters.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1: ../Common/BuggyMessage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2108356922" 
	@${RM} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1  ../Common/BuggyMessage.c 
	@-${MV} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.d ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2108356922/BuggyMessage.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/LEDs.p1: ../Driver/LEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/LEDs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/LEDs.p1  ../Driver/LEDs.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/LEDs.d ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/LEDs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/Speaker.p1: ../Driver/Speaker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Speaker.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/Speaker.p1  ../Driver/Speaker.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/Speaker.d ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/Speaker.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/Uart.p1: ../Driver/Uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Uart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Uart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/Uart.p1  ../Driver/Uart.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/Uart.d ${OBJECTDIR}/_ext/2139645815/Uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/Uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/Timer.p1: ../Driver/Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/Timer.p1  ../Driver/Timer.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/Timer.d ${OBJECTDIR}/_ext/2139645815/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/ESP8266.p1: ../Driver/ESP8266.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/ESP8266.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/ESP8266.p1  ../Driver/ESP8266.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/ESP8266.d ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/ESP8266.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1: ../Driver/AnalogSensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1  ../Driver/AnalogSensors.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.d ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/AnalogSensors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1: ../Driver/DigitalSensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2139645815" 
	@${RM} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1  ../Driver/DigitalSensors.c 
	@-${MV} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.d ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2139645815/DigitalSensors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Stm.Initialize.p1: Stm.Initialize.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stm.Initialize.p1.d 
	@${RM} ${OBJECTDIR}/Stm.Initialize.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Stm.Initialize.p1  Stm.Initialize.c 
	@-${MV} ${OBJECTDIR}/Stm.Initialize.d ${OBJECTDIR}/Stm.Initialize.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Stm.Initialize.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Stm.Operational.p1: Stm.Operational.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stm.Operational.p1.d 
	@${RM} ${OBJECTDIR}/Stm.Operational.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Stm.Operational.p1  Stm.Operational.c 
	@-${MV} ${OBJECTDIR}/Stm.Operational.d ${OBJECTDIR}/Stm.Operational.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Stm.Operational.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"       --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -DSIMULATED -P -N255 -I"../Driver" -I"../Common" --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/IOTests.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Simulator
	${RM} -r dist/Simulator

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
