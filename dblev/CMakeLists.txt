cmake_minimum_required (VERSION 2.6)
project (MAL)

set(step0_source
  step0_repl.cpp
)

add_executable(step0_repl ${step0_source})

set(step1_source
  step1_read_print.cpp
  reader.cpp
  printer.cpp
)

set(step1_headers
   types.h
   reader.h
   printer.h
   regex_strings.h
)

add_executable(step1_read_print  ${step1_source} ${step1_headers})
