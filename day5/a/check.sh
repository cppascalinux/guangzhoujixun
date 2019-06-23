while true; do
	./gen; ./a; ./a1
	if diff a.out a1.out; then
		echo AC
	else
		echo WA
		exit 0
	fi
done