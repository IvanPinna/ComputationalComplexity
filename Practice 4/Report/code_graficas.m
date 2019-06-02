clear, close all;
y1  = [22.2917 26.9959 32.8119 33.0345 113.379]
y2 = [18.9752 21.2051 23.837 23.9195 58.9733]
x = 1:5
%labels = ["eil51", "eil76", "kroA100", "eil101", "a280"] 

plot(x, y1, '*r');
hold on; 
plot(x, y2, '*b');

xlabel('Maps')
ylabel('Time(seconds)')
legend('SCX', '50%');
title('Execution time');
hold off;

%Puntuación
clear, close all;
x = 1:5
s1 = [1193.69 1881.76 122508 2538.07 25208.8]
s2= [1379.27 2069.86 144786 3005.41 31242.9]
s = [426 538 21282 629]% -1] %No disponemos de la solucion óptima para el último mapa.
%labels = ["eil51", "eil76", "kroA100", "eil101", "a280"] 

plot(x, s1, '*r');
hold on; 
plot(x, s2, '*b');
plot(1:4, s, '*g');

xlabel('Maps')
ylabel('Best solution')
legend('SCX', '50%', 'optimal');
title('Best solution SCX and 50%');