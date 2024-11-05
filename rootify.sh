suffix=sample1--00000
folder=raw/

./trc2root/trc2root \
 -o ${suffix}.root -cmstiming \
 -c1 ${folder}/C2--${suffix}.trc \
 -c2 ${folder}/C2--${suffix}.trc \
 -c3 ${folder}/C3--${suffix}.trc \
 -c5 ${folder}/C5--${suffix}.trc

