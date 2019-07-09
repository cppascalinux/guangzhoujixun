while true; do
	./gen;./b;./bf
	if diff bf.out b.out; then
		echo $i
	else
		exit 0
	fi
	i=$(($i+1))
done