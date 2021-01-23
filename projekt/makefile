all:
	cc main_curl.c mapa.c read_json.c url.c connect.c -lcurl ../cJSON/cjson.o
read:
	cc tests/test-read-json.c read_json.c ../cJSON/cjson.o -o test-read
url:
	cc connect.c url.c tests/test-url.c -lcurl -o test-url
connect:
	cc connect.c url.c tests/test-connect.c -lcurl -o test-connect

test-read: read
	./test-read
test-url: url
	./test-url
test-connect: connect
	./test-connect

do_mapy_test: do_mapy_test
	gcc wpisanie_test.c wpisanie_do_mapy.c -o do_mapy_test
	valgrind ./do_mapy_test
	./do_mapy_test 
