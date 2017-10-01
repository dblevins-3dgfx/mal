#pragma once

const char* LISP_REGEXP = R"([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))";
const char* INTEGER_REGEXP = R"(-?[0-9]+)";
