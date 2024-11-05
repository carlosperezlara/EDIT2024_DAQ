suffix=$1
raw_folder=LecroyMount
out_folder=output

echo " >>> Sending Acquisition Job to Lecroy's WaveRunner 8208HD <<< "
time python3 daq.py

echo " >>> Converting BINARY to ROOT <<< "
time trc2root -o ${suffix}.root -cmstiming \
 -c2 ${raw_folder}/C2--${suffix}.trc 
 -c3 ${raw_folder}/C3--${suffix}.trc 
 -c5 ${raw_folder}/C5--${suffix}.trc 

#echo " >>> PreProcessing Signals <<< "
#time signalProcessing --input_file=${suffix}.root --save_meas --config=signalProcessing.config

mv ${suffix}.root ${out_folder}/

echo ""
echo " ${out_folder}/${suffix}.root has been created. Goodbye!"
