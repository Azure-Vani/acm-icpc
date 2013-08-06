# deleted file list
a=(datamk.cpp out ou in check.cpp force.cpp G.ps d.ps G.dot D.ps D.dot in_b script.sh log d.dot)

function In {
	tmp=$1
	for i in $2
	do
		if [ ${tmp##*/} == $i ]
		then
			return 0;
		fi
	done
	return 1
}

function del {
	if [ -x $1 ] || In $1 "${a[*]}"
	then
		echo "rm $1"
		rm $1 -i
	fi
}

function Dfs {
	for i in $1/*
	do
		[ -d $i ] && Dfs $i
		[ -f $i ] && del $i
	done
}

if [ "$#" == "0" ]; then
	Dfs .
else
	Dfs "$1"
fi

exit 0
