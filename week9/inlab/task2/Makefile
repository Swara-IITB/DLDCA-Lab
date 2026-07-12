all: naive optim

naive: naive.cpp main.cpp ../common/matrix.hpp
	g++ -O0 -o naive naive.cpp main.cpp

optim: optim.cpp main.cpp ../common/matrix.hpp
	g++ -O0 -mfma -mavx -o optim optim.cpp main.cpp

clean:
	rm -f naive optim