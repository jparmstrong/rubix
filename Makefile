$(mkdir -p build)

.phony: build

all:
	gcc -ggdb -O3 print.c rubix.c main.c -o build/rubix

wasm:
	clang -target wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all print.c rubix.c main.c -o build/rubix.wasm
