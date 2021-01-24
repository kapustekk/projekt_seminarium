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

do_mapy_test: do_mapy_test
	gcc wpisanie_test.c mapa.c connect.c read_json.c wpisanie_do_mapy.c -o do_mapy_test
	valgrind ./do_mapy_test
	./do_mapy_test 
clean:
	rm -f do_mapy_test
	rm -f *.o

