#!/bin/bash

outdir=/store/group/dpg_hgcal/comm_hgcal/nkasarag/
tag=V08-08-00-v3
#while [ $a -lt 350 ]
for i in {53..54..2}
do
    #ene = $i
    for v in 73; do

	python submitDigi.py -t ${tag} -v ${v} -m 2 --etas 2.0  -d pi-  -n 100 -e ${outdir} -g --enList ${i}  --nRuns 100 -b 0	
	#python3 submitProd.py -t ${tag} -v ${v} -m 2 --etas 2.0  -d pi-  -n 100 -e ${outdir} -g --enList ${i}  --nRuns 100
	# python submitProd.py -t ${tag} -v ${v} -m 2 --etas 1.7 2.0 2.4 -d pi- -b 3.8 -n 500  -e ${outdir} -g --enList 35 50 75 100    --nRuns 20
	# python submitProd.py -t ${tag} -v ${v} -m 2 --etas 1.7 2.0 2.4 -d pi- -b 3.8 -n 100  -e ${outdir} -g --enList 150 200 300 500 --nRuns 50

	#python submitDigi.py -t V08-08-00-v2 -v ${v} -m 2 --etas 1.7 2.0 2.4 -d pi- -b 3.8 -n 0 -e /store/cmst3/group/hgcal/Geant4/ -g --enList 2 5 7 10 15 25 --nRuns 5
	#python submitDigi.py -t V08-08-00-v2 -v ${v} -m 2 --etas 1.7 2.0 2.4 -d pi- -b 3.8 -n 0 -e /store/cmst3/group/hgcal/Geant4/ -g --enList 35 50 75 100    --nRuns 20
	#python submitDigi.py -t V08-08-00-v2 -v ${v} -m 2 --etas 1.7 2.0 2.4 -d pi- -b 3.8 -n 0 -e /store/cmst3/group/hgcal/Geant4/ -g --enList 150 200 300 500 --nRuns 50

    done
done
