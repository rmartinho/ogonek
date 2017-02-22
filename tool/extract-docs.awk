BEGIN { FS=" +" }
/^ *\/\*\* *$/ { select=1; next }
/^ +\*\/ *$/  { select=0; print ""; next }
select==1 && /^ +\*/ { print substr($0, index($0, $2)+2) }
