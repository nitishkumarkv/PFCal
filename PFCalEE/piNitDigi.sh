#!/bin/bash

#outdir=/store/group/dpg_hgcal/comm_hgcal/nkasarag/ ###/eos/cms/store/group/dpg_hgcal/comm_hgcal/nkasarag
outdir=/eos/user/n/nkasarag/Simulation_Full_HGCAL/rootFiles2
tag=V08-08-00-v3
#while [ $a -lt 350 ]
#for i in {135..138..1};
#do
    #ene = $i
for v in 73; do

    #python submitDigi.py -t ${tag} -v ${v} -m 2 --etas 2.0  -d mu-  -n 10 -e ${outdir} -g --enList 200 --nRuns 20  -b 0

    #python submitDigi.py -t ${tag} -v ${v} -m 2 --etas 2.0 -d pi- -b 3.8 -n 100  -e ${outdir} -g --enList 26.5802228834 --nRuns 1000 
#    python submitDigi.py -t ${tag} -v ${v} -m 2 --etas 2.0 -d pi- -b 0.0 -n 1  -e ${outdir} -g --enList 26.580223 13.290111 79.740669 --nRuns 1 
    #python submitDigi_ori.py -t ${tag} -v ${v} -m 2 --etas 2.0 -d pi- -b 0.0 -n 100  -e ${outdir} -g --enList 26.580223 13.290111 79.740669 --nRuns 100
    #python submitDigi.py -t ${tag} -v ${v} -m 2 --etas 2.0 -d pi- -b 0.0 -n 100  -e ${outdir} -g --enList 5.31604 13.290111 21.264178 26.580223 31.896267 53.160446 66.450557 79.740669  --nRuns 350
    python submitDigi.py -t ${tag} -v ${v} -m 2 --etas 2.0 -d pi- -b 0.0 -n 100  -e ${outdir} -g --enList 5.31604 26.580223 79.740669 --nRuns 100
done
