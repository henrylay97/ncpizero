#!/bin/bash

source /sbnd/app/users/mdeltutt/static_evd/setup.sh

export DISPLAY=localhost:1

RUN_NUM=`echo $1 | cut -d ':' -f 1`
SUBRUN_NUM=`echo $1 | cut -d ':' -f 2`

FILE=`samweb -e sbnd list-files "defname: official_MCP2022A_prodoverlay_corsika_cosmics_proton_genie_rockbox_sce_reco2_sbnd and run_number $RUN_NUM.$SUBRUN_NUM"`
LOC=`samweb -e sbnd locate-file $FILE | cut -f 2 -d :`
FILE_LOC=$LOC/$FILE

evd.py -s $FILE_LOC

