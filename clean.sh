# deleted file list
a=(datamk.cpp out ou in check.cpp force.cpp G.ps d.ps G.dot)

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
		rm $1
	fi
}

function Dfs {
	for i in $1/*
	do
		[ -d $i ] && Dfs $i
		[ -f $i ] && del $i
	done
}

Dfs .
exit 0
