reset
set terminal postscript eps enhanced colour "Times-Roman,26";


do for[k=13:130]{
fileName_in = sprintf("%s_k%iVSsteps.dat", polymerName, k);
fileName_out = sprintf("%s_k%iVSsteps.eps", polymerName, k);

#fileName_in = sprintf("results/%s_totalAngleVSsteps.dat", polymerName);
#fileName_out = sprintf("results/%s_totalAngleVSsteps.eps", polymerName);

set output fileName_out;
#set title "N^{0}"
set xlabel "Scaling step";

set ylabel "New Observable";
#set key box inside vertical left Left reverse width -1 top spacing 1.2 ;
unset key
#set logscale y

plot [:][:] fileName_in w errorb lc rgb "steelblue" pt 31
}