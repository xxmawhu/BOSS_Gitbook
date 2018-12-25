#!/bin/bash -
# * ===============================================================================
# *   DESCRIPTION: Batch create jobOption files based on a template
# *        AUTHOR: Remco de Boer <remco.de.boer@ihep.ac.cn>
# *  ORGANIZATION: IHEP, CAS (Beijing, CHINA)
# *       CREATED: 22 October 2018
# *         USAGE: bash CreateJobFiles.sh <package name> <number of jobs> <number of events>
# *     ARGUMENTS: 1) package name (default is "RhopiAlg")
# *                2) number of job files to be created (default is 25)
# *                3) number of events per job (default is 10,000)
# * ===============================================================================

set -e # exit if a command or function exits with a non-zero status

# * ===================================================== * #
# * ------- Attempt to load script with functions ------- * #
# * ===================================================== * #
	commonFunctionsScriptName="CommonFunctions.sh"
	if [ -s "${commonFunctionsScriptName}" ]; then
		source "${commonFunctionsScriptName}"
	else
		echo -e "\e[91mFATAL ERROR: Source script \"${commonFunctionsScriptName}\" does not exist\e[0m"
		exit
	fi


# ! ================================ ! #
# ! ------- Script arguments ------- ! #
# ! ================================ ! #
	# * (1) package name (optional -- default is "RhopiAlg")
	packageName="RhopiAlg" # default argument
	if [ $# -ge 1 ]; then
		packageName="${1}"
	fi
	# * (2) number of jobOption files and submit scripts that need to be generated
	nJobs=25 # default argument
	if [ $# -ge 2 ]; then
		nJobs=${2}
	fi
	# * (3) number of events per job (optional -- default is 10,000)
	nEventsPerJob=10000 # default argument
	if [ $# -ge 3 ]; then
		nEventsPerJob=${3}
	fi


# * ================================= * #
# * ------- Script parameters ------- * #
# * ================================= * #
	afterburnerPath="${PWD/${PWD/*BOSS_Afterburner}}" # get path of BOSS Afterburner
	scriptFolder="${afterburnerPath}/jobs" # contains templates and will write scripts to its subfolders
	outputFolder="/scratchfs/bes/${USER}/data" # rtraw, dst, root, and log files will be written to this folder


# * =============================================== * #
# * ------- Check arguments and parameters -------  * #
# * =============================================== * #
	CheckIfFolderExists "${scriptFolder}"
	CheckIfFolderExists "${outputFolder}"


# * ============================= * #
# * ------- Main function ------- * #
# * ============================= * #

	# * User input
	echo "This will create ${nJobs} \"ana_${packageName}_mc.txt\" job files with ${nEventsPerJob} events each in folder:"
	echo "   \"${scriptFolder}\"."

	AskForInput "\nTo continue, press ENTER, else Ctrl+C ..."

	# * Create and EMPTY scripts directory
	CreateOrEmptyDirectory "${scriptFolder}" "ana"  "${packageName}_mc"
	CreateOrEmptyDirectory "${scriptFolder}" "sub"  "${packageName}_mc"
	CreateOrEmptyDirectory "${scriptFolder}" "sim"  "${packageName}_mc"
	CreateOrEmptyDirectory "${scriptFolder}" "rec"  "${packageName}_mc"
	# * Create and EMPTY output directory
	CreateOrEmptyDirectory "${outputFolder}" "raw"  "${packageName}_mc"
	CreateOrEmptyDirectory "${outputFolder}" "dst"  "${packageName}_mc"
	CreateOrEmptyDirectory "${outputFolder}" "root" "${packageName}_mc"
	CreateOrEmptyDirectory "${outputFolder}" "log"  "${packageName}_mc"

	# * Loop over jobs
	for jobNo in $(seq 0 $((${nJobs} - 1))); do

		echo -en "\e[0K\rCreating files for job $(($jobNo+1))/${nJobs}..." # overwrite previous line

		# * Generate the analyse files (ana)
		templateName="${scriptFolder}/templates/jobOptions_ana_${packageName}_mc.txt"
		outputFile="${scriptFolder}/ana/ana_${packageName}_mc_${jobNo}.txt"
		CheckIfFileExists "${templateName}"
		awk '{flag = 1}
			{sub(/DSTFILE/,"dst/rec_'${packageName}'_mc_'${jobNo}'.dst")}
			{sub(/ROOTFILE/,"root/ana_'${packageName}'_mc_'${jobNo}'.root")}
			{sub(/OUTPUT_PATH/,"'${outputFolder}'")}
			{sub(/NEVENTS/,'${nEventsPerJob}')}
			{if(flag == 1) {print $0} else {next} }' \
		"${templateName}" > "${outputFile}"
		ChangeLineEndingsFromWindowsToUnix "${outputFile}"
		chmod +x "${outputFile}"

		# * Generate the simulation files (sim)
		templateName="${scriptFolder}/templates/jobOptions_sim.txt"
		outputFile="${scriptFolder}/sim/sim_${packageName}_mc_${jobNo}.txt"
		CheckIfFileExists "${templateName}"
		awk '{flag = 1}
			{sub(/RDF/,"raw/sim_'${packageName}'_mc_'${jobNo}'.rtraw")}
			{sub(/SCRIPT_PATH/,"'${scriptFolder}'")}
			{sub(/OUTPUT_PATH/,"'${outputFolder}'")}
			{sub(/RAND/,'$(($(date +%s%N) % 1000000000))')}
			{sub(/DEC/,"dec/'${packageName}'.dec")}
			{sub(/NEVENTS/,'${nEventsPerJob}')}
			{if(flag == 1) {print $0} else {next} }' \
		${templateName} > "${outputFile}"
		ChangeLineEndingsFromWindowsToUnix "${outputFile}"
		chmod +x "${outputFile}"

		# * Generate the reconstruction files (rec)
		templateName="${scriptFolder}/templates/jobOptions_rec.txt"
		outputFile="${scriptFolder}/rec/rec_${packageName}_mc_${jobNo}.txt"
		CheckIfFileExists "${templateName}"
		awk '{flag = 1}
			{sub(/RDF/,"raw/sim_'${packageName}'_mc_'${jobNo}'.rtraw")}
			{sub(/DSTFILE/,"dst/rec_'${packageName}'_mc_'${jobNo}'.dst")}
			{sub(/OUTPUT_PATH/,"'${outputFolder}'")}
			{sub(/RAND/,'$(($(date +%s%N) % 1000000000))')}
			{sub(/NEVENTS/,'${nEventsPerJob}')}
			{if(flag == 1) {print $0} else {next} }' \
		"${templateName}" > "${outputFile}"
		ChangeLineEndingsFromWindowsToUnix "${outputFile}"
		chmod +x "${outputFile}"

		# * Generate the submit files (sub)
		templateName="${scriptFolder}/templates/submit_mc.sh"
		outputFile="${scriptFolder}/sub/sub_${packageName}_mc_${jobNo}.sh"
		CheckIfFileExists "${templateName}"
		awk '{flag = 1}
			{sub(/SCRIPT_PATH/,"'${scriptFolder}'")}
			{sub(/OUTPUT_PATH/,"'${outputFolder}'")}
			{sub(/SIM_BOS/,"sim/sim_'${packageName}'_mc_'${jobNo}'.txt")}
			{sub(/SIM_LOG/,"log/sim_'${packageName}'_mc_'${jobNo}'.log")}
			{sub(/REC_BOS/,"rec/rec_'${packageName}'_mc_'${jobNo}'.txt")}
			{sub(/REC_LOG/,"log/rec_'${packageName}'_mc_'${jobNo}'.log")}
			{sub(/ANA_BOS/,"ana/ana_'${packageName}'_mc_'${jobNo}'.txt")}
			{sub(/ANA_LOG/,"log/ana_'${packageName}'_mc_'${jobNo}'.log")}
			{if(flag == 1) {print $0} else {next} }' \
		"${templateName}" > "${outputFile}"
		ChangeLineEndingsFromWindowsToUnix "${outputFile}"
		chmod +x "${outputFile}"

	done
	echo


# * ===================================== * #
# * ------- Final terminal output ------- * #
# * ===================================== * #
	PrintSuccessMessage \
		"Succesfully created ${nJobs} \"${packageName}\" job files with ${nEventsPerJob} events each\n"

set +e # exit if a command or function exits with a non-zero status