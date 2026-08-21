if [ -z "$1" ]; then
	echo "Blad: Podaj plik .elf"
	exit 1
fi

arm-none-eabi-gdb -ex "target extended-remote localhost:3333" \
		  -ex "monitor reset halt" \
		  -ex "load" "$1"
