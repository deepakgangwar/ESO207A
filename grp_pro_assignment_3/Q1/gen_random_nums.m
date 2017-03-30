a = randi (1e6, 1, 1e6);
fid = fopen('rn.txt','w');
fprintf (fid,'%d\n', a);