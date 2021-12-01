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




interp: obj/main.o obj/Interf4Plugin.o obj/Interp4Program.o obj/xmlinterp.o obj/Configuration.o obj/Scene.o obj/MobileObj.o obj/MacierzRot3D.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/Interf4Plugin.o obj/Interp4Program.o obj/Configuration.o obj/Scene.o obj/xmlinterp.o obj/MobileObj.o obj/MacierzRot3D.o -ldl -lxerces-c -lpthread

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/Interp4Program.hh inc/Interf4Plugin.hh inc/xmlinterp.hh inc/Scene.hh inc/Sender.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Interf4Plugin.o: src/Interf4Plugin.cpp inc/Interf4Plugin.hh
	g++ -c ${CPPFLAGS} -o obj/Interf4Plugin.o src/Interf4Plugin.cpp

obj/Interp4Program.o: src/Interp4Program.cpp inc/Interp4Program.hh
	g++ -c ${CPPFLAGS} -o obj/Interp4Program.o src/Interp4Program.cpp
	
obj/Scene.o: src/Scene.cpp inc/Scene.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp
	
obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh inc/MobileObj.hh inc/xmlinterp.hh
		g++ -c ${CPPFLAGS} -o obj/Configuration.o src/Configuration.cpp	
	
obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh inc/Configuration.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp
	
obj/MobileObj.o: src/MobileObj.cpp inc/MobileObj.hh 
	g++ -c ${CPPFLAGS} -o obj/MobileObj.o src/MobileObj.cpp
	
obj/MacierzRot3D.o: src/MacierzRot3D.cpp inc/MacierzRot3D.hh inc/SMacierz.hh inc/geomVector.hh
	g++ -c ${CPPFLAGS} -o obj/MacierzRot3D.o src/MacierzRot3D.cpp	
		


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
 
