all:
	cc main_curl.c mapa.c read_json.c url.c connect.c -lcurl ../cJSON/cjson.o

read: 
	cc tests/test-read-json.c read_json.c ../cJSON/cjson.o -o test-read

test-read: read
	./test-read