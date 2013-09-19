% This file allow user to write a new kernel into the kernelfun.hpp using
% matlab function handle

% Kernel 
syms rSquare;
kernel = exp(-sqrt(rSquare)/2); % user input here
ckernel = ccode(kernel);
kernelLineNumber = 7;

% Pass the Kernel to kernelfun.hpp
fid = fopen('kernelfun.hpp','r+');
for i = 1:(kernelLineNumber-1)
fgets(fid);
end
fseek(fid,0,'cof');% overwrite the existing line
fprintf(fid,'      %s\n',ckernel);
fclose(fid);