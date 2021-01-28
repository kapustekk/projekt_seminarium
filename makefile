all:
	cc main.c mapa.c read_json.c url.c connect.c odkrywanie_wnetrz.c wpisanie_do_mapy.c logic.c -lcurl ../cJSON/cjson.o -o czolg
read:
	cc tests/test-read-json.c read_json.c ../cJSON/cjson.o -o test-read
url:
	cc url.c tests/test-url.c -o test-url
connect:
	cc connect.c tests/test-connect.c -lcurl -o test-connect
map:
	gcc tests/wpisanie_test.c mapa.c connect.c read_json.c wpisanie_do_mapy.c -o test-map -lcurl ../cJSON/cjson.o

test-read: read
	valgrind ./test-read
	./test-read
test-url: url
	valgrind ./test-url
	./test-url
test-connect: connect
	valgrind ./test-url
	./test-connect

test-map: map
	valgrind ./test-map
	./test-map 
test-wczytanie: 
	gcc tests/test-mapa.c mapa.c wpisanie_do_mapy.c -o test-mapa
	valgrind ./test-mapa
	./test-mapa
test-memory:all
	valgrind ./czolg reset odkryj

clean:
	rm -f do_mapy_test
	rm -f *.o
	rm -f test-read
	rm -f test-url
	rm -f test-connect
	rm -f test-map
	rm -f test-mapa

