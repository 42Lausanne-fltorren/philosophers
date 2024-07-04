#!/bin/bash

ex=0

# Test 1 800 200 200. The philosopher should not eat and should die.
test="Test 1 800 200 200"
echo -n $test ": "
res=`./philo 1 800 200 200 | tail -n 1`
if [[ $res == *"0 died" ]]; then
    echo "OK"
else
    echo "KO"
    echo $res
    ex=1
fi

#Test 5 800 200 200. No philosopher should die.
test="Test 5 800 200 200"
echo $test ": No test."

test="Test 5 800 200 200 7"
echo -n $test ": "
res=`./philo 5 800 200 200 7 | grep "is done eating" | wc -l`
if (( $res >= 35 )); then
    echo "OK"
else
    echo "KO"
    echo $res
    ex=1
fi

test="Test 4 410 200 200"
echo $test ": No test."

test="Test 4 310 200 200"
echo -n $test ": "
res=`./philo 4 310 200 200 | tail -n 1`
if [[ $res == *"died"* ]]; then
    echo "OK"
else
    echo "KO"
    echo $res
    ex=1
fi

test="Test with 2 philosophers"
min=60
max=1000
ttd=$(($RANDOM%($max-$min+1)+$min))
min=$(($ttd/3))
max=1000
tte=$(($RANDOM%($max-$min+1)+$min))
tts=$(($RANDOM%($max-$min+1)+$min))
echo -n $test "(parameters: $ttd $tte $tts): "
res=`./philo 2 $ttd $tte $tts | grep "died" | awk '{print $1}'`
if (( res >= $ttd - 10 && res <= $ttd + 10)); then
    echo "OK"
else
    echo "KO"
    echo $res
    ex=1
fi

exit $ex