k=58e-3;
Lm=15e-3;    Rm=0.7;
J=21.04e-3;    B=859e-6;

s = tf('s');
Zl = ( k^2+(s*J+B)*(s*Lm+Rm) )/(s*J+B);   % = V(s)/I(s)