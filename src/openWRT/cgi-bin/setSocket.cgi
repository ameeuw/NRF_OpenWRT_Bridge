#!/bin/sh -ax

socket=`echo "$QUERY_STRING" | sed -n 's/^.*so=\([^&]*\).*$/\1/p' | sed "s/%20/ /g"`
 state=`echo "$QUERY_STRING" | sed -n 's/^.*st=\([^&]*\).*$/\1/p' | sed "s/%20/ /g"`

host=`echo -e "$socket,$state;" > /dev/ttyACM0`;

echo "Content-type: text/html"
echo ""
echo "Script:<br>"
echo "Query String is: $QUERY_STRING<br>"
echo "Socket Number: $socket<br>"
echo "State: $state<br>"