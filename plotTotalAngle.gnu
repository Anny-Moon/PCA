reset
set terminal postscript eps enhanced colour "Times-Roman,26";

fileName_in = sprintf("results/%s_TotalAngleVSsteps.dat", polymerName);
fileName_out = sprintf("results/%s_TotalAngleVSsteps.eps", polymerName);

set output fileName_out;
set xlabel "Scaling step";
set ylabel "Total angle";
unset key

plot [][] fileName_in w errorb lc rgb "steelblue" pt 31
