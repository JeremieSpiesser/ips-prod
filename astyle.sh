#!/bin/bash

OPTIONS='
    --style=linux -s4
    --pad-oper --pad-header --pad-comma
    --align-pointer=name --align-reference=name
    --break-one-line-headers
    --remove-braces
    --break-return-type
    --convert-tabs
    --close-templates
    --max-code-length=101
    --mode=c
    --lineend=linux
    --attach-inlines
    --indent-labels
    --indent-col1-comments
    --indent-preproc-block'

astyle $OPTIONS --recursive 'src/*.cpp'  || exit 1
astyle $OPTIONS --recursive 'headers/*.h'    || exit 1
astyle $OPTIONS --recursive 'tests/test*.h'    || exit 1
find . -name '*.orig' -exec rm {} \;
exit 0
