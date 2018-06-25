#!/bin/bash
if [ $# != 1 ]; then
    echo "incorrect number of arguments"
fi

WORK_DIR="$1"
CORR_DIR="$WORK_DIR/test_correct"
INCORR_DIR="$WORK_DIR/test_incorrect"
WITH_MAIN_CATCH="$WORK_DIR/test_correct_catch_bad"
NO_MAIN_C_DIR="$WORK_DIR/test_lib_correct"
NO_MAIN_I_DIR="$WORK_DIR/test_lib_incorrect"

if [ ! -d "$CORR_DIR" ]; then
    mkdir "$CORR_DIR"
fi

if [ ! -d "$INCORR_DIR" ]; then
    mkdir "$INCORR_DIR"
fi

if [ ! -d "$NO_MAIN_C_DIR" ]; then
    mkdir "$NO_MAIN_C_DIR"
fi

if [ ! -d "$NO_MAIN_I_DIR" ]; then
    mkdir "$NO_MAIN_I_DIR"
fi

if [ ! -d "$WITH_MAIN_CATCH" ]; then
    mkdir "$WITH_MAIN_CATCH"
fi

temp_file=$(mktemp)

for filename in "$WORK_DIR"/*.c; do
    bname=${filename##*/}
    echo "preprocessing $bname"
    sed -e 's/#include/\/\/_#_include/g' -e 's/#ifndef s_/\/\/_#_ifndef s_/g' -e 's/#define s_/\/\/_#_define s_/g' -e 's/#endif \/\/s_/\/\/_#_endif \/\/s_/g' "$filename" > $temp_file
    gpp +s "\"" "\"" "\\" +s "'" "'" "\\" -DNO_BUG $temp_file -o "$CORR_DIR/$bname"
    gpp +s "\"" "\"" "\\" +s "'" "'" "\\" $temp_file -o "$INCORR_DIR/$bname"
    gpp +s "\"" "\"" "\\" +s "'" "'" "\\" -DNO_MAIN $temp_file -o "$NO_MAIN_I_DIR/$bname" 
    gpp +s "\"" "\"" "\\" +s "'" "'" "\\" -DNO_MAIN -DCATCH_BAD_PARAM $temp_file -o "$NO_MAIN_C_DIR/$bname"
    gpp +s "\"" "\"" "\\" +s "'" "'" "\\" -DNO_BUG -DCATCH_BAD_PARAM $temp_file -o "$WITH_MAIN_CATCH/$bname"
    sed -i -e 's/\/\/_#_include/#include/g' -e 's/\/\/_#_ifndef/#ifndef/g' -e 's/\/\/_#_define/#define/g' -e 's/\/\/_#_endif \/\/s_/#endif \/\/s_/g' "$INCORR_DIR/$bname" "$CORR_DIR/$bname" "$NO_MAIN_I_DIR/$bname" "$NO_MAIN_C_DIR/$bname" "$WITH_MAIN_CATCH/$bname"
done

rm -f temp_file
