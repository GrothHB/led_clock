for plik in *.c *.h; do
	while read -r nazwa; do
		if [ -n "$nazwa" ]; then
			echo "Podmieniam: $nazwa w pliku $plik"
			vim -es -c "%s/\<$nazwa\>/volatile &/g" -c "wq" "$plik"
		fi
	done < warnings2
done
