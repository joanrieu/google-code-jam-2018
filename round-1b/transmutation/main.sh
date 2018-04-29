#!/bin/bash -e

function parse {
            read metals
            for ((m=1;m<=metals;m++))
            do
                read ma mb
                rule $ma $mb $m
            done
            head -1 | tr " " "\n" |
            for ((m=1;m<=metals;m++))
            do
                read s
                stock $s $m
            done
            main $t
}

function rule {
    ma=$1
    mb=$2
    m=$3
    cat <<END
function get$m {
    if [[ \$getting$m -eq 1 ]]
    then
        exit
    elif [[ \$stock$m -gt 0 ]]
    then
        let stock$m=stock$m-1
    else
        let getting$m=1
        get$ma
        get$mb
        let getting$m=0
    fi
}
END
}

function stock {
    s=$1
    m=$2
    cat <<END
let stock$m=$s
END
}

function main {
    t=$1
    cat <<END
echo -n "Case #$t: "
while true
do
    get1
    echo .
done | wc -l
END
}

read tsts
for ((t=1;t<=tsts;t++))
do
    parse | bash
done
