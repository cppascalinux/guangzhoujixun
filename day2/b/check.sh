while true; do
	./gen;./std;./b1
	if diff std.out b1.out; then
		echo AC
	else
		echo WA
		exit 0
	fi
done