#!bash

PROGNAME=${0##*[\\/]}

# require one parameter at least
if [ $# = 0 ]; then
  echo "${PROGNAME}: command [options...]"
  exit 1
fi

# find shell program in PATH
for name in "COMMAND.COM"
do
  COMMAND_SHELL_NAME=`type -path $name`
  if [ "$COMMAND_SHELL_NAME" != "" ]; then
    break;
  fi
done
if [ "$COMMAND_SHELL_NAME" = "" ]; then
  echo "${PROGNAME}: cannot find shell"
  exit 1
fi

# fix all of arguments
FIXED_ARGS=`for arg in "$@"
do
  # replace slash to back slash if need
  if [ "${arg#/[a-zA-Z]}" != "" -a "${arg##*/}" != "${arg}" ]; then
    echo $arg | sed -e 's,/,\\\\,g'
  else
    echo $arg
  fi
done`

# set positional parameters
OIFS=$IFS
IFS=`builtin echo -ne '\012\015'`
set $FIXED_ARGS
IFS=$OIFS

# run commands
"$COMMAND_SHELL_NAME" "/c" "$@"
