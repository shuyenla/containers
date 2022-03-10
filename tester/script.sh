#!/bin bash

CC = "clang++"
CFLAGS = "-Wall -Wextra -Werror -std=c++98"
CFLAGS += " -fsanitize=address -g3"

include = "../srcs/"
srcs = "srcs"

isEq ()
{
	[ $1 -eq $2 ] && echo 0 || echo 1
}

printRet()
{
    # 1 test name, 2 difference
    printf "%-30s:" $1
    if [ $2 -eq 0 ]; then
        printf "Output is different\n"
    else
        printf "Output is the same\n"
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
    logdir = "logs"; deepdir = "diff" 
    mkdir -p $logdir $deepdir
    container=$(echo $1 | cut -d "/" -f 2)
	file=$(echo $1 | cut -d "/" -f 3)
	testname=$(echo $file | cut -d "." -f 1)
	ft_bin="ft.$container.out"; ft_log="$logdir/ft.$testname.$container.log"
	std_bin="std.$container.out"; std_log="$logdir/std.$testname.$container.log"
	diff_file="$deepdir/$testname.$container.diff"

    compile "$1" "ft"  "$ft_bin"  /dev/null; ft_ret=$?
	compile "$1" "std" "$std_bin" /dev/null; std_ret=$?

    > $ft_log; > $std_log;
	if [ $ft_ret -eq 0 ]; then
		./$ft_bin &>$ft_log; ft_ret=$?
	fi
	if [ $std_ret -eq 0 ]; then
		./$std_bin &>$std_log; std_ret=$?
	fi

    diff $std_log $ft_log 2>/dev/null 1>"$diff_file";
    different $diff_file; difference = $?
    printRet "$container/$file" $difference

}

tester()
{
    test = $(find "${srcs}/${1}" | sort)
    for file in ${test[@]}; do
        test_one "${file}"
    done
}

function main()
{
    containers = (vector stack map set)
    for container in ${containers[@]}; do
        print "s\n" $container
        tester $container 2>/dev/null
    done
}