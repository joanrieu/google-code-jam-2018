echo 1
numbers=100000
echo $numbers
let i=0
while [[ $i -lt 100000 ]]
do
    printf '%d ' $RANDOM
    let i=i+1
done | sed -r 's/ $//g'
echo
