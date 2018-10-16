num_grid = 256;

Pa = @(mm)2*(num_grid-mm-12)/(mm-2)/(3+10*(num_grid-mm-12)/(mm-2));
Pb = @(mm)1/(3+10*(num_grid-mm-12)/(mm-2));
Pc = @(mm)(3+20*(num_grid-mm-12)/(mm-2))/(15+50*(num_grid-mm-12)/(mm-2));
%red color
fplot(Pa,[10,240],'r');
hold on
%blue color
fplot(Pb,[10,240],'b');
%green color
hold on
fplot(Pc,[10,240],'g');
