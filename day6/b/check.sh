while true; do
	./gen;time ./b;time ./bf
	if diff b.out bf.out; then
		echo AC
	else
		echo WA
		exit 0
	fi
done