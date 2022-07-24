#should be executed with bash: bash s.sh

g++ -o gen gen.cpp
make

for((i = 1; i <= 99; ++i)); do	
	
	mkdir folder$i

	./gen $i

	mv folder$i Entradas

	 ./exec 100

	rm -r Entradas
done
