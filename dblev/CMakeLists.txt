cmake_minimum_required (VERSION 2.6)
project (MAL)

set(source
  reader.cpp
  printer.cpp
  env.cpp
)

set(headers
   types.h
   reader.h
   printer.h
   regex_strings.h
   env.h
)

#add_executable(step0_repl step0_repl.cpp)
#add_executable(step1_read_print step1_read_print.cpp ${source} ${headers})
#add_executable(step2_eval step2_eval.cpp  ${source} ${headers})
add_executable(step3_env step3_env.cpp  ${source} ${headers})


