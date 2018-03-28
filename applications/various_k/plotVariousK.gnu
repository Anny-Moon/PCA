reset
set terminal postscript eps enhanced colour "Times-Roman,26";

do for [k=1:450]{
fileName_in = sprintf("results/%s_k%iVSsteps.dat", polymerName, k);
fileName_out = sprintf("results/%s_k%iVSsteps.eps", polymerName, k);

set output fileName_out;

set xlabel "Scaling step";
set ylabel "Observable";

#set key box inside vertical left Left reverse width -1 top spacing 1.2 ;
unset key

plot [:][:] fileName_in w errorb lc rgb "steelblue" pt 31
}