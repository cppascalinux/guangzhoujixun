while true; do
	./gen; time ./a; time ./bf
	if diff a.out bf.out; then
		echo AC
	else
		echo WA
		exit 0
	fi
done