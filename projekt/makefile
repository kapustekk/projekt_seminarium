all:
	cc main_curl.c mapa.c read_json.c logic.c connect.c -lcurl ../cJSON/cjson.o

read: 
	cc tests/test-read-json.c read_json.c ../cJSON/cjson.o -o test-read

test-read: read
	./test-read

do_mapy_test: do_mapy_test
	gcc wpisanie_test.c wpisanie_do_mapy.c -o do_mapy_test
	valgrind ./do_mapy_test
	./do_mapy_test 