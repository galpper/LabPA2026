executable = Main
compiler = g++
compiler-options = -g -Wall -Wextra -Werror

ifdef OS
	executable := $(executable).exe
endif

build:
	$(compiler) $(compiler-options) -o $(executable) ICollection/*.cpp ICollection/collections/*.cpp ICollection/interfaces/*.cpp Clases/cpp/*.cpp DataType/cpp/*.cpp ISistema.cpp Factory.cpp Sistema.cpp main.cpp
	
	
.PHONY: clean
clean:
	rm -f $(executable)
