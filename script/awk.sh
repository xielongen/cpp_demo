#!/bin/bash
#message = `mysql -uadmin -p123456 -e 'show global variables'`
#echo $message
#
#echo `uptime`
echo $(date +%s.%N)
date -d "2018-09-01 00:00" +%s --utc
date +"%c" >> /tmp/test
awk '
    BEGIN{
    }
    {
        last = NF - 1
        printf "%s", $last
    }
    {
    }
' /tmp/test
ls |awk '{print $3}'