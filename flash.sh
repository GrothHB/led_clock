if [ -z "$1" ]; then
	echo "Blad: Podaj plik .bin"
	exit 1
fi

echo "Montownie nucleo..."
doas mount -t msdos /dev/sd1i /mnt

echo "Kopiowanie $1 na nucleo ..."
doas cp "$1" /mnt/
sync

echo "Odmontowywanie..."
doas umount /mnt

echo "Zakonczone sukcesem!"
