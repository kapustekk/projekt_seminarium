all:
	cc main_curl.c mapa.c read_json.c url.c connect.c wpisanie_do_mapy.c logic.c -lcurl ../cJSON/cjson.o
read:
	cc tests/test-read-json.c read_json.c ../cJSON/cjson.o -o test-read
url:
	cc url.c tests/test-url.c -o test-url
connect:
	cc connect.c tests/test-connect.c -lcurl -o test-connect

test-read: read
	valgrind ./test-read
	./test-read
test-url: url
	valgrind ./test-url
	./test-url
test-connect: connect
	valgrind ./test-url
	./test-connect

test-wpisanie_do_mapy: test-wpisanie_do_mapy
	gcc tests/wpisanie_test.c connect.c read_json.c wpisanie_do_mapy.c -o test-wpisanie_do_mapy -lcurl ../cJSON/cjson.o
	valgrind ./test-wpisanie_do_mapy
	./test-wpisanie_do_mapy 

test-logic: test-logic
	gcc tests/logic_test.c url.c logic.c mapa.c connect.c read_json.c wpisanie_do_mapy.c -o test-logic -lcurl ../cJSON/cjson.o
	valgrind ./test-logic
	./test-logic

test-mapa: test-mapa
	gcc tests/test_mapa.c mapa.c wpisanie_do_mapy.c -o test-mapa
	valgrind ./test-mapa
	./test-mapa

clean:
	rm -f do_mapy_test
	rm -f *.o

