while true; do
	./gen;./a;./std
	if diff a.out std.out; then
		echo AC
	else
		echo WA
		exit 0
	fi
done