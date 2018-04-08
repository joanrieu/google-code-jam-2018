#!/bin/bash

function debug {
    true #printf "\e[32m%s\e[0m\n" "$*" >&2
}

function solution {
    case=$1
    sol=$2
    printf "Case #%d: %s\n" $case $sol
}

function measure {
    (
        printf 'let d=0;let s=1;'
        sed 's/C/let s=2*s;/g;s/S/let d=d+s;/g' <<<$program
        printf 'echo $d;'
    ) | bash
}

function hack {
    program=$1
    sed -r 's/CS(S*C*)$/SC\1/' <<<$program
}

function solve {
    case=$1
    shield=$2
    program=$3

    debug
    debug case $case
    debug shield $shield
    debug program $program

    let hacks=0

    while true
    do
        damage=$(measure $program)
        debug "   " $hacks $program '-->' $damage
        if [[ $damage -le $shield ]]
        then
            solution $case $hacks
            break
        fi
        oldprogram=$program
        program=$(hack $program)
        let hacks=hacks+1
        if [[ $program == $oldprogram ]]
        then
            solution $case IMPOSSIBLE
            break
        fi
    done
}

function io {
    read count
    let case=1
    while [[ $case -le $count ]]
    do
        read -d ' ' shield
        read program
        solve $case $shield $program
        let case=case+1
    done
}

io
