#!/bin/bash

function solution {
    case=$1
    sol=$2
    printf "Case #%d: %s\n" $case $sol
}

function trouble-pass {
    unset rerun
    read a
    read b

    while read c
    do
        if [[ $a -gt $c ]]
        then
            rerun=yes
            tmp=$a
            a=$c
            c=$tmp
        fi

        echo $a

        a=$b
        b=$c
    done

    echo $a
    echo $b
}

function trouble {
    case=$1
    let i=0
    trouble-pass >tmp-$case-0.txt
    while [[ $rerun ]]
    do
        trouble-pass <tmp-$case-$i.txt >tmp-$case-$((i+1)).txt
        let i=i+1
    done
    cat tmp-$case-$i.txt
}

function check {
    case=$1
    let col=$(sort --check 2>&1 | cut -d ':' -f 3)-2
    if [[ $col -lt 0 ]]
    then
        solution $case OK
    else
        solution $case $col
    fi
}

function solve {
    case=$1
    trouble $case | check $case
}

function io {
    read cases
    let case=1
    while [[ $case -le $cases ]]
    do
        read length
        head -1 | tr " " "\n" | solve $case
        let case=case+1
    done
}

io
