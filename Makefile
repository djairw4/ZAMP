__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp ./opis_dzialan.cmd

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -iquote inc
LDFLAGS=-Wall




interp: obj/main.o obj/Interf4Plugin.o obj/Interp4Program.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/Interf4Plugin.o obj/Interp4Program.o -ldl

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/Interp4Program.hh inc/Interf4Plugin.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Interf4Plugin.o: src/Interf4Plugin.cpp inc/Interf4Plugin.hh
	g++ -c ${CPPFLAGS} -o obj/Interf4Plugin.o src/Interf4Plugin.cpp

obj/Interp4Program.o: src/Interp4Program.cpp inc/Interp4Program.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Program.o src/Interp4Program.cpp


clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
