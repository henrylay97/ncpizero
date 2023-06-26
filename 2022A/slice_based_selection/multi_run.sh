#!/bin/bash

#cafe -q 'ncpizero_selection.C(true, "basic",                          ncpizero_cuts,                           false)'
cafe -q 'ncpizero_selection.C(true, "pfp_cuts",                       ncpizero_pfp_cuts,                       false)'
cafe -q 'ncpizero_selection.C(true, "razzle_id_cuts",                 ncpizero_razzle_id_cuts,                 false)'
cafe -q 'ncpizero_selection.C(true, "razzle_lead_sublead_value_cuts", ncpizero_razzle_lead_sublead_value_cuts, false)'
cafe -q 'ncpizero_selection.C(true, "razzle_value_cuts",              ncpizero_razzle_value_cuts,              false)'
cafe -q 'ncpizero_selection.C(true, "dEdx_shower_dEdx_value_cuts",    ncpizero_shower_dEdx_value_cuts,         false)'
cafe -q 'ncpizero_selection.C(true, "muon_rej_cuts",                  ncpizero_muon_rej_cuts,                  false)'
