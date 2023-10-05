#! bash
### Time-stamp: <lfn2sfn-change.sh: 10 JUN 1999   0:27 (rjvdboon)>
### A little exercise in bash...
export SCRTMPFIL=_ttmmpp.rj
function _rjmv2() {
  if [ $# -ne 2 ] ; then
    echo "usage: _rjmv2 OldName NewName" 1>&2
    return 1
  fi
  if [ -f $1 ] ; then
    if [ "$1" = "$2" ] ; then
      echo "_rjmv2: \`$1' and \`$2' are the same." 1>&2
      return 1
    else
      echo _rjmv2: mv $1 $2
      mv $1 $2
    fi
  else
      echo "_rjmv2: \`$1' does not exist! Did you execute me already?" 1>&2
      return 1
  fi 
}

echo Straightforward patches to AUTHORS, MANIFEST, Makefile.in, and Makefile
echo will be applied to change y.tab to y_tab
for f in \
  ./AUTHORS \
  ./MANIFEST \
  ./Makefile.in \
  ./Makefile
do
  sed -e 's%y.tab%y_tab%g' $f > ${SCRTMPFIL} \
    && update ${SCRTMPFIL} $f \
    && rm ${SCRTMPFIL}
done

echo The files in the ./support/ branch, and parse.y are deliberately
echo not changed.
