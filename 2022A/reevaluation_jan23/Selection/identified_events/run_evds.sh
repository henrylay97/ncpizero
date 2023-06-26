#!/bin/bash

source /cvmfs/sbnd.opensciencegrid.org/products/sbnd/setup_sbnd.sh
source /sbnd/app/users/hlay/ncpizero/localProducts_larsoft_v09_64_01_e20_prof/setup
mrbslp

export DISPLAY=localhost:1

cat $1 | while read LINE
do
    if [[ $LINE == *"creating shared library"* ]];
	then
	continue
    fi

    echo $PWD

    RUN_NUM=`echo $LINE | cut -d ' ' -f 1`
    SUBRUN_NUM=`echo $LINE | cut -d ' ' -f 2`
    EV_NUM=`echo $LINE | cut -d ' ' -f 3`

    FILE=`samweb -e sbnd list-files "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_sbnd and run_number $RUN_NUM.$SUBRUN_NUM"`
    LOC=`samweb -e sbnd locate-file $FILE | cut -f 2 -d :`
    FILE_LOC=$LOC/$FILE

    lar -c evd.fcl -s $FILE_LOC -n 1 -e $RUN_NUM:$SUBRUN_NUM:$EV_NUM
done
