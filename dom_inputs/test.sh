g++ -g -Wall Ou2.cpp
echo ----- icayley
time ./a.out <icayley.txt>output.txt
diff output.txt ocayley.txt

echo ----- ifootball.txt
time ./a.out <ifootball.txt > output.txt
diff output.txt ofootball.txt

echo ----- ifullerene.txt
time ./a.out <ifullerene.txt > output.txt
diff output.txt ofullerene.txt

echo ----- ikneser.txt
time ./a.out <ikneser.txt > output.txt
diff output.txt okneser.txt

echo ----- iqueen.txt
time ./a.out <iqueen.txt  > output.txt
diff output.txt oqueen.txt

echo ----- success!