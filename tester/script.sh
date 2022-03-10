#!/bin/bash

CC="clang++"
CFLAGS="-Wall -Wextra -Werror -std=c++98"
CFLAGS+=" -fsanitize=address -g3"

include="../srcs/"
srcs="srcs"

compile () {
	# 1=file 2=define used {ft/std} 3=output_file 4?=compile_log
	macro_name=$"USING_${2}"
    # printf "%s\n" "$macro_name"
	compile_cmd="$CC $CFLAGS -o ${3} -I./$include -D ${macro_name} ${1}"
	if [ -n "$4" ]; then
		compile_cmd+=" &>${4}"
	fi
	eval "${compile_cmd}"
	return $?
}

isEq ()
{
	[ $1 -eq $2 ] && echo 0 || echo 1
}

printRet()
{
    # 1 container, 2 compilation diff, 3 diff
    compile='';
    case $2 in
        0) compile="✅";;
        1) compile="❌";;
    esac
    output='';
    case $3 in
        0) output="✅";;
        1) output="❌";;
    esac
    printf "%-8s: compile: %s diff: %s\n" $1 "$compile" "$output"
}

different()
{
    if ! [ -s $1 ]; then
		return 0
	fi
    return 1
}

test_one()
{
    #1 container
    bindir="bin"; logdir="logs"; deepdir="diff"
    mkdir -p $bindir $logdir $deepdir
    container=$1
	file="${srcs}/$1.cpp"
	ft_bin="$bindir/ft.$container.out"; ft_log="$logdir/ft.$container.log"
	std_bin="$bindir/std.$container.out"; std_log="$logdir/std.$container.log"
	diff_file="$deepdir/$container.diff"

    compile "$file" "FT"  "$ft_bin"  /dev/null; ft_ret=$?
	compile "$file" "STD" "$std_bin" /dev/null; std_ret=$?
    compilation=$(isEq $ft_ret $std_ret)

    > $ft_log; > $std_log;
	if [ $ft_ret -eq 0 ]; then
		./$ft_bin &>$ft_log; ft_ret=$?
	fi
	if [ $std_ret -eq 0 ]; then
		./$std_bin &>$std_log; std_ret=$?
	fi

    diff $std_log $ft_log 2>/dev/null 1>"$diff_file";
    different $diff_file; difference=$?

    printRet $container $compilation $difference

    #clean
     rm -f $ft_bin $std_bin
	 [ -s "$diff_file" ] || rm -f $diff_file $ft_log $std_log &>/dev/null
	 rmdir $bindir $deepdir $logdir &>/dev/null
}

function main()
{
    containers=(vector stack map set)
    for container in ${containers[@]}; do
        test_one $container
    done
}